#pragma once
#include <cstdarg>
#include <string>
#include <vector>

namespace tui {
   static std::string format_to_str(const char* fmt, va_list _args) {
      std::vector<char> buf(1, 0);
      va_list args;
      va_copy(args, _args);
      int required_size = vsnprintf(nullptr, 0, fmt, _args);
      if(required_size > 0) {
         buf.resize(required_size+1);
         vsnprintf(&buf[0], buf.size(), fmt, args);
      }

      va_end(args);

      return std::string(&buf[0]);
   }
} // namespace tui