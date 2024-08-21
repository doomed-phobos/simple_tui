#include "tui/text_format.hpp"

#include <ncurses.h>

namespace tui {
  const unsigned TextStyle::kNone      = 0;
  const unsigned TextStyle::kDefault   = 1;
  const unsigned TextStyle::kUnderline = A_UNDERLINE;
  const unsigned TextStyle::kReverse   = A_REVERSE;
  const unsigned TextStyle::kBlink     = A_BLINK;
  const unsigned TextStyle::kDim       = A_DIM;
  const unsigned TextStyle::kBold      = A_BOLD;
} // namespace tui