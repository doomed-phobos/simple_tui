#pragma once
#include "tui/point.hpp"

#include <memory>
#include <format>

namespace tui {
  struct TextFormat;

  /// @brief Main class that initialize the library
  /// Use TryCreate function to create a System's new unique instance
  class System {
  public:
    ~System();
    
    void clear() const;
    void clearAt(const Point& pt) const;
    void clearLineFromHere() const;
    void clearHereToEnd() const;
    template<typename... Args>
    void draw(unsigned pos, std::format_string<Args...> fmt, Args&&... args) const {
      draw(pos, std::format(fmt, std::forward<Args>(args)...));
    }
    template<typename... Args>
    void draw(std::format_string<Args...> fmt, Args&&... args) const {
      draw(std::format(fmt, std::forward<Args>(args)...));
    }
    void draw(unsigned pos, const std::string& text) const;
    void draw(const std::string& text) const;
    void drawHLine(int n = -1) const;
    void setTextFormat(const TextFormat& fmt);
    void forcePaint() const;
    void moveTo(const Point& pt) const;
    void moveTail(const Point& offset) const;

    Point currentPosition() const;
    /*void moveTo(const Point& pt) const; 

    void put(char chr, const TextFormat& tformat = formats::kDefault_TextColor) const;
    void replace(const Point& pt, char chr, const TextFormat& tformat = formats::kDefault_TextColor) const;
    
    // FIXME:
        // Maybe ato use clrtobot or similar?*/
    int width() const;
    int height() const;
    std::wstring waitString(std::wstring value = {}) const;
    int waitKeyDown() const;

    static System* GetOrTryCreate();
  private:
    static std::unique_ptr<System> s_instance; 
    static void InitColorPairs();

    System() {}
  };
} // namespace tui