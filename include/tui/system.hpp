#pragma once
#include "tui/point.hpp"
#include "tui/text_format.hpp"
#include "tui/event.hpp"
#include "tui/key.hpp"

#include <memory>
#include <cstdarg>

namespace tui {
   class System {
   public:
      ~System();

      void moveTo(const Point& pt) const; 
      Point getXY() const;

      void printf(TextFormat tformat, const char* fmt, ...) const;
      void printf(const char* fmt, ...) const;
      void print(TextFormat tformat, const char* str) const {
         this->printf(tformat, "%s", str);
      }
      void print(const char* str) const {
         this->print({}, str);
      }
      void put(char chr, TextFormat tformat = {}) const;
      void replace(const Point& pt, char chr, TextFormat tformat = {}) const;
      
      void paint() const;
      void clear() const;
     
      void waitEvents(Event& ev) const;

      static System* GetInstance();
      static std::shared_ptr<System> TryCreate();
   private:
      static void InitColorPairs();
      static std::shared_ptr<System> s_instance;

      void printf(TextFormat tformat, const char* fmt, va_list args) const;

      System() {}
   };
} // namespace tui