/*
 * Copyright (c) 2017 Agora.io
 * All rights reserved.
 * Proprietry and Confidential -- Agora.io
 */

/*
 *  Created by Wang Yongli, 2017
 */

#ifndef AGORA_NODE_EVENT_HANDLER_H
#define AGORA_NODE_EVENT_HANDLER_H

#include "IAgoraRtcEngine.h"
#include "IAgoraRtcEngineEx.h"
#include "agora_node_ext.h"
#include "node_napi_api.h"
#include <string>
#include <unordered_map>
#include <uv.h>
namespace agora {
namespace rtc {
#define RTC_EVENT_JOIN_CHANNEL "joinchannel"
#define RTC_EVENT_REJOIN_CHANNEL "rejoinchannel"
#define RTC_EVENT_WARNING "warning"
#define RTC_EVENT_ERROR "error"
#define RTC_EVENT_AUDIO_QUALITY "audioquality"
#define RTC_EVENT_AUDIO_VOLUME_INDICATION "audiovolumeindication"
#define RTC_EVENT_LEAVE_CHANNEL "leavechannel"
#define RTC_EVENT_RTC_STATS "rtcstats"
#define RTC_EVENT_AUDIO_DEVICE_STATE_CHANGED "audiodevicestatechanged"
#define RTC_EVENT_AUDIO_MIXING_FINISHED "audiomixingfinished"
#define RTC_EVENT_REMOTE_AUDIO_MIXING_BEGIN "remoteaudiomixingbegin"
#define RTC_EVENT_REMOTE_AUDIO_MIXING_END "remoteaudiomixingend"
#define RTC_EVENT_AUDIO_EFFECT_FINISHED "audioeffectfinished"
#define RTC_EVENT_VIDEO_DEVICE_STATE_CHANGED "videodevicestatechanged"
#define RTC_EVENT_NETWORK_QUALITY "networkquality"
#define RTC_EVENT_LASTMILE_QUALITY "lastmilequality"
#define RTC_EVENT_FIRST_LOCAL_VIDEO_FRAME "firstlocalvideoframe"
#define RTC_EVENT_FIRST_REMOTE_VIDEO_DECODED "firstremotevideodecoded"
#define RTC_EVENT_VIDEO_SIZE_CHANGED "videosizechanged"
#define RTC_EVENT_REMOTE_VIDEO_STATE_CHANGED "remoteVideoStateChanged"
#define RTC_EVENT_FIRST_REMOTE_VIDEO_FRAME "firstremotevideoframe"
#define RTC_EVENT_USER_JOINED "userjoined"
#define RTC_EVENT_USER_OFFLINE "useroffline"
#define RTC_EVENT_USER_MUTE_AUDIO "usermuteaudio"
#define RTC_EVENT_USER_MUTE_VIDEO "usermutevideo"
#define RTC_EVENT_USER_ENABLE_VIDEO "userenablevideo"
#define RTC_EVENT_USER_ENABLE_LOCAL_VIDEO "userenablelocalvideo"
#define RTC_EVENT_APICALL_EXECUTED "apicallexecuted"
#define RTC_EVENT_LOCAL_VIDEO_STATS "localvideostats"
#define RTC_EVENT_LOCAL_AUDIO_STATS "localAudioStats"
#define RTC_EVENT_REMOTE_VIDEO_STATS "remotevideostats"
#define RTC_EVENT_REMOTE_AUDIO_STATS "remoteAudioStats"
#define RTC_EVENT_CAMERA_READY "cameraready"
#define RTC_EVENT_CAMERA_FOCUS_AREA_CHANGED "cameraFocusAreaChanged"
#define RTC_EVENT_CAMERA_EXPOSURE_AREA_CHANGED "cameraExposureAreaChanged"
#define RTC_EVENT_VIDEO_STOPPED "videostopped"
#define RTC_EVENT_CONNECTION_LOST "connectionlost"
#define RTC_EVENT_CONNECTION_INTERRUPTED "connectioninterrupted"
#define RTC_EVENT_CONNECTION_BANNED "connectionbanned"
#define RTC_EVENT_REFRESH_RECORDING_SERVICE_STATUS                             \
  "refreshrecordingservicestatus"
#define RTC_EVENT_STREAM_MESSAGE "streammessage"
#define RTC_EVENT_STREAM_MESSAGE_ERROR "streammessageerror"
#define RTC_EVENT_MEDIA_ENGINE_LOAD_SUCCESS "mediaengineloadsuccess"
#define RTC_EVENT_MEDIA_ENGINE_STARTCALL_SUCCESS "mediaenginestartcallsuccess"
#define RTC_EVENT_REQUEST_TOKEN "requesttoken"
#define RTC_EVENT_TOKEN_PRIVILEGE_WILL_EXPIRE "tokenPrivilegeWillExpire"
#define RTC_EVENT_FIRST_LOCAL_AUDIO_FRAME "firstlocalaudioframe"
#define RTC_EVENT_FIRST_REMOTE_AUDIO_FRAME "firstremoteaudioframe"
#define RTC_EVENT_FIRST_REMOTE_AUDIO_DECODED "firstRemoteAudioDecoded"
#define RTC_EVENT_ACTIVE_SPEAKER "activespeaker"
#define RTC_EVENT_STREAM_PUBLISHED "streamPublished"
#define RTC_EVENT_STREAM_UNPUBLISHED "streamUnpublished"
#define RTC_EVENT_TRANSCODING_UPDATED "transcodingUpdated"
#define RTC_EVENT_STREAM_INJECT_STATUS "streamInjectStatus"
#define RTC_EVENT_LOCAL_PUBLISH_FALLBACK_TO_AUDIO_ONLY                         \
  "localPublishFallbackToAudioOnly"
#define RTC_EVENT_REMOTE_SUBSCRIBE_FALLBACK_TO_AUDIO_ONLY                      \
  "remoteSubscribeFallbackToAudioOnly"
#define RTC_EVENT_CLIENT_ROLE_CHANGED "clientrolechanged"
#define RTC_EVENT_AUDIO_DEVICE_VOLUME_CHANGED "audiodevicevolumechanged"
#define RTC_EVENT_REMOTE_AUDIO_TRANSPORT_STATS "remoteAudioTransportStats"
#define RTC_EVENT_REMOTE_VIDEO_TRANSPORT_STATS "remoteVideoTransportStats"
#define RTC_EVENT_MICROPHONE_ENABLED "microphoneEnabled"
#define RTC_EVENT_CONNECTION_STATE_CHANED "connectionStateChanged"
#define RTC_EVENT_AUDIO_MIXING_STATE_CHANGED "audioMixingStateChanged"
#define RTC_EVENT_LASTMILE_PROBE_RESULT "lastmileProbeResult"
#define RTC_EVENT_LOCAL_USER_REGISTERED "localUserRegistered"
#define RTC_EVENT_USER_INFO_UPDATED "userInfoUpdated"
#define RTC_EVENT_LOCAL_VIDEO_STATE_CHANGED "localVideoStateChanged"
#define RTC_EVENT_LOCAL_AUDIO_STATE_CHANGED "localAudioStateChanged"
#define RTC_EVENT_REMOTE_AUDIO_STATE_CHANGED "remoteAudioStateChanged"
#define RTC_EVENT_CHANNEL_MEDIA_RELAY_STATE "channelMediaRelayState"
#define RTC_EVENT_CHANNEL_MEDIA_RELAY_EVENT "channelMediaRelayEvent"
#define RTC_EVENT_RTMP_STREAMING_STATE_CHANGED "rtmpStreamingStateChanged"

#define RTC_EVENT_VIDEO_SOURCE_JOIN_SUCCESS "videosourcejoinsuccess"
#define RTC_EVENT_VIDEO_SOURCE_REQUEST_NEW_TOKEN "videosourcerequestnewtoken"
#define RTC_EVENT_VIDEO_SOURCE_LEAVE_CHANNEL "videosourceleavechannel"

#define RTC_EVENT_FIRST_LOCAL_AUDIO_FRAME_PUBLISH                              \
  "firstLocalAudioFramePublished"
#define RTC_EVENT_FIRST_LOCAL_VIDEO_FRAME_PUBLISH                              \
  "firstLocalVideoFramePublished"
#define RTC_EVENT_RTMP_STREAMING_EVENT "rtmpStreamingEvent"
#define RTC_EVENT_AUDIO_PUBLISH_STATE_CHANGED "audioPublishStateChanged"
#define RTC_EVENT_VIDEO_PUBLISH_STATE_CHANGED "videoPublishStateChanged"
#define RTC_EVENT_AUDIO_SUBSCRIBE_STATE_CHANGED "audioSubscribeStateChanged"
#define RTC_EVENT_VIDEO_SUBSCRIBE_STATE_CHANGED "videoSubscribeStateChanged"
#define RTC_EVENT_AUDIO_ROUTE_CHANGED "audioRouteChanged"
#define RTC_EVENT_API_ERROR "apierror"
#define RTC_EVENT_VIDEO_FRAME_SIZE_CHANGED "videoSourceFrameSizeChanged"
#define RTC_EVENT_MEDIA_DEVICE_CHANGED "mediaDeviceChanged"
#define RTC_EVENT_EXTENSION_EVENT "extensionEvent"

class NodeRtcEngine;
class NodeUid;
class CustomRtcConnection;
class NodeEventHandler : public IRtcEngineEventHandlerEx {
public:
  struct NodeEventCallback {
    Persistent<Function> callback;
    Persistent<Object> js_this;
  };

public:
  NodeEventHandler(NodeRtcEngine *pEngine);
  ~NodeEventHandler();
  void fireApiError(const char *funcName);
  void addEventHandler(const std::string &eventName, Persistent<Object> &obj,
                       Persistent<Function> &callback);

  // send to js
  virtual void onWarning(int warn, const char *msg) override;
  virtual void onError(int err, const char *msg) override;
  virtual void onApiCallExecuted(int err, const char *api,
                                 const char *result) override;

  virtual void onAudioVolumeIndication(const RtcConnection &connection,
                                       const AudioVolumeInfo *sperkers,
                                       unsigned int speakerNumber,
                                       int totalVolume) override;
  virtual void onUserJoined(const RtcConnection &connection, uid_t remoteUid,
                            int elapsed) override;
  virtual void onUserOffline(const RtcConnection &connection, uid_t remoteUid,
                             USER_OFFLINE_REASON_TYPE reason) override;
  virtual void
  onConnectionStateChanged(const RtcConnection &connection,
                           CONNECTION_STATE_TYPE state,
                           CONNECTION_CHANGED_REASON_TYPE reason) override;
  virtual void onNetworkQuality(const RtcConnection &connection, uid_t uid,
                                int txQuality, int rxQuality) override;
  virtual void onRemoteVideoStateChanged(const RtcConnection &connection,
                                         uid_t uid, REMOTE_VIDEO_STATE state,
                                         REMOTE_VIDEO_STATE_REASON reason,
                                         int elapsed) override;
  virtual void onRemoteAudioStateChanged(const RtcConnection &connection,
                                         uid_t uid, REMOTE_AUDIO_STATE state,
                                         REMOTE_AUDIO_STATE_REASON reason,
                                         int elapsed) override;
  virtual void onJoinChannelSuccess(const RtcConnection &connection,
                                    int elapsed) override;
  virtual void
  onLocalVideoStateChanged(const RtcConnection &connection,
                           LOCAL_VIDEO_STREAM_STATE localVideoState,
                           LOCAL_VIDEO_STREAM_ERROR error) override;
  virtual void
  onLocalAudioStateChanged(const RtcConnection &connection,
                           LOCAL_AUDIO_STREAM_STATE state,
                           LOCAL_AUDIO_STREAM_ERROR error) override;
  virtual void onRtcStats(const RtcConnection &connection,
                          const RtcStats &stats) override;
  virtual void onLeaveChannel(const RtcConnection &connection,
                              const RtcStats &stats) override;
  virtual void onLocalAudioStats(const RtcConnection &connection,
                                 const LocalAudioStats &stats) override;
  virtual void onLocalVideoStats(const RtcConnection &connection,
                                 const LocalVideoStats &stats) override;
  virtual void onRemoteVideoStats(const RtcConnection &connection,
                                  const RemoteVideoStats &stats) override;
  virtual void onRemoteAudioStats(const RtcConnection &connection,
                                  const RemoteAudioStats &stats) override;
  virtual void
  onLocalPublishFallbackToAudioOnly(bool isFallbackOrRecover) override;
  virtual void
  onRemoteSubscribeFallbackToAudioOnly(uid_t uid,
                                       bool isFallbackOrRecover) override;
  virtual void onMediaDeviceChanged(int deviceType) override;
  virtual void onAudioDeviceStateChanged(const char *deviceId, int deviceType,
                                         int deviceState) override;
  virtual void onVideoDeviceStateChanged(const char *deviceId, int deviceType,
                                         int deviceState) override;

private:
private:
  std::unordered_map<std::string, NodeEventCallback *> m_callbacks;
  NodeRtcEngine *m_engine;

  void onAudioVolumeIndication_node(const CustomRtcConnection &connection,
                                    AudioVolumeInfo *sperkers,
                                    unsigned int speakerNumber,
                                    int totalVolume);
  void onRtcStats_node_with_type(const char *type,
                                 const CustomRtcConnection &connection,
                                 const RtcStats &stats);
  void onLocalAudioStats_node(const CustomRtcConnection &connection,
                              const LocalAudioStats &stats);
  void onLocalVideoStats_node(const CustomRtcConnection &connection,
                              const LocalVideoStats &stats);
  void onRemoteVideoStats_node(const CustomRtcConnection &connection,
                               const RemoteVideoStats &stats);
  void onRemoteAudioStats_node(const CustomRtcConnection &connection,
                               const RemoteAudioStats &stats);
  void sendJSWithConnection(const char *type, int count,
                            const CustomRtcConnection connection, ...);
};
} // namespace rtc
} // namespace agora

#endif
