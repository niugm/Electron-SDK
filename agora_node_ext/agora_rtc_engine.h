/*
 * Copyright (c) 2017 Agora.io
 * All rights reserved.
 * Proprietary and Confidential -- Agora.io
 */

/*
 *  Created by Wang Yongli, 2017
 */

#ifndef AGORA_NODE_RTC_ENGINE_H
#define AGORA_NODE_RTC_ENGINE_H

#include "AVPlugin/IAVFramePlugin.h"
#include "AVPlugin/IAVFramePluginManager.h"
#include "IAgoraMediaEngine.h"
#include "IAgoraRtcEngine.h"
#include "node_event_handler.h"
#include "node_log.h"
#include "node_metadata_observer.h"
#include "node_napi_api.h"
#include "node_video_render.h"
#include <functional>
#include <list>
#include <map>
#include <mutex>
#include <node.h>
#include <node_object_wrap.h>
#include <unordered_set>
/*
 * Used to declare native interface to nodejs
 */
#define NAPI_API(m) static void(m)(const Nan::FunctionCallbackInfo<Value> &args)

/*
 * Used to define native interface which is exposed to nodejs
 */
#define NAPI_API_DEFINE(cls, method)                                           \
  void cls::method(const Nan::FunctionCallbackInfo<Value> &args)

namespace agora {
namespace rtc {
// using media::IExternalVideoRenderFactory;
using v8::Isolate;
const int max_bmp_width = 500;
const int max_bmp_height = 500;
/*
 * class NodeRtcEngine is the wrapper for IAgoraRtcEngine, and is exposed to
 * nodejs as the native interface.
 */
class NodeRtcEngine : public node::ObjectWrap {
public:
  /*
   * Constructor
   */
  static void createInstance(const FunctionCallbackInfo<Value> &args);

  /*
   * Helper function, used to declare all supported native interface that are
   * exposed to nodejs.
   */
  static void Init(Local<Object> &module);

  /*
   * Wrapper for RtcEngine functions
   */
  NAPI_API(initialize);
  NAPI_API(getVersion);
  NAPI_API(getErrorDescription);
  NAPI_API(joinChannel);
  NAPI_API(leaveChannel);
  NAPI_API(renewToken);
  NAPI_API(setChannelProfile);
  NAPI_API(setClientRole);
  NAPI_API(startEchoTest);
  NAPI_API(stopEchoTest);
  // NAPI_API(enableLastmileTest);
  // NAPI_API(disableLastmileTest);
  NAPI_API(enableVideo);
  NAPI_API(disableVideo);
  NAPI_API(startPreview);
  NAPI_API(stopPreview);
  // NAPI_API(setVideoProfile);
  NAPI_API(setVideoEncoderConfiguration);
  NAPI_API(enableAudio);
  NAPI_API(disableAudio);
  NAPI_API(setAudioProfile);
  NAPI_API(getCallId);
  NAPI_API(rate);
  NAPI_API(complain);
  NAPI_API(setEncryptionSecret);
  NAPI_API(createDataStream);
  NAPI_API(sendStreamMessage);
  NAPI_API(setEncryptionMode);

  NAPI_API(configPublisher);

  NAPI_API(addPublishStreamUrl);
  NAPI_API(removePublishStreamUrl);
  NAPI_API(addVideoWatermark);
  NAPI_API(clearVideoWatermarks);
  NAPI_API(setLiveTranscoding);
  NAPI_API(addInjectStreamUrl);
  NAPI_API(removeInjectStreamUrl);

  /*
   * Wrapper for RtcEngineParameter API
   */
  NAPI_API(setBool);
  NAPI_API(setInt);
  NAPI_API(setUInt);
  NAPI_API(setNumber);
  NAPI_API(setString);
  NAPI_API(setObject);
  NAPI_API(getBool);
  NAPI_API(getInt);
  NAPI_API(getUInt);
  NAPI_API(getNumber);
  NAPI_API(getString);
  NAPI_API(getObject);
  NAPI_API(getArray);
  NAPI_API(setParameters);
  // NAPI_API(setProfile);
  NAPI_API(convertPath);

  NAPI_API(muteLocalAudioStream);
  NAPI_API(muteAllRemoteAudioStreams);
  NAPI_API(setDefaultMuteAllRemoteAudioStreams);
  NAPI_API(muteRemoteAudioStreamEx);
  NAPI_API(muteLocalVideoStream);
  NAPI_API(enableLocalVideo);
  NAPI_API(enableLocalAudio);
  NAPI_API(muteAllRemoteVideoStreams);
  NAPI_API(setDefaultMuteAllRemoteVideoStreams);
  NAPI_API(muteRemoteVideoStreamEx);
  NAPI_API(setRemoteVideoStreamType);
  NAPI_API(setRemoteDefaultVideoStreamType);
  NAPI_API(enableAudioVolumeIndication);
  NAPI_API(startAudioRecording);
  NAPI_API(stopAudioRecording);
  NAPI_API(startAudioMixing);
  NAPI_API(stopAudioMixing);
  NAPI_API(pauseAudioMixing);
  NAPI_API(resumeAudioMixing);
  NAPI_API(adjustAudioMixingVolume);
  NAPI_API(adjustAudioMixingPlayoutVolume);
  NAPI_API(adjustAudioMixingPublishVolume);
  NAPI_API(getAudioMixingPlayoutVolume);
  NAPI_API(getAudioMixingPublishVolume);
  NAPI_API(getAudioMixingDuration);
  NAPI_API(getAudioMixingCurrentPosition);
  NAPI_API(setAudioMixingPosition);
  NAPI_API(getEffectsVolume);
  NAPI_API(setEffectsVolume);
  NAPI_API(setVolumeOfEffect);
  NAPI_API(playEffect);
  NAPI_API(stopEffect);
  NAPI_API(stopAllEffects);
  NAPI_API(preloadEffect);
  NAPI_API(unloadEffect);
  NAPI_API(pauseEffect);
  NAPI_API(pauseAllEffects);
  NAPI_API(resumeEffect);
  NAPI_API(resumeAllEffects);
  NAPI_API(setLocalVoicePitch);
  NAPI_API(setLocalVoiceEqualization);
  NAPI_API(setLocalVoiceReverb);
  // NAPI_API(setExternalAudioSink);
  // NAPI_API(setLocalPublishFallbackOption);
  // NAPI_API(setRemoteSubscribeFallbackOption);
  NAPI_API(pauseAudio);
  NAPI_API(resumeAudio);
  NAPI_API(setExternalAudioSource);
#if defined(__APPLE__) || defined(_WIN32)
  NAPI_API(getScreenWindowsInfo);
  NAPI_API(getScreenDisplaysInfo);
  // NAPI_API(startScreenCapture);
  NAPI_API(stopScreenCapture);
  NAPI_API(updateScreenCaptureRegion);
#endif
  NAPI_API(setLogFile);
  NAPI_API(setLogFilter);

  NAPI_API(setLocalVideoMirrorMode);

  NAPI_API(enableDualStreamMode);
  NAPI_API(setRecordingAudioFrameParameters);
  NAPI_API(setPlaybackAudioFrameParameters);
  NAPI_API(setMixedAudioFrameParameters);
  NAPI_API(adjustRecordingSignalVolume);
  NAPI_API(adjustPlaybackSignalVolume);
  // NAPI_API(setHighQualityAudioParameters);
  NAPI_API(enableWebSdkInteroperability);
  // NAPI_API(setVideoQualityParameters);

  NAPI_API(enableLoopbackRecording);
  NAPI_API(enableLoopbackRecordingEx);
  NAPI_API(onEvent);
  NAPI_API(registerDeliverFrame);

  /*
   * Wrapper for device manager
   */
  NAPI_API(getVideoDevices);
  NAPI_API(setVideoDevice);
  NAPI_API(getCurrentVideoDevice);
  NAPI_API(startVideoDeviceTest);
  NAPI_API(stopVideoDeviceTest);
  NAPI_API(getAudioPlaybackDevices);
  NAPI_API(setAudioPlaybackDevice);
  NAPI_API(getPlaybackDeviceInfo);
  NAPI_API(getCurrentAudioPlaybackDevice);
  NAPI_API(setAudioPlaybackVolume);
  NAPI_API(getAudioPlaybackVolume);
  NAPI_API(getAudioRecordingDevices);
  NAPI_API(setAudioRecordingDevice);
  NAPI_API(getRecordingDeviceInfo);
  NAPI_API(getCurrentAudioRecordingDevice);
  NAPI_API(getAudioRecordingVolume);
  NAPI_API(setAudioRecordingVolume);
  NAPI_API(startAudioPlaybackDeviceTest);
  NAPI_API(stopAudioPlaybackDeviceTest);
  NAPI_API(startAudioRecordingDeviceTest);
  NAPI_API(stopAudioRecordingDeviceTest);
  NAPI_API(getAudioPlaybackDeviceMute);
  NAPI_API(setAudioPlaybackDeviceMute);
  NAPI_API(getAudioRecordingDeviceMute);
  NAPI_API(setAudioRecordingDeviceMute);

  /*
   * Native interface used to setup local and remote video canvas.
   */
  NAPI_API(subscribe);
  NAPI_API(unsubscribe);
  NAPI_API(setupLocalVideo);
  NAPI_API(setVideoRenderDimension);
  NAPI_API(setHighFPS);
  NAPI_API(setFPS);
  NAPI_API(addToHighVideo);
  NAPI_API(removeFromHighVideo);

  /**
   * Plugins
   */
  NAPI_API(initializePluginManager);
  NAPI_API(releasePluginManager);
  NAPI_API(registerPlugin);
  NAPI_API(unregisterPlugin);
  NAPI_API(enablePlugin);
  NAPI_API(getPlugins);
  NAPI_API(setPluginParameter);
  NAPI_API(getPluginParameter);

  /**
   * 2.3.3 apis
   */
  NAPI_API(getConnectionState);
  NAPI_API(release);

  /**
   * 2.4.0 apis
   */
  // NAPI_API(setBeautyEffectOptions);
  NAPI_API(setLocalVoiceChanger);
  NAPI_API(setLocalVoiceReverbPreset);
  // NAPI_API(enableSoundPositionIndication);
  // NAPI_API(setRemoteVoicePosition);
  NAPI_API(startLastmileProbeTest);
  NAPI_API(stopLastmileProbeTest);
  NAPI_API(setRemoteUserPriority);
  // NAPI_API(startEchoTestWithInterval);
  NAPI_API(startRecordingDeviceTest);
  NAPI_API(stopRecordingDeviceTest);
  // NAPI_API(setCameraCapturerConfiguration);
  NAPI_API(setLogFileSize);

  /**
   * 2.8.0 Apis
   */
  // NAPI_API(registerLocalUserAccount);
  // NAPI_API(joinChannelWithUserAccount);
  // NAPI_API(getUserInfoByUserAccount);
  // NAPI_API(getUserInfoByUid);

  /**
   * 2.9.0 Apis
   */
  // NAPI_API(switchChannel);
  NAPI_API(startChannelMediaRelay);
  NAPI_API(updateChannelMediaRelay);
  NAPI_API(stopChannelMediaRelay);

  /**
   * 2.9.0.100 Apis
   */
  NAPI_API(startScreenCaptureByWindow);
  NAPI_API(updateScreenCaptureParameters);
  NAPI_API(setScreenCaptureContentHint);

  /**
   * 3.0.0 Apis
   */
  NAPI_API(adjustUserPlaybackSignalVolume);

  /**
   * 3.0.1 Apis
   */
  NAPI_API(setAudioMixingPitch);

  NAPI_API(sendMetadata);
  NAPI_API(addMetadataEventHandler);
  NAPI_API(setMaxMetadataSize);
  NAPI_API(registerMediaMetadataObserver);
  NAPI_API(unRegisterMediaMetadataObserver);

  NAPI_API(sendCustomReportMessage);
  NAPI_API(enableEncryption);
  // NAPI_API(setClientRoleWithOptions);
  NAPI_API(startLocalVideoTranscoder);
  NAPI_API(updateLocalTranscoderConfiguration);
  NAPI_API(stopLocalVideoTranscoder);
  NAPI_API(joinChannelEx);
  NAPI_API(joinChannel2);
  NAPI_API(updateChannelMediaOptions);
  NAPI_API(updateChannelMediaOptionsEx);

  NAPI_API(createMediaPlayer);
  NAPI_API(startPrimaryCameraCapture);
  NAPI_API(startSecondaryCameraCapture);
  NAPI_API(stopPrimaryCameraCapture);
  NAPI_API(stopSecondaryCameraCapture);
  NAPI_API(startPrimaryScreenCapture);
  NAPI_API(startSecondaryScreenCapture);
  NAPI_API(stopPrimaryScreenCapture);
  NAPI_API(stopSecondaryScreenCapture);
  NAPI_API(adjustLoopbackRecordingVolume);
  NAPI_API(setCameraDeviceOrientation);

  // Extension
  NAPI_API(enableExtension);
  NAPI_API(loadExtensionProvider);
  NAPI_API(getExtensionProperty);
  NAPI_API(setExtensionProperty);
  NAPI_API(setExtensionProviderProperty);
  NAPI_API(setBeautyEffectOptions);
  NAPI_API(setScreenCaptureOrientation);
  NAPI_API(setAddonLogFile);
  NAPI_API(leaveChannelEx);
  NAPI_API(startAudioRecording2);
  NAPI_API(setProcessDpiAwareness);
  NAPI_API(enableVirtualBackground);
  NAPI_API(startScreenCaptureByDisplayId);

public:
  Isolate *getIsolate() { return m_isolate; }
  IRtcEngine *getRtcEngine() { return m_engine; }

protected:
  NodeRtcEngine(Isolate *isolate);
  ~NodeRtcEngine();

private:
  DECLARE_CLASS;
  IRtcEngine *m_engine;
  std::unique_ptr<NodeEventHandler> m_eventHandler;
  Isolate *m_isolate;
  std::unique_ptr<agora::rtc::NodeVideoFrameObserver> m_nodeVideoFrameObserver;

  AVideoDeviceManager *m_videoVdm = nullptr;
  AAudioDeviceManager *m_audioVdm = nullptr;

  std::unique_ptr<IAVFramePluginManager> m_avPluginManager;
  std::unique_ptr<NodeMetadataObserver> metadataObserver;
};

/*
 * Use to extract native this pointer from JS object
 */
#define napi_get_native_this(args, native)                                     \
  native = ObjectWrap::Unwrap<NodeRtcEngine>(args.Holder());

/*
 * Use to extract native this pointer from JS object
 */
#define napi_get_native_channel(args, native)                                  \
  native = ObjectWrap::Unwrap<NodeRtcChannel>(args.Holder());

/*
 * to extract one parameter from JS call parameters.
 */
#define napi_get_param_1(args, type1, param1)                                  \
  do {                                                                         \
    status = napi_get_value_##type1##_(args[0], (param1));                     \
    if (status != napi_ok) {                                                   \
      break;                                                                   \
    }                                                                          \
  } while (false);

/*
 * to extract two parameters from JS call parameters.
 */
#define napi_get_param_2(argv, type1, param1, type2, param2)                   \
  do {                                                                         \
    status = napi_get_value_##type1##_(argv[0], (param1));                     \
    if (status != napi_ok) {                                                   \
      break;                                                                   \
    }                                                                          \
    status = napi_get_value_##type2##_(argv[1], (param2));                     \
    if (status != napi_ok) {                                                   \
      break;                                                                   \
    }                                                                          \
  } while (false);

/*
 * to extract three parameters from JS call parameters.
 */
#define napi_get_param_3(argv, type1, param1, type2, param2, type3, param3)    \
  do {                                                                         \
    status = napi_get_value_##type1##_(argv[0], (param1));                     \
    if (status != napi_ok) {                                                   \
      break;                                                                   \
    }                                                                          \
    status = napi_get_value_##type2##_(argv[1], (param2));                     \
    if (status != napi_ok) {                                                   \
      break;                                                                   \
    }                                                                          \
    status = napi_get_value_##type3##_(argv[2], (param3));                     \
    if (status != napi_ok) {                                                   \
      break;                                                                   \
    }                                                                          \
  } while (false);

/*
 * to extract four parameters from JS call parameters.
 */
#define napi_get_param_4(argv, type1, param1, type2, param2, type3, param3,    \
                         type4, param4)                                        \
  do {                                                                         \
    status = napi_get_value_##type1##_(argv[0], (param1));                     \
    if (status != napi_ok) {                                                   \
      break;                                                                   \
    }                                                                          \
    status = napi_get_value_##type2##_(argv[1], (param2));                     \
    if (status != napi_ok) {                                                   \
      break;                                                                   \
    }                                                                          \
    status = napi_get_value_##type3##_(argv[2], (param3));                     \
    if (status != napi_ok) {                                                   \
      break;                                                                   \
    }                                                                          \
    status = napi_get_value_##type4##_(argv[3], (param4));                     \
    if (status != napi_ok) {                                                   \
      break;                                                                   \
    }                                                                          \
  } while (false);

/*
 * to extract seven parameters from JS call parameters.
 */
#define napi_get_param_7(argv, type1, param1, type2, param2, type3, param3,    \
                         type4, param4, type5, param5, type6, param6, type7,   \
                         param7)                                               \
  do {                                                                         \
    status = napi_get_value_##type1##_(argv[0], (param1));                     \
    if (status != napi_ok) {                                                   \
      break;                                                                   \
    }                                                                          \
    status = napi_get_value_##type2##_(argv[1], (param2));                     \
    if (status != napi_ok) {                                                   \
      break;                                                                   \
    }                                                                          \
    status = napi_get_value_##type3##_(argv[2], (param3));                     \
    if (status != napi_ok) {                                                   \
      break;                                                                   \
    }                                                                          \
    status = napi_get_value_##type4##_(argv[3], (param4));                     \
    if (status != napi_ok) {                                                   \
      break;                                                                   \
    }                                                                          \
    status = napi_get_value_##type5##_(argv[4], (param5));                     \
    if (status != napi_ok) {                                                   \
      break;                                                                   \
    }                                                                          \
    status = napi_get_value_##type6##_(argv[5], (param6));                     \
    if (status != napi_ok) {                                                   \
      break;                                                                   \
    }                                                                          \
    status = napi_get_value_##type7##_(argv[6], (param7));                     \
    if (status != napi_ok) {                                                   \
      break;                                                                   \
    }                                                                          \
  } while (false);
/*
 * to return int value for JS call.
 */
#define napi_set_int_result(args, result)                                      \
  (args).GetReturnValue().Set(Integer::New(args.GetIsolate(), (result)))

/*
 * to return array value for JS call.
 */
#define napi_set_array_result(args, data) args.GetReturnValue().Set(data);
/**
 * to return bool value for JS call
 */
#define napi_set_bool_result(args, result)                                     \
  (args).GetReturnValue().Set(v8::Boolean::New(args.GetIsolate(), (result)))

/*
 * to return string value for JS call
 */
#define napi_set_string_result(args, data)                                     \
  Local<Value> tmp = String::NewFromUtf8(args.GetIsolate(), data,              \
                                         NewStringType::kInternalized)         \
                         .ToLocalChecked();                                    \
  args.GetReturnValue().Set(tmp);

/**
 * Helper MACRO to check whether the last API call return success.
 */
#define CHECK_NAPI_STATUS(engine, status)                                      \
  if (status != napi_ok) {                                                     \
    LOG_ERROR("Error :%s, :%d\n", __FUNCTION__, __LINE__);                     \
    engine->m_eventHandler->fireApiError(__FUNCTION__);                        \
    break;                                                                     \
  }

#define CHECK_NAPI_STATUS_STR(engine, status, key)                             \
  if (status != napi_ok) {                                                     \
    LOG_ERROR("Error :%s, :%d, error key: %s\n", __FUNCTION__, __LINE__,       \
              key.c_str());                                                    \
    char errMessage[256];                                                      \
    sprintf(errMessage,                                                        \
            "%s, error key: ******* \"%s\" *******, line :%d, call",           \
            __FUNCTION__, key.c_str(), __LINE__);                              \
    engine->m_eventHandler->fireApiError(errMessage);                          \
    break;                                                                     \
  }

#define CHECK_ARG_NUM(engine, args, num)                                       \
  if (args.Length() < num) {                                                   \
    CHECK_NAPI_STATUS(engine, napi_invalid_arg);                               \
  }

/**
 * Helper MACRO to check whether the extracted object is emptry;
 */
#define CHECK_NAPI_OBJECT(obj)                                                 \
  if (obj.IsEmpty()) {                                                         \
    LOG_ERROR("Error :%s, :%d\n", __FUNCTION__, __LINE__);                     \
    break;                                                                     \
  }

/**
 * Helper MACRO to check whether the extracted native this is valid.
 */
#define CHECK_NATIVE_THIS(engine)                                              \
  if (!engine || !engine->m_engine) {                                          \
    LOG_ERROR("m_engine is null.\n");                                          \
    break;                                                                     \
  }

#define CHECK_NATIVE_CHANNEL(channel)                                          \
  if (!channel || !channel->m_channel) {                                       \
    LOG_ERROR("m_channel is null.\n");                                         \
    break;                                                                     \
  }

#define CHECK_PLUGIN_INFO_EXIST(engine, pluginId)                              \
  if (!engine->m_avPluginManager->hasPlugin(pluginId)) {                       \
    LOG_ERROR("Error : plugin %s, not exist\n", pluginId.c_str());             \
    break;                                                                     \
  }

#define CHECK_PLUGIN_INFO_NOT_EXIST(engine, pluginId)                          \
  if (engine->m_avPluginManager->hasPlugin(pluginId)) {                        \
    LOG_ERROR("Error : plugin %s, has exist\n", pluginId.c_str());             \
    break;                                                                     \
  }

#define CHECK_PLUGIN_MANAGER_EXIST(engine)                                     \
  if (!engine->m_avPluginManager.get()) {                                      \
    LOG_ERROR("Error : plugin manager not exist\n");                           \
    break;                                                                     \
  }

#ifdef _WIN32
#define CHECK_PLUGIN_MODULE_EXIST(pluginInfo)                                  \
  if (pluginInfo.pluginModule == NULL) {                                       \
    LOG_ERROR("Error :%s, :%d, not unload plugin \"%s\"\n", __FUNCTION__,      \
              __LINE__, pluginInfo.id);                                        \
    break;                                                                     \
  }
#else
#define CHECK_PLUGIN_MODULE_EXIST(pluginInfo)                                  \
  if (pluginInfo.pluginModule == NULL) {                                       \
    LOG_ERROR("Error :%s, :%d, %sn, not unload plugin \"%s\"\n", __FUNCTION__, \
              __LINE__, dlerror(), pluginInfo.id);                             \
    break;                                                                     \
  }
#endif

#define CHECK_PLUGIN_INSTANCE_EXIST(pluginInfo)                                \
  if (pluginInfo.instance == NULL) {                                           \
    LOG_ERROR("Error :%s, :%d, not release plugin \"%s\"\n", __FUNCTION__,     \
              __LINE__, pluginInfo.id);                                        \
    break;                                                                     \
  }

#define READ_PLUGIN_ID(pEngine, status, arg, str)                              \
  nodestring nodeStr;                                                          \
  status = napi_get_value_nodestring_(arg, nodeStr);                           \
  CHECK_NAPI_STATUS(pEngine, status)                                           \
  str = nodeStr;

typedef int int32;
typedef NodeString nodestring;
typedef unsigned int uint32;

#ifdef _WIN32
#define CALL_MEM_FUNC_FROM_POINTER(pointer, func) pointer->##func()
#define CALL_MEM_FUNC_FROM_POINTER_WITH_PARAM(pointer, func, param)            \
  pointer->##func(param)
#define CALL_MEM_FUNC_FROM_POINTER_WITH_PARAM2(pointer, func, param1, param2)  \
  pointer->##func(param1, param2)
#define CALL_MEM_FUNC_FROM_POINTER_WITH_PARAM3(pointer, func, param1, param2,  \
                                               param3)                         \
  pointer->##func(param1, param2, param3)
#define CALL_MEM_FUNC_FROM_POINTER_WITH_PARAM7(                                \
    pointer, func, param1, param2, param3, param4, param5, param6, param7)     \
  pointer->##func(param1, param2, param3, param4, param5, param6, param7)

#define CALL_MEM_FUNC(cls, func) cls.##func()
#define CALL_MEM_FUNC_WITH_PARAM(cls, func, param) cls.##func(param)
#define CALL_MEM_FUNC_WITH_PARAM2(cls, func, param1, param2)                   \
  cls.##func(param1, param2)
#define CALL_MEM_FUNC_WITH_PARAM3(cls, func, param1, param2, param3)           \
  cls.##func(param1, param2, param3)
#define CALL_MEM_FUNC_WITH_PARAM7(cls, func, param1, param2, param3, param4,   \
                                  param5, param6, param7)                      \
  cls.##func(param1, param2, param3, param4, param5, param6, param7)
#else
#define CALL_MEM_FUNC_FROM_POINTER(pointer, func) pointer->func()
#define CALL_MEM_FUNC_FROM_POINTER_WITH_PARAM(pointer, func, param)            \
  pointer->func(param)
#define CALL_MEM_FUNC_FROM_POINTER_WITH_PARAM2(pointer, func, param1, param2)  \
  pointer->func(param1, param2)
#define CALL_MEM_FUNC_FROM_POINTER_WITH_PARAM3(pointer, func, param1, param2,  \
                                               param3)                         \
  pointer->func(param1, param2, param3)
#define CALL_MEM_FUNC_FROM_POINTER_WITH_PARAM7(                                \
    pointer, func, param1, param2, param3, param4, param5, param6, param7)     \
  pointer->func(param1, param2, param3, param4, param5, param6, param7)

#define CALL_MEM_FUNC(cls, func) cls.func()
#define CALL_MEM_FUNC_WITH_PARAM(cls, func, param) cls.func(param)
#define CALL_MEM_FUNC_WITH_PARAM2(cls, func, param1, param2)                   \
  cls.func(param1, param2)
#define CALL_MEM_FUNC_WITH_PARAM3(cls, func, param1, param2, param3)           \
  cls.func(param1, param2, param3)
#define CALL_MEM_FUNC_WITH_PARAM7(cls, func, param1, param2, param3, param4,   \
                                  param5, param6, param7)                      \
  cls.func(param1, param2, param3, param4, param5, param6, param7)

#endif
/*
 * Helper macro to transfer JS call directly to RtcEngine
 */
#define NAPI_API_DEFINE_WRAPPER_PARAM_0(method)                                \
  NAPI_API_DEFINE(NodeRtcEngine, method) {                                     \
    LOG_ENTER;                                                                 \
    do {                                                                       \
      NodeRtcEngine *pEngine = nullptr;                                        \
      napi_get_native_this(args, pEngine);                                     \
      CHECK_NATIVE_THIS(pEngine);                                              \
      int result = CALL_MEM_FUNC_FROM_POINTER(pEngine->m_engine, method);      \
      args.GetReturnValue().Set(Integer::New(args.GetIsolate(), result));      \
    } while (false);                                                           \
    LOG_LEAVE;                                                                 \
  }
#define NAPI_API_DEFINE_WRAPPER_PARAM_1(method, type)                          \
  NAPI_API_DEFINE(NodeRtcEngine, method) {                                     \
    LOG_ENTER;                                                                 \
    do {                                                                       \
      NodeRtcEngine *pEngine = nullptr;                                        \
      napi_get_native_this(args, pEngine);                                     \
      CHECK_NATIVE_THIS(pEngine);                                              \
      napi_status status = napi_ok;                                            \
      type param;                                                              \
      napi_get_param_1(args, type, param);                                     \
      CHECK_NAPI_STATUS(pEngine, status);                                      \
      int result = CALL_MEM_FUNC_FROM_POINTER_WITH_PARAM(pEngine->m_engine,    \
                                                         method, param);       \
      args.GetReturnValue().Set(Integer::New(args.GetIsolate(), result));      \
    } while (false);                                                           \
    LOG_LEAVE;                                                                 \
  }

#define NAPI_API_DEFINE_WRAPPER_PARAM_2(method, type, type2)                   \
  NAPI_API_DEFINE(NodeRtcEngine, method) {                                     \
    LOG_ENTER;                                                                 \
    do {                                                                       \
      NodeRtcEngine *pEngine = nullptr;                                        \
      napi_get_native_this(args, pEngine);                                     \
      CHECK_NATIVE_THIS(pEngine);                                              \
      napi_status status = napi_ok;                                            \
      type param;                                                              \
      type2 param2;                                                            \
      napi_get_param_2(args, type, param, type2, param2);                      \
      CHECK_NAPI_STATUS(pEngine, status);                                      \
      int result = CALL_MEM_FUNC_FROM_POINTER_WITH_PARAM2(                     \
          pEngine->m_engine, method, param, param2);                           \
      args.GetReturnValue().Set(Integer::New(args.GetIsolate(), result));      \
    } while (false);                                                           \
    LOG_LEAVE;                                                                 \
  }

#define NAPI_API_DEFINE_WRAPPER_PARAM_3(method, type, type2, type3)            \
  NAPI_API_DEFINE(NodeRtcEngine, method) {                                     \
    LOG_ENTER;                                                                 \
    do {                                                                       \
      NodeRtcEngine *pEngine = nullptr;                                        \
      napi_get_native_this(args, pEngine);                                     \
      CHECK_NATIVE_THIS(pEngine);                                              \
      napi_status status = napi_ok;                                            \
      type param;                                                              \
      type2 param2;                                                            \
      type3 param3;                                                            \
      napi_get_param_3(args, type, param, type2, param2, type3, param3);       \
      CHECK_NAPI_STATUS(pEngine, status);                                      \
      int result = CALL_MEM_FUNC_FROM_POINTER_WITH_PARAM3(                     \
          pEngine->m_engine, method, param, param2, param3);                   \
      args.GetReturnValue().Set(Integer::New(args.GetIsolate(), result));      \
    } while (false);                                                           \
    LOG_LEAVE;                                                                 \
  }

#define NAPI_API_DEFINE_WRAPPER_PARAM_7(method, type, type2, type3, type4,     \
                                        type5, type6, type7)                   \
  NAPI_API_DEFINE(NodeRtcEngine, method) {                                     \
    LOG_ENTER;                                                                 \
    do {                                                                       \
      NodeRtcEngine *pEngine = nullptr;                                        \
      napi_get_native_this(args, pEngine);                                     \
      CHECK_NATIVE_THIS(pEngine);                                              \
      napi_status status = napi_ok;                                            \
      type param;                                                              \
      type2 param2;                                                            \
      type3 param3;                                                            \
      type4 param4;                                                            \
      type5 param5;                                                            \
      type6 param6;                                                            \
      type7 param7;                                                            \
      napi_get_param_7(args, type, param, type2, param2, type3, param3, type4, \
                       param4, type5, param5, type6, param6, type7, param7);   \
      CHECK_NAPI_STATUS(pEngine, status);                                      \
      int result = CALL_MEM_FUNC_FROM_POINTER_WITH_PARAM7(                     \
          pEngine->m_engine, method, param, param2, param3, param4, param5,    \
          param6, param7);                                                     \
      args.GetReturnValue().Set(Integer::New(args.GetIsolate(), result));      \
    } while (false);                                                           \
    LOG_LEAVE;                                                                 \
  }

/*
 * Helper macro to transfer call directly to rtc.
 */
#define NAPI_API_DEFINE_WRAPPER_SET_PARAMETER_0(method)                        \
  NAPI_API_DEFINE(NodeRtcEngine, method) {                                     \
    LOG_ENTER;                                                                 \
    do {                                                                       \
      NodeRtcEngine *pEngine = nullptr;                                        \
      napi_get_native_this(args, pEngine);                                     \
      CHECK_NATIVE_THIS(pEngine);                                              \
      RtcEngineParameters rep(pEngine->m_engine);                              \
      int result = CALL_MEM_FUNC(rep, method);                                 \
      napi_set_int_result(args, result);                                       \
    } while (false);                                                           \
    LOG_LEAVE;                                                                 \
  }

#define NAPI_API_DEFINE_WRAPPER_SET_PARAMETER_1(method, type)                  \
  NAPI_API_DEFINE(NodeRtcEngine, method) {                                     \
    LOG_ENTER;                                                                 \
    do {                                                                       \
      NodeRtcEngine *pEngine = nullptr;                                        \
      napi_get_native_this(args, pEngine);                                     \
      CHECK_NATIVE_THIS(pEngine);                                              \
      napi_status status = napi_ok;                                            \
      type param;                                                              \
      napi_get_param_1(args, type, param);                                     \
      CHECK_NAPI_STATUS(pEngine, status);                                      \
      RtcEngineParameters rep(pEngine->m_engine);                              \
      int result = CALL_MEM_FUNC_WITH_PARAM(rep, method, param);               \
      napi_set_int_result(args, result);                                       \
    } while (false);                                                           \
    LOG_LEAVE;                                                                 \
  }

#define NAPI_API_DEFINE_WRAPPER_SET_PARAMETER_2(method, type, type2)           \
  NAPI_API_DEFINE(NodeRtcEngine, method) {                                     \
    LOG_ENTER;                                                                 \
    do {                                                                       \
      NodeRtcEngine *pEngine = nullptr;                                        \
      napi_get_native_this(args, pEngine);                                     \
      CHECK_NATIVE_THIS(pEngine);                                              \
      napi_status status = napi_ok;                                            \
      type param;                                                              \
      type2 param2;                                                            \
      napi_get_param_2(args, type, param, type2, param2);                      \
      CHECK_NAPI_STATUS(pEngine, status);                                      \
      RtcEngineParameters rep(pEngine->m_engine);                              \
      int result = CALL_MEM_FUNC_WITH_PARAM2(rep, method, param, param2);      \
      napi_set_int_result(args, result);                                       \
    } while (false);                                                           \
    LOG_LEAVE;                                                                 \
  }

#define NAPI_API_DEFINE_WRAPPER_SET_PARAMETER_3(method, type, type2, type3)    \
  NAPI_API_DEFINE(NodeRtcEngine, method) {                                     \
    LOG_ENTER;                                                                 \
    do {                                                                       \
      NodeRtcEngine *pEngine = nullptr;                                        \
      napi_get_native_this(args, pEngine);                                     \
      CHECK_NATIVE_THIS(pEngine);                                              \
      napi_status status = napi_ok;                                            \
      type param;                                                              \
      type2 param2;                                                            \
      type3 param3;                                                            \
      napi_get_param_3(args, type, param, type2, param2, type3, param3);       \
      CHECK_NAPI_STATUS(pEngine, status);                                      \
      RtcEngineParameters rep(pEngine->m_engine);                              \
      int result =                                                             \
          CALL_MEM_FUNC_WITH_PARAM3(rep, method, param, param2, param3);       \
      napi_set_int_result(args, result);                                       \
    } while (false);                                                           \
    LOG_LEAVE;                                                                 \
  }

#define NAPI_API_DEFINE_WRAPPER_SET_PARAMETER_7(method, type, type2, type3,    \
                                                type4, type5, type6, type7)    \
  NAPI_API_DEFINE(NodeRtcEngine, method) {                                     \
    LOG_ENTER;                                                                 \
    do {                                                                       \
      NodeRtcEngine *pEngine = nullptr;                                        \
      napi_get_native_this(args, pEngine);                                     \
      CHECK_NATIVE_THIS(pEngine);                                              \
      napi_status status = napi_ok;                                            \
      type param;                                                              \
      type2 param2;                                                            \
      type3 param3;                                                            \
      type4 param4;                                                            \
      type5 param5;                                                            \
      type6 param6;                                                            \
      type7 param7;                                                            \
      napi_get_param_7(args, type, param, type2, param2, type3, param3, type4, \
                       param4, type5, param5, type6, param6, type7, param7);   \
      CHECK_NAPI_STATUS(pEngine, status);                                      \
      RtcEngineParameters rep(pEngine->m_engine);                              \
      int result = CALL_MEM_FUNC_WITH_PARAM7(                                  \
          rep, method, param, param2, param3, param4, param5, param6, param7); \
      napi_set_int_result(args, result);                                       \
    } while (false);                                                           \
    LOG_LEAVE;                                                                 \
  }

} // namespace rtc
} // namespace agora

#define NAPI_API_CHANNEL_DEFINE_WRAPPER(method)                                \
  NAPI_API_DEFINE(NodeRtcChannel, method) {                                    \
    LOG_ENTER;                                                                 \
    int result = -1;                                                           \
    do {                                                                       \
      NodeRtcChannel *pChannel = nullptr;                                      \
      napi_get_native_channel(args, pChannel);                                 \
      CHECK_NATIVE_CHANNEL(pChannel);                                          \
      result = CALL_MEM_FUNC_FROM_POINTER(pChannel->m_channel, method);        \
    } while (false);                                                           \
    napi_set_int_result(args, result);                                         \
    LOG_LEAVE;                                                                 \
  }

#define NAPI_API_CHANNEL_DEFINE_WRAPPER_1(method, type)                        \
  NAPI_API_DEFINE(NodeRtcChannel, method) {                                    \
    LOG_ENTER;                                                                 \
    int result = -1;                                                           \
    do {                                                                       \
      NodeRtcChannel *pChannel = nullptr;                                      \
      napi_get_native_channel(args, pChannel);                                 \
      CHECK_NATIVE_CHANNEL(pChannel);                                          \
      napi_status status = napi_ok;                                            \
      type param;                                                              \
      napi_get_param_1(args, type, param);                                     \
      CHECK_NAPI_STATUS(pChannel, status);                                     \
      result = CALL_MEM_FUNC_FROM_POINTER_WITH_PARAM(pChannel->m_channel,      \
                                                     method, param);           \
    } while (false);                                                           \
    napi_set_int_result(args, result);                                         \
    LOG_LEAVE;                                                                 \
  }

#define NAPI_API_CHANNEL_DEFINE_WRAPPER_2(method, type, type2)                 \
  NAPI_API_DEFINE(NodeRtcChannel, method) {                                    \
    LOG_ENTER;                                                                 \
    int result = -1;                                                           \
    do {                                                                       \
      NodeRtcChannel *pChannel = nullptr;                                      \
      napi_get_native_channel(args, pChannel);                                 \
      CHECK_NATIVE_CHANNEL(pChannel);                                          \
      napi_status status = napi_ok;                                            \
      type param;                                                              \
      type2 param2;                                                            \
      napi_get_param_2(args, type, param, type2, param2);                      \
      CHECK_NAPI_STATUS(pChannel, status);                                     \
      result = CALL_MEM_FUNC_FROM_POINTER_WITH_PARAM2(pChannel->m_channel,     \
                                                      method, param, param2);  \
    } while (false);                                                           \
    napi_set_int_result(args, result);                                         \
    LOG_LEAVE;                                                                 \
  }

#define NAPI_API_CHANNEL_DEFINE_WRAPPER_3(method, type, type2, type3)          \
  NAPI_API_DEFINE(NodeRtcChannel, method) {                                    \
    LOG_ENTER;                                                                 \
    int result = -1;                                                           \
    do {                                                                       \
      NodeRtcChannel *pChannel = nullptr;                                      \
      napi_get_native_channel(args, pChannel);                                 \
      CHECK_NATIVE_CHANNEL(pChannel);                                          \
      napi_status status = napi_ok;                                            \
      type param;                                                              \
      type2 param2;                                                            \
      type3 param3;                                                            \
      napi_get_param_3(args, type, param, type2, param2, type3, param3);       \
      CHECK_NAPI_STATUS(pChannel, status);                                     \
      result = CALL_MEM_FUNC_FROM_POINTER_WITH_PARAM3(                         \
          pChannel->m_channel, method, param, param2, param3);                 \
    } while (false);                                                           \
    napi_set_int_result(args, result);                                         \
    LOG_LEAVE;                                                                 \
  }

#if defined(_WIN32)
size_t                   /* O - Length of string */
strlcpy(char *dst,       /* O - Destination string */
        const char *src, /* I - Source string */
        size_t size);    /* I - Size of destination string buffer */
#endif

#endif
