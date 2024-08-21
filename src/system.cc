#include "tui/system.hpp"

#include "tui/menu.hpp"
#include "tui/text_format.hpp"

#include <ncurses.h>
#include <menu.h>

namespace tui {
  std::unique_ptr<System> System::s_instance{};

  System::~System() {
    endwin();
  }

  void System::draw(const TextFormat& tformat, const std::string& text) const {
    attron(COLOR_PAIR(tformat.color) | tformat.style);
    
    addstr(text.c_str());
    attroff(A_ATTRIBUTES);
  }

  void System::draw(const std::string& text) const {
    draw({kDefault_TextColor}, text);
  }

  void System::draw(const Menu& menu) const {
    post_menu(menu.handle());
  }

  void System::forcePaint() const {
    refresh();
  }

  KeyCode System::waitKeyDown() const {
    return (KeyCode) getch();
  }
  
  System* System::GetOrTryCreate() {
    if(s_instance) return s_instance.get();
    
    if(!initscr()) return nullptr;
    if(keypad(stdscr, TRUE) == ERR) return nullptr;

    noecho();

    start_color();

    InitColorPairs();
    
    s_instance.reset(new System());

    return s_instance.get();
  }

  void System::InitColorPairs() {
    for(int i = 0; i < kLastColor_TextColor; ++i)
        init_pair(i, i, COLOR_BLACK);
  }
  /*
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

  

  void System::clear() const {
    ::clear();
  }

  void System::replace(const Point& pt, char chr, const TextFormat& tformat) const {
    this->moveTo(pt);
    this->put(chr, tformat);
    this->moveTo(pt);
  }
  */
} // namespace tui