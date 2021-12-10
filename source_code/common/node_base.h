#pragma once
#include <node_api.h>
#include "logger.h"

namespace agora {
namespace rtc {
namespace electron {
enum ERROR_CODE {
  ERROR_OK = 0,
  ERROR_PARAMETER_1 = -1,
  ERROR_PARAMETER_2 = -2,
  ERROR_PARAMETER_3 = -3,
  ERROR_PARAMETER_4 = -4,
  ERROR_PARAMETER_5 = -5,
  ERROR_NOT_INIT = -6
};

} // namespace electron
} // namespace rtc
} // namespace agora
