#include "tui/text_format.hpp"

#include <ncurses.h>

namespace tui {
   /*
   FIXME:
      For me, who use a few of menus this function isn't causing me any performance problem.

      Performance pseudo-analysis in 5 options:
         *) Without: 63.6 ms
         *) With:    89 ms
      
      Maybe to define TextStyle in compilation-time?
      Maybe to use a tui thread?
   */
   static constexpr inline unsigned convert_from_ncurses(int style) {
      int ncurses_style = 0;

      if(style != kDefault_TextStyle) {
         if(style & kBold_TextStyle)
            ncurses_style |= A_BOLD;
         if(style & kDim_TextStyle)
            ncurses_style |= A_DIM;
      } else {
         ncurses_style = A_NORMAL;
      }
      
      return ncurses_style;
   }

   TextFormat::TextFormat() :
      TextFormat{kDefault_TextColor, kDefault_TextStyle} {}
   TextFormat::TextFormat(TextColor color) :
      TextFormat{color, kDefault_TextStyle} {}
   TextFormat::TextFormat(TextColor color, unsigned style) :
      m_color{color}, m_style{convert_from_ncurses(style)} {}
} // namespace tui