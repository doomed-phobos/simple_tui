#pragma once
#include "tui/key.hpp"

namespace tui {
   struct Event {
      KeyCode keycode = kKeyNil_KeyCode;
   };
} // namespace tui