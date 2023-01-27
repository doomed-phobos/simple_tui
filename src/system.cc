#include "tui/system.hpp"

#include <ncurses.h>
#include <vector>

namespace {
   static std::string format(const char* fmt, va_list _args) {
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
}

namespace cli {
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

   void System::printf(Color fg_color, const char* fmt, va_list args) const {
      attron(COLOR_PAIR(fg_color));
      
      addstr(format(fmt, args).c_str());
      attroff(A_COLOR);
   }

   void System::printf(Color fg_color, const char* fmt, ...) const {
      va_list args;
      va_start(args, fmt);
      this->printf(fg_color, fmt, args);
      va_end(args);
   }

   void System::printf(const char* fmt, ...) const {
      va_list args;
      va_start(args, fmt);
      this->printf(kColor_Default, fmt, args);
      va_end(args);
   }

   void System::put(char chr, Color fg_color) const {
      addch(chr | COLOR_PAIR(fg_color));
   }

   void System::paint() const {
      refresh();
   }

   void System::clear() const {
      ::clear();
   }

   void System::replace(const Point& pt, char chr, Color fg_color) const {
      this->moveTo(pt);
      this->put(chr, fg_color);
      this->moveTo(pt);
   }

   void System::waitEvents(Event& ev) const {
      int ch = getch();
      ev.keycode = (KeyCode)ch; // FIXME: Possible bug
   }

   System* System::GetInstance() {
      return s_instance.get();
   }

   std::shared_ptr<System> System::TryCreate() {
      if(initscr() == nullptr)
         return nullptr;
      if(keypad(stdscr, TRUE) == ERR)
         return nullptr;
      
      start_color();
      noecho();

      InitColorPairs();
      
      s_instance.reset(new System());

      return s_instance;
   }

   void System::InitColorPairs() {
      for(short i = kColor_Default; i < kColor_LastColor; ++i)
         init_pair(i, i, COLOR_BLACK);
   }
} // namespace cli