#pragma once
// #include "tui/point.hpp"
// #include "tui/text_format.hpp"
#include "tui/key.hpp"

#include <memory>
#include <format>

namespace tui {
  class Menu;
  struct TextFormat;

  /// @brief Main class that initialize the library
  /// Use TryCreate function to create a System's new unique instance
  class System {
  public:
    ~System();
    
    template<typename... Args>
    void draw(const TextFormat& tfmt, std::format_string<Args...> fmt, Args&&... args) const {
      draw(tfmt, std::format(fmt, std::forward<Args>(args)...));
    }
    template<typename... Args>
    void draw(std::format_string<Args...> fmt, Args&&... args) const {
      draw(std::format(fmt, std::forward<Args>(args)...));
    }
    void draw(const TextFormat& tfmt, const std::string& text) const;
    void draw(const std::string& text) const;
    void draw(const Menu& menu) const;

    void forcePaint() const;
    /*void moveTo(const Point& pt) const; 
    Point getXY() const;

    void put(char chr, const TextFormat& tformat = formats::kDefault_TextColor) const;
    void replace(const Point& pt, char chr, const TextFormat& tformat = formats::kDefault_TextColor) const;
    
    // FIXME:
        // Maybe ato use clrtobot or similar?
    void clear() const;*/
    KeyCode waitKeyDown() const;

    static System* GetOrTryCreate();
  private:
    static std::unique_ptr<System> s_instance; 
    static void InitColorPairs();

    System() {}
  };
} // namespace tui