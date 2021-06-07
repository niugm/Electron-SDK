/*
 * @Author: zhangtao@agora.io
 * @Date: 2021-04-22 11:36:26
 * @Last Modified by: zhangtao@agora.io
 * @Last Modified time: 2021-05-11 11:59:59
 */

export enum ApiTypeEngine {
  kEngineInitialize,
  kEngineRelease,
  kEngineSetChannelProfile,
  kEngineSetClientRole,
  kEngineJoinChannel,
  kEngineSwitchChannel,
  kEngineLeaveChannel,
  kEngineRenewToken,
  kEngineRegisterLocalUserAccount,
  kEngineJoinChannelWithUserAccount,
  kEngineGetUserInfoByUserAccount,
  kEngineGetUserInfoByUid,
  kEngineStartEchoTest,
  kEngineStopEchoTest,
  kEngineSetCloudProxy,
  kEngineEnableVideo,
  kEngineDisableVideo,
  kEngineSetVideoProfile,
  kEngineSetVideoEncoderConfiguration,
  kEngineSetCameraCapturerConfiguration,
  kEngineSetupLocalVideo,
  kEngineSetupRemoteVideo,
  kEngineStartPreview,
  kEngineSetRemoteUserPriority,
  kEngineStopPreview,
  kEngineEnableAudio,
  kEngineEnableLocalAudio,
  kEngineDisableAudio,
  kEngineSetAudioProfile,
  kEngineMuteLocalAudioStream,
  kEngineMuteAllRemoteAudioStreams,
  kEngineSetDefaultMuteAllRemoteAudioStreams,
  kEngineAdjustUserPlaybackSignalVolume,
  kEngineMuteRemoteAudioStream,
  kEngineMuteLocalVideoStream,
  kEngineEnableLocalVideo,
  kEngineMuteAllRemoteVideoStreams,
  kEngineSetDefaultMuteAllRemoteVideoStreams,
  kEngineMuteRemoteVideoStream,
  kEngineSetRemoteVideoStreamType,
  kEngineSetRemoteDefaultVideoStreamType,
  kEngineEnableAudioVolumeIndication,
  kEngineStartAudioRecording,
  kEngineStopAudioRecording,
  kEngineStartAudioMixing,
  kEngineStopAudioMixing,
  kEnginePauseAudioMixing,
  kEngineResumeAudioMixing,
  kEngineSetHighQualityAudioParameters,
  kEngineAdjustAudioMixingVolume,
  kEngineAdjustAudioMixingPlayoutVolume,
  kEngineGetAudioMixingPlayoutVolume,
  kEngineAdjustAudioMixingPublishVolume,
  kEngineGetAudioMixingPublishVolume,
  kEngineGetAudioMixingDuration,
  kEngineGetAudioMixingCurrentPosition,
  kEngineSetAudioMixingPosition,
  kEngineSetAudioMixingPitch,
  kEngineGetEffectsVolume,
  kEngineSetEffectsVolume,
  kEngineSetVolumeOfEffect,
  kEngineEnableFaceDetection,
  kEnginePlayEffect,
  kEngineStopEffect,
  kEngineStopAllEffects,
  kEnginePreloadEffect,
  kEngineUnloadEffect,
  kEnginePauseEffect,
  kEnginePauseAllEffects,
  kEngineResumeEffect,
  kEngineResumeAllEffects,
  kEngineGetEffectDuration,
  kEngineSetEffectPosition,
  kEngineGetEffectCurrentPosition,
  kEngineEnableDeepLearningDenoise,
  kEngineEnableSoundPositionIndication,
  kEngineSetRemoteVoicePosition,
  kEngineSetLocalVoicePitch,
  kEngineSetLocalVoiceEqualization,
  kEngineSetLocalVoiceReverb,
  kEngineSetLocalVoiceChanger,
  kEngineSetLocalVoiceReverbPreset,
  kEngineSetVoiceBeautifierPreset,
  kEngineSetAudioEffectPreset,
  kEngineSetVoiceConversionPreset,
  kEngineSetAudioEffectParameters,
  kEngineSetVoiceBeautifierParameters,
  kEngineSetLogFile,
  kEngineSetLogFilter,
  kEngineSetLogFileSize,
  kEngineUploadLogFile,
  kEngineSetLocalRenderMode,
  kEngineSetRemoteRenderMode,
  kEngineSetLocalVideoMirrorMode,
  kEngineEnableDualStreamMode,
  kEngineSetExternalAudioSource,
  kEngineSetExternalAudioSink,
  kEngineSetRecordingAudioFrameParameters,
  kEngineSetPlaybackAudioFrameParameters,
  kEngineSetMixedAudioFrameParameters,
  kEngineAdjustRecordingSignalVolume,
  kEngineAdjustPlaybackSignalVolume,
  kEngineAdjustLoopbackRecordingSignalVolume,
  kEngineEnableWebSdkInteroperability,
  kEngineSetVideoQualityParameters,
  kEngineSetLocalPublishFallbackOption,
  kEngineSetRemoteSubscribeFallbackOption,
  kEngineSwitchCamera,
  kEngineSetDefaultAudioRouteToSpeakerPhone,
  kEngineSetEnableSpeakerPhone,
  kEngineEnableInEarMonitoring,
  kEngineSetInEarMonitoringVolume,
  kEngineIsSpeakerPhoneEnabled,
  kEngineSetAudioSessionOperationRestriction,
  kEngineEnableLoopBackRecording,
  kEngineStartScreenCaptureByDisplayId,
  kEngineStartScreenCaptureByScreenRect,
  kEngineStartScreenCaptureByWindowId,
  kEngineSetScreenCaptureContentHint,
  kEngineUpdateScreenCaptureParameters,
  kEngineUpdateScreenCaptureRegion,
  kEngineStopScreenCapture,
  kEngineStartScreenCapture,
  kEngineSetVideoSource,
  kEngineGetCallId,
  kEngineRate,
  kEngineComplain,
  kEngineGetVersion,
  kEngineEnableLastMileTest,
  kEngineDisableLastMileTest,
  kEngineStartLastMileProbeTest,
  kEngineStopLastMileProbeTest,
  kEngineGetErrorDescription,
  kEngineSetEncryptionSecret,
  kEngineSetEncryptionMode,
  kEngineEnableEncryption,
  kEngineRegisterPacketObserver,
  kEngineCreateDataStream,
  kEngineSendStreamMessage,
  kEngineAddPublishStreamUrl,
  kEngineRemovePublishStreamUrl,
  kEngineSetLiveTranscoding,
  kEngineAddVideoWaterMark,
  kEngineClearVideoWaterMarks,
  kEngineSetBeautyEffectOptions,
  kEngineAddInjectStreamUrl,
  kEngineStartChannelMediaRelay,
  kEngineUpdateChannelMediaRelay,
  kEngineStopChannelMediaRelay,
  kEngineRemoveInjectStreamUrl,
  kEngineSendCustomReportMessage,
  kEngineGetConnectionState,
  kEngineEnableRemoteSuperResolution,
  kEngineRegisterMediaMetadataObserver,
  kEngineSetParameters,

  kEngineUnRegisterMediaMetadataObserver,
  kEngineSetMaxMetadataSize,
  kEngineSendMetadata,
  kEngineSetAppType,

  kMediaPushAudioFrame,
  kMediaPullAudioFrame,
  kMediaSetExternalVideoSource,
  kMediaPushVideoFrame,
}

export enum ApiTypeChannel {
  kChannelCreateChannel,
  kChannelRelease,
  kChannelJoinChannel,
  kChannelJoinChannelWithUserAccount,
  kChannelLeaveChannel,
  kChannelPublish,
  kChannelUnPublish,
  kChannelChannelId,
  kChannelGetCallId,
  kChannelRenewToken,
  kChannelSetEncryptionSecret,
  kChannelSetEncryptionMode,
  kChannelEnableEncryption,
  kChannelRegisterPacketObserver,
  kChannelRegisterMediaMetadataObserver,
  kChannelUnRegisterMediaMetadataObserver,
  kChannelSetMaxMetadataSize,
  kChannelSendMetadata,
  kChannelSetClientRole,
  kChannelSetRemoteUserPriority,
  kChannelSetRemoteVoicePosition,
  kChannelSetRemoteRenderMode,
  kChannelSetDefaultMuteAllRemoteAudioStreams,
  kChannelSetDefaultMuteAllRemoteVideoStreams,
  kChannelMuteAllRemoteAudioStreams,
  kChannelAdjustUserPlaybackSignalVolume,
  kChannelMuteRemoteAudioStream,
  kChannelMuteAllRemoteVideoStreams,
  kChannelMuteRemoteVideoStream,
  kChannelSetRemoteVideoStreamType,
  kChannelSetRemoteDefaultVideoStreamType,
  kChannelCreateDataStream,
  kChannelSendStreamMessage,
  kChannelAddPublishStreamUrl,
  kChannelRemovePublishStreamUrl,
  kChannelSetLiveTranscoding,
  kChannelAddInjectStreamUrl,
  kChannelRemoveInjectStreamUrl,
  kChannelStartChannelMediaRelay,
  kChannelUpdateChannelMediaRelay,
  kChannelStopChannelMediaRelay,
  kChannelGetConnectionState,
  kChannelEnableRemoteSuperResolution,
}

export enum ApiTypeAudioDeviceManager {
  kADMEnumeratePlaybackDevices,

  kADMSetPlaybackDevice,
  kADMGetPlaybackDevice,
  kADMGetPlaybackDeviceInfo,
  kADMSetPlaybackDeviceVolume,
  kADMGetPlaybackDeviceVolume,
  kADMSetPlaybackDeviceMute,
  kADMGetPlaybackDeviceMute,
  kADMStartPlaybackDeviceTest,
  kADMStopPlaybackDeviceTest,

  kADMEnumerateRecordingDevices,
  kADMSetRecordingDevice,
  kADMGetRecordingDevice,
  kADMGetRecordingDeviceInfo,
  kADMSetRecordingDeviceVolume,
  kADMGetRecordingDeviceVolume,
  kADMSetRecordingDeviceMute,
  kADMGetRecordingDeviceMute,
  kADMStartRecordingDeviceTest,
  kADMStopRecordingDeviceTest,

  kADMStartAudioDeviceLoopbackTest,
  kADMStopAudioDeviceLoopbackTest,
}

export enum ApiTypeVideoDeviceManager {
  kVDMEnumerateVideoDevices,
  
  kVDMSetDevice,
  kVDMGetDevice,
  kVDMStartDeviceTest,
  kVDMStopDeviceTest,
}

export enum ApiTypeRawDataPluginManager {
  kRDPMRegisterPlugin,
  kRDPMUnregisterPlugin,
  kRDPMHasPlugin,
  kRDPMEnablePlugin,
  kRDPMGetPlugins,
  kRDPMSetPluginParameter,
  kRDPMGetPluginParameter,
  kRDPMRelease
}

export enum PROCESS_TYPE {
  MAIN,
  SCREEN_SHARE
}

export interface Result {
  retCode: number;
  result: string;
}
export enum AUDIO_RECORDING_QUALITY_TYPE
{
    /** 0: Low quality. The sample rate is 32 kHz, and the file size is around
     * 1.2 MB after 10 minutes of recording.
    */
    AUDIO_RECORDING_QUALITY_LOW = 0,
    /** 1: Medium quality. The sample rate is 32 kHz, and the file size is
     * around 2 MB after 10 minutes of recording.
    */
    AUDIO_RECORDING_QUALITY_MEDIUM = 1,
    /** 2: High quality. The sample rate is 32 kHz, and the file size is
     * around 3.75 MB after 10 minutes of recording.
    */
    AUDIO_RECORDING_QUALITY_HIGH = 2,
}

export enum AUDIO_RECORDING_POSITION {
  /** The SDK will record the voices of all users in the channel. */
  AUDIO_RECORDING_POSITION_MIXED_RECORDING_AND_PLAYBACK = 0,
  /** The SDK will record the voice of the local user. */
  AUDIO_RECORDING_POSITION_RECORDING = 1,
  /** The SDK will record the voices of remote users. */
  AUDIO_RECORDING_POSITION_MIXED_PLAYBACK = 2,
};

export interface AudioRecordingConfiguration {
  filePath: string;
  recordingQuality: AUDIO_RECORDING_QUALITY_TYPE;
  recordingPosition: AUDIO_RECORDING_POSITION;
}
