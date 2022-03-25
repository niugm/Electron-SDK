import {
  VideoSourceType,
  RendererConfigInternal,
  RendererConfig,
  CONTENT_MODE,
} from "../Renderer/type";

import { EngineEvents } from "../Common/JSEvents";
import { AgoraRtcEngine } from "../Api/AgoraRtcEngine";

export const TAG = "[Agora]: ";
export const DEBUG_TAG = "[Agora]: ";

export const deprecate = (originApi?: string, replaceApi?: string) => {
  console.warn(
    `${TAG} This method ${originApi} will be deprecated soon. `,
    replaceApi ? `Please use ${replaceApi} instead` : ""
  );
};

export const logWarn = (msg: string, tag: string = TAG) => {
  console.warn(`${tag} ${msg}`);
};

export const logError = (msg: string, tag: string = TAG) => {
  console.error(`${tag} ${msg}`);
};

export const logInfo = (msg: string, tag: string = TAG) => {
  console.log(`${tag} ${msg}`);
};
export const logDebug = (msg: string, tag: string = DEBUG_TAG) => {
  console.warn(`${tag} ${msg}`);
};

export const objsKeysToLowerCase = (array: Array<any>) => {
  array.forEach((obj) => {
    for (const key in obj) {
      if (Object.prototype.hasOwnProperty.call(obj, key)) {
        const element = obj[key];
        obj[key.toLocaleLowerCase()] = element;
      }
    }
  });
};

export const changeEventNameForOnXX = (eventName: string) =>
  eventName.slice(2, 3).toLocaleLowerCase() + eventName.slice(3);
export const jsonStringToArray = (jsonString: string) => {
  try {
    return JSON.parse(jsonString);
  } catch (error) {
    logError(`jsonStringToArray error: ${jsonString}`);
    return [];
  }
};
interface ForwardEventParam {
  event: {
    eventName: string;
    params: string;
    buffer?: string;
    changeNameHandler: (_eventName: string) => string;
  };
  fire: (eventName: string, ...arg: any[]) => void;
  filter: (eventName: string, params: Array<any>, buffer?: string) => Boolean;
}
const onApiErrorEventName = "onApiError";

export const forwardEvent = ({
  event: { eventName, params, buffer, changeNameHandler },
  fire,
  filter,
}: ForwardEventParam) => {
  if (eventName === onApiErrorEventName) {
    console.error(eventName, params);
    fire(EngineEvents.API_ERROR, params);
    return;
  }
  try {
    const _params = JSON.parse(params);
    const isFilter = filter(eventName, _params, buffer);
    if (isFilter || !fire) {
      return;
    }
    const finalEventName = changeNameHandler(eventName);

    fire(finalEventName, ..._params);
    fire(finalEventName.toLocaleLowerCase(), ..._params);
  } catch (error) {
    console.error(
      `forwardEvent eventName:${eventName}  params:${params}  error:`,
      error
    );
  }
};

export const formatVideoFrameBufferConfig = (
  videoSourceType: VideoSourceType,
  originChannelId = "",
  originUid = 0
): {
  uid: number;
  channelId: string;
  videoSourceType: VideoSourceType;
} => {
  if (videoSourceType === undefined || videoSourceType === null) {
    throw new Error(`must set videoSourceType`);
  }
  let uid = originUid;
  let channelId = originChannelId;

  switch (videoSourceType) {
    case VideoSourceType.kVideoSourceTypeCameraPrimary:
    case VideoSourceType.kVideoSourceTypeCameraSecondary:
    case VideoSourceType.kVideoSourceTypeScreenPrimary:
    case VideoSourceType.kVideoSourceTypeScreenSecondary:
      channelId = "";
      uid = 0;
      break;
    case VideoSourceType.kVideoSourceTypeRemote:
      if (!uid || !channelId) {
        throw new Error(`must have uid:${uid}}  channelId:${channelId}`);
      }
      break;
    default:
      break;
  }
  return { uid, channelId, videoSourceType };
};

export const getRendererConfigInternal = (
  config: RendererConfig
): RendererConfigInternal => {
  const rendererOptions = Object.assign(
    {
      contentMode: CONTENT_MODE.FIT,
      mirror: false,
    },
    config.rendererOptions
  );

  const { uid, channelId } = formatVideoFrameBufferConfig(
    config.videoSourceType,
    config.channelId,
    config.uid
  );

  return { ...config, uid, channelId, rendererOptions };
};

const rtcEngineMap: Map<string, AgoraRtcEngine> = new Map();

export const getEngineById = (id: string): AgoraRtcEngine | undefined => {
  return rtcEngineMap.get(id);
};
export const deleteEngineById = (id: string): boolean => {
  return rtcEngineMap.delete(id);
};

export const setEngineById = (
  id: string,
  engine: AgoraRtcEngine
): Map<string, AgoraRtcEngine> => {
  return rtcEngineMap.set(id, engine);
};
