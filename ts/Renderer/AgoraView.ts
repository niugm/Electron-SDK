import { getEngineById, logWarn } from "../Utils";
import { CONTENT_MODE, VideoSourceType } from "./type";

const VIDEO_SOURCE_TYPE_STRING = "video-source-type";
const UID_STRING = "uid";
const CHANNEL_ID_STRING = "channel-id";
const RENDERER_CONTENT_MODE_STRING = "renderer-content-mode";
const RENDERER_MIRROR_STRING = "renderer-mirror";
const ENGINE_ID_STRING = "engine-id";

const observedAttributes = [
  VIDEO_SOURCE_TYPE_STRING,
  UID_STRING,
  CHANNEL_ID_STRING,
  RENDERER_CONTENT_MODE_STRING,
  RENDERER_MIRROR_STRING,
  ENGINE_ID_STRING,
];
export default class AgoraView extends HTMLElement {
  isConnectedCallback = false;
  static get observedAttributes() {
    return observedAttributes;
  }

  get videoSourceType(): VideoSourceType {
    const number = Number(this.getAttribute(VIDEO_SOURCE_TYPE_STRING));
    return isNaN(number) ? 0 : number;
  }

  set videoSourceType(val) {
    if (val) {
      this.setAttribute(VIDEO_SOURCE_TYPE_STRING, String(val));
    } else {
      this.removeAttribute(VIDEO_SOURCE_TYPE_STRING);
    }
  }
  get uid(): number {
    const number = Number(this.getAttribute(UID_STRING));
    return isNaN(number) ? 0 : number;
  }

  set uid(val) {
    if (val) {
      this.setAttribute(UID_STRING, String(val));
    } else {
      this.removeAttribute(UID_STRING);
    }
  }
  get channelId(): string {
    return this.getAttribute(CHANNEL_ID_STRING) || "";
  }

  set channelId(val) {
    if (val) {
      this.setAttribute(CHANNEL_ID_STRING, val);
    } else {
      this.removeAttribute(CHANNEL_ID_STRING);
    }
  }

  get renderContentMode(): CONTENT_MODE {
    const number = Number(
      this.getAttribute(RENDERER_CONTENT_MODE_STRING) || CONTENT_MODE.FIT
    );
    return isNaN(number) ? CONTENT_MODE.FIT : number;
  }

  set renderContentMode(val) {
    if (val) {
      this.setAttribute(RENDERER_CONTENT_MODE_STRING, String(val));
    } else {
      this.removeAttribute(RENDERER_CONTENT_MODE_STRING);
    }
  }
  get renderMirror(): boolean {
    return this.getAttribute(RENDERER_MIRROR_STRING) === "true";
  }

  set renderMirror(val) {
    if (val) {
      this.setAttribute(RENDERER_MIRROR_STRING, String(val));
    } else {
      this.removeAttribute(RENDERER_MIRROR_STRING);
    }
  }
  get engineId(): string {
    return this.getAttribute(ENGINE_ID_STRING)!;
  }

  set engineId(val) {
    if (val) {
      this.setAttribute(ENGINE_ID_STRING, val);
    } else {
      this.removeAttribute(ENGINE_ID_STRING);
    }
  }

  // Can define constructor arguments if you wish.
  constructor() {
    // If you define a constructor, always call super() first!
    // This is specific to CE and required by the spec.
    super();

    // Setup a click listener on <app-drawer> itself.
    this.addEventListener("click", (e) => {
      // Don't toggle the drawer if it's disabled.
      // console.log("click");
      // const rtcEngine = getEngineById(this.engineId)!;
      // rtcEngine.setView({
      //   videoSourceType: this.videoSourceType,
      //   uid: this.uid,
      //   channelId: this.channelId,
      //   rendererOptions: {
      //     mirror: this.renderMirror,
      //     contentMode: this.renderContentMode,
      //   },
      // });
    });
  }
  initializeRender() {
    const rtcEngine = getEngineById(this.engineId);
    if (!rtcEngine) {
      throw new Error(
        "must initialize a engine and give an engine-id to agora-view"
      );
    }
    rtcEngine.destroyRendererByView(this);
    rtcEngine.setView({
      videoSourceType: this.videoSourceType,
      view: this,
      uid: this.uid,
      channelId: this.channelId,
      rendererOptions: {
        mirror: this.renderMirror,
        contentMode: this.renderContentMode,
      },
    });
    this.logInfo();
  }
  logInfo() {
    console.log(
      "\nthis.channelId: ",
      `"${this.channelId}"`,
      "\nthis.uid: ",
      this.uid,
      "\nthis.renderContentMode: ",
      this.renderContentMode,
      "\nthis.renderMirror: ",
      this.renderMirror,
      "\nthis.videoSourceType: ",
      this.videoSourceType
    );
  }
  connectedCallback() {
    this.isConnectedCallback = true;
    this.initializeRender();
  }

  disconnectedCallback() {
    this.isConnectedCallback = false;
    const rtcEngine = getEngineById(this.engineId);
    if (!rtcEngine) {
      logWarn(
        "It is recommended to remove the dom node before the engine is released"
      );
      return;
    }
    rtcEngine.destroyRendererByView(this);
  }
  attributeChangedCallback(attrName: string, oldVal: any, newVal: any) {
    if (!this.isConnectedCallback) {
      return;
    }
    const isSetRenderOption = [
      RENDERER_CONTENT_MODE_STRING,
      RENDERER_MIRROR_STRING,
    ].includes(attrName);
    if (isSetRenderOption) {
      const rtcEngine = getEngineById(this.engineId);
      if (!rtcEngine) {
        throw new Error(
          "must initialize a engine and give an engine-id to agora-view"
        );
      }
      rtcEngine.setRenderOption(
        this,
        this.renderContentMode,
        this.renderMirror
      );
      return;
    }
    const isNeedReInitialize = observedAttributes.includes(attrName);
    if (!isNeedReInitialize) {
      return;
    }
    this.initializeRender();
  }
}
window.customElements.define("agora-view", AgoraView);
