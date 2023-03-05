#include "tui/system.hpp"

#include "tui/string.hpp"

#include <ncurses.h>

namespace tui {
   std::shared_ptr<System> System::s_instance = nullptr;

   System::~System() {
      endwin();
   }

   void System::moveTo(const Point& pt) const {
      move(pt.y, pt.x);
   }

   Point System::getXY() const {
      return {getcurx(stdscr), getcury(stdscr)};
   }

   void System::printf(const TextFormat& tformat, const char* fmt, va_list args) const {
      attron(COLOR_PAIR(tformat.color()) | tformat.style());
      
      addstr(format_to_str(fmt, args).c_str());
      attroff(A_ATTRIBUTES);
   }

   void System::printf(const TextFormat& tformat, const char* fmt, ...) const {
      va_list args;
      va_start(args, fmt);
      this->printf(tformat, fmt, args);
      va_end(args);
   }

   void System::printf(const char* fmt, ...) const {
      va_list args;
      va_start(args, fmt);
      this->printf(formats::kDefault_TextColor, fmt, args);
      va_end(args);
   }

   void System::put(char chr, const TextFormat& tformat) const {
      addch(chr | COLOR_PAIR(tformat.color()) | tformat.style());
   }

   void System::forcePaint() const {
      refresh();
   }

   void System::clear() const {
      ::clear();
   }

   void System::replace(const Point& pt, char chr, const TextFormat& tformat) const {
      this->moveTo(pt);
      this->put(chr, tformat);
      this->moveTo(pt);
   }

   KeyCode System::waitKeyDown() const {
      return (KeyCode) getch();
   }

   System* System::GetInstance() {
      return s_instance.get();
   }

   std::shared_ptr<System> System::TryCreate() {
      if(initscr() == nullptr)
         return nullptr;
      if(keypad(stdscr, TRUE) == ERR)
         return nullptr;
      
      noecho();
      start_color();

      InitColorPairs();
      
      s_instance.reset(new System());

      return s_instance;
   }

   void System::InitColorPairs() {
      for(const auto& color : formats::colors)
         init_pair(color.color(), color.color(), COLOR_BLACK);
   }
} // namespace tui