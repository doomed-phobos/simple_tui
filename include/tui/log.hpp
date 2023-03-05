#pragma once
#include "tui/system.hpp"
#include "tui/string.hpp"

namespace tui::priv {
   static void debug_printf(const tui::TextFormat& tformat, char c, const char* fmt, ...) {
      va_list args;
      va_start(args, fmt);
      instance->printf(tformat, "[%c] %s", c, format_to_str(fmt, args).c_str());
      va_end(args);
      instance->forcePaint();
   }
} // namespace tui::priv

#define INFO(...) tui::priv::debug_printf(tui::formats::kDefault_TextColor, '*', __VA_ARGS__)
#define WARNING(...) tui::priv::debug_printf(tui::formats::kLight_Yellow_TextColor, '!', __VA_ARGS__)
#define ERROR(...) tui::priv::debug_printf(tui::formats::kLight_Red_TextColor, 'X', __VA_ARGS__)