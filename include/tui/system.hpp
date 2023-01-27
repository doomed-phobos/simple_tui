#pragma once
#include "tui/point.hpp"
#include "tui/color.hpp"
#include "tui/event.hpp"
#include "tui/key.hpp"

#include <memory>
#include <cstdarg>

namespace cli {
   class System {
   public:
      ~System();

      void moveTo(const Point& pt) const; 
      Point getXY() const;

      void printf(Color fg_color, const char* fmt, ...) const;
      void printf(const char* fmt, ...) const;
      void print(Color fg_color, const char* str) const {
         this->printf(fg_color, "%s", str);
      }
      void print(const char* str) const {
         this->print(kColor_Default, str);
      }
      void put(char chr, Color fg_color = kColor_Default) const;
      void replace(const Point& pt, char chr, Color fg_color = kColor_Default) const;
      
      void paint() const;
      void clear() const;
     
      void waitEvents(Event& ev) const;

      static System* GetInstance();
      static std::shared_ptr<System> TryCreate();
   private:
      static void InitColorPairs();
      static std::shared_ptr<System> s_instance;

      void printf(Color fg_color, const char* fmt, va_list args) const;

      System() {}
   };
} // namespace cli