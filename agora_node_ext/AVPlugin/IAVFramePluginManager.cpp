#include "IAVFramePluginManager.h"
#include "IAVFramePlugin.h"
#include <stdint.h>
#include <stdio.h>

using namespace agora::media::base;

IAVFramePluginManager::IAVFramePluginManager() {}

IAVFramePluginManager::~IAVFramePluginManager() {}

bool IAVFramePluginManager::onCaptureVideoFrame(VideoFrame &videoFrame) {
  for (auto const &element : m_mapPlugins) {
    if (element.second.enabled) {
      element.second.instance->onPluginCaptureVideoFrame(
          (VideoPluginFrame *)&videoFrame);
    }
  }

  return true;
}

bool IAVFramePluginManager::onRenderVideoFrame(
    agora::rtc::uid_t uid, agora::rtc::conn_id_t connectionId,
    VideoFrame &videoFrame) {
  return true;
}

bool IAVFramePluginManager::onTranscodedVideoFrame(
    agora::media::IVideoFrameObserver::VideoFrame &videoFrame) {
  return true;
}

bool IAVFramePluginManager::onScreenCaptureVideoFrame(VideoFrame &videoFrame) {
  return true;
}

bool IAVFramePluginManager::onRecordAudioFrame(const char *channelId,
                                               AudioFrame &audioFrame) {
  return true;
}

bool IAVFramePluginManager::onPlaybackAudioFrame(const char *channelId,
                                                 AudioFrame &audioFrame) {
  return true;
}

bool IAVFramePluginManager::onMixedAudioFrame(const char *channelId,
                                              AudioFrame &audioFrame) {
  return true;
}

bool IAVFramePluginManager::onPlaybackAudioFrameBeforeMixing(
    const char *channelId, agora::rtc::uid_t userId,
    agora::media::IAudioFrameObserver::AudioFrame &audioFrame) {
  return true;
}

void IAVFramePluginManager::registerPlugin(agora_plugin_info &plugin) {
  m_mapPlugins.emplace(plugin.id, plugin);
}

void IAVFramePluginManager::unregisterPlugin(std::string &pluginId) {
  auto iter = m_mapPlugins.find(pluginId);
  if (iter != m_mapPlugins.end()) {
    // free plugin instance
    if (iter->second.instance) {
      iter->second.instance->release();
    }
    // unload libs
    if (iter->second.pluginModule) {
#ifdef WIN32
      FreeLibrary((HMODULE)(iter->second.pluginModule));
#else
      dlclose(iter->second.pluginModule);
#endif
    }
    m_mapPlugins.erase(iter);
  }
}

bool IAVFramePluginManager::hasPlugin(std::string &pluginId) {
  return m_mapPlugins.end() != m_mapPlugins.find(pluginId);
}

bool IAVFramePluginManager::enablePlugin(std::string &pluginId, bool enabled) {
  auto iter = m_mapPlugins.find(pluginId);
  if (iter != m_mapPlugins.end()) {
    iter->second.enabled = enabled;
    return true;
  }
  return false;
}

bool IAVFramePluginManager::getPlugin(std::string &pluginId,
                                      agora_plugin_info &pluginInfo) {
  auto iter = m_mapPlugins.find(pluginId);
  if (iter != m_mapPlugins.end()) {
    pluginInfo = iter->second;
    return true;
  }
  return false;
}

std::vector<std::string> IAVFramePluginManager::getPlugins() {
  std::vector<std::string> result;
  for (auto const &element : m_mapPlugins) {
    result.push_back(element.first);
  }
  return result;
}

int IAVFramePluginManager::release() {
  for (auto const &element : m_mapPlugins) {
    // free plugin instance
    if (element.second.instance) {
      element.second.instance->release();
    }
    // unload libs
    if (element.second.pluginModule) {
#ifdef WIN32
      FreeLibrary((HMODULE)(element.second.pluginModule));
#else
      dlclose(element.second.pluginModule);
#endif
    }
  }
  return 0;
}
