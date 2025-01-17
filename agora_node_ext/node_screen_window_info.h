//
//  node_screen_window_info.hpp
//
//  Created by suleyu on 2018/8/8.
//  Copyright © 2018 Agora. All rights reserved.
//

#ifndef AGORA_SCREEN_WINDOW_INFO_H
#define AGORA_SCREEN_WINDOW_INFO_H

#include <string>
#include <vector>

#if defined(_WIN32)
#include <windows.h>
#endif
#define IMAGE_MAX_PIXEL_SIZE 500

#include "IAgoraRtcEngine.h"

struct ScreenDisplayInfo {;

  std::string name;
  std::string ownerName;
  unsigned int displayId;
  unsigned int width;
  unsigned int height;
  int x;
  int y;
  bool isActive;
  bool isMain;
  bool isBuiltin;

  unsigned char *imageData;
  unsigned int imageDataLength;

  ScreenDisplayInfo()
      : width(0), height(0), isActive(false), isMain(false), isBuiltin(false),
        imageData(nullptr), imageDataLength(0) {}
};

struct ScreenWindowInfo {
#if defined(__APPLE__)
  unsigned int windowId;
  int processId;
  int currentProcessId;
#elif defined(_WIN32)
  HWND windowId;
  DWORD processId;
  DWORD currentProcessId;
#endif

  std::string name;
  std::string ownerName;

  unsigned int width;
  unsigned int height;
  int x;
  int y;

  unsigned char *imageData;
  unsigned int imageDataLength;

  unsigned int originWidth;
  unsigned int originHeight;

  ScreenWindowInfo()
      : windowId(0), width(0), height(0), imageData(nullptr),
        imageDataLength(0), originWidth(0), originHeight(0) {}
};

std::vector<ScreenDisplayInfo> getAllDisplayInfo();
std::vector<ScreenWindowInfo> getAllWindowInfo();

#if defined(_WIN32)
void DestroyGdiplus();
#endif

#endif /* AGORA_SCREEN_WINDOW_INFO_H */
