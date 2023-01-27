#pragma once
#include "tui/key.hpp"

namespace cli {
   struct Event {
      KeyCode keycode = kKeyCode_KeyNil;
   };
} // namespace cli