#pragma once

namespace tui {
  enum TextPosition {
    kDefault_TextPosition = 0,

    kTop_TextPosition     = 1 << 0,
    kMiddle_TextPosition  = 1 << 1,
    kBottom_TextPosition  = 1 << 2,

    kLeft_TextPosition    = 1 << 3,
    kCenter_TextPosition  = 1 << 4,
    kRight_TextPosition   = 1 << 5,
  };
} // namespace tui  