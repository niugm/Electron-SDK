#ifndef AGORA_SCREEN_WINDOW_INFO_H
#define AGORA_SCREEN_WINDOW_INFO_H

#include <string>
#include <vector>
#include "IAgoraRtcEngine.h"

#if defined(_WIN32)
#include <windows.h>
#endif
#define IMAGE_MAX_PIXEL_SIZE 500

#if defined(__APPLE__)
struct DisplayID {
  unsigned int idVal;

  DisplayID() : idVal(0) {}
};
typedef DisplayID ScreenIDType;
#elif defined(_WIN32)
typedef agora::rtc::Rectangle ScreenIDType;
#endif

typedef struct DisplayInfo {
  DisplayInfo() : idVal(0) {}
  unsigned int idVal;
} DisplayInfo;
struct ScreenDisplayInfo {
  ScreenIDType displayId;
  DisplayInfo displayInfo;

  std::string name;
  std::string ownerName;

  unsigned int width;
  unsigned int height;
  int x;
  int y;
  bool isActive;
  bool isMain;
  bool isBuiltin;

  unsigned char* imageData;
  unsigned int imageDataLength;

  ScreenDisplayInfo()
      : width(0),
        height(0),
        isActive(false),
        isMain(false),
        isBuiltin(false),
        imageData(nullptr),
        imageDataLength(0) {}
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

  unsigned char* imageData;
  unsigned int imageDataLength;

  unsigned int originWidth;
  unsigned int originHeight;

  ScreenWindowInfo()
      : windowId(0),
        width(0),
        height(0),
        imageData(nullptr),
        imageDataLength(0),
        originWidth(0),
        originHeight(0) {}
};

std::vector<ScreenDisplayInfo> getAllDisplayInfo();
std::vector<ScreenWindowInfo> getAllWindowInfo();

#if defined(_WIN32)
void DestroyGdiplus();
#endif

#endif /* AGORA_SCREEN_WINDOW_INFO_H */