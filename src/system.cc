#include "tui/system.hpp"

#include "tui/text_format.hpp"
#include "tui/text_position.hpp"
#include "tui/key.hpp"

#include <ncurses.h>
#include <algorithm>
#include <ranges>
#include <string_view>
using namespace std::literals;

namespace tui {
  std::unique_ptr<System> System::s_instance{};

  System::~System() {
    endwin();
  }

  void System::clear() const {
    ::clear();
  }

  void System::clearAt(const Point& pt) const {
    mvdelch(pt.y, pt.x);
  }

  void System::clearHereToEnd() const {
    ::clrtobot();
  }

  void System::clearLineFromHere() const {
    ::clrtoeol();
  }

  void System::draw(unsigned pos, const std::string& text) const {
    if(pos == kDefault_TextPosition) {
      addstr(text.c_str());
    } else {
      Point pt = currentPosition();
      if(const auto nlines = std::ranges::count(text, '\n') + 1; pos & kTop_TextPosition) pt.y = 0;
      else if(pos & kMiddle_TextPosition) pt.y = LINES/2 - nlines;
      else if(pos & kBottom_TextPosition) pt.y = LINES - nlines;

      if(pos & kLeft_TextPosition) pt.x = 0;
      else if(
        const auto maxlength =
        std::ranges::max(
          text
          | std::views::split('\n')
          | std::views::transform([](auto&& x) {return x.size();})
        ); pos & kCenter_TextPosition) pt.x = (COLS-maxlength)/2;
      else if(pos & kRight_TextPosition) pt.x = COLS - maxlength;

      int lines{};
      std::ranges::for_each(text | std::views::split('\n'),
        [&pt, &lines](auto&& x) {mvaddnstr(pt.y+lines++, pt.x, x.data(), x.size());}, [](auto&& x) {return std::string_view(x);});
    }
  }

  void System::draw(const std::string& text) const {
    draw(kDefault_TextPosition, text);
    
  }

  void System::forcePaint() const {
    refresh();
  }

  void System::drawHLine(int n) const {
    hline(ACS_HLINE, n > 0 ? n : COLS);
  }

  void System::moveTo(const Point& pt) const {
    move(pt.y, pt.x);
  }

  void System::moveTail(const Point& offset) const {
    move(LINES - offset.y, offset.x);
  }

  void System::setTextFormat(const TextFormat& fmt) {
    if(fmt.color != kDefault_TextColor) {
      if(fmt.color != kNone_TextColor) attron(COLOR_PAIR(fmt.color));
      else attroff(A_COLOR);
    }

    if(fmt.style != TextStyle::kDefault) {
      attroff(A_ATTRIBUTES & ~A_COLOR);
      if(fmt.style != TextStyle::kNone) attron(fmt.style);
    }
  }

  Point System::currentPosition() const {
    return {getcurx(stdscr), getcury(stdscr)};
  }

  std::wstring System::waitString(std::wstring value) const {
    const auto og = currentPosition();
    auto utf8_byte_type = [](uint8_t chr) {
      if(chr < 0x80) return 1; // ASCII
      else if(chr < 0xC0) return 0; // UTF8 continuation byte
      else if(chr >= 0xF5 || (chr & 0xFE) == 0xC0) return -1; // Invalid
      else return (((0xe5 << 24) >> ((unsigned)chr >> 4 << 1)) & 3) + 1;
    };

    // int x = value.length();
    // auto change_cursor = [&](int dir) {
      // x = std::clamp<int>(x+dir, 0, value.size());
    // };
    for(wint_t chr{}; chr != '\n';) {
      moveTo(og);
      clearLineFromHere();
      addwstr(value.c_str());
      // moveTo({og.x + x, og.y});

      switch(get_wch(&chr), chr) {
        case kBackspace_KeyCode:
          // if(!value.empty()) change_cursor(-1), value.pop_back();
          break;
        case kUpArrow_KeyCode:
        case kDownArrow_KeyCode: break;
        case kLeftArrow_KeyCode:
        case kRightArrow_KeyCode:
          // change_cursor(chr == kRightArrow_KeyCode ? +1 : -1);
          break;
        default:
          if(auto type = utf8_byte_type(chr); type >= 0) {
            moveTo({og.x, og.y+1});
            draw("{}", type);
            value.push_back(chr);
          }
          break;
      }
    }
    moveTo({0, og.y+1});

    return value;
  }

  int System::waitKeyDown() const {
    return getch();
  }

  int System::width() const {return COLS;}
  int System::height() const {return LINES;}
  
  System* System::GetOrTryCreate() {
    if(s_instance) return s_instance.get();
    
    setlocale(LC_ALL, "C.UTF-8");
    if(!initscr()) return nullptr;
    // newterm(NULL, stderr, stdin);
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