#pragma once
#include "tui/point.hpp"
#include "tui/text_format.hpp"
#include "tui/key.hpp"

#include <memory>
#include <cstdarg>

namespace tui {
   class System {
   public:
      ~System();

      void moveTo(const Point& pt) const; 
      Point getXY() const;

      void printf(const TextFormat& tformat, const char* fmt, ...) const;
      void printf(const char* fmt, ...) const;
      void print(const TextFormat& tformat, const char* str) const {
         this->printf(tformat, "%s", str);
      }
      void print(const char* str) const {
         this->print(formats::kDefault_TextColor, str);
      }
      void put(char chr, const TextFormat& tformat = formats::kDefault_TextColor) const;
      void replace(const Point& pt, char chr, const TextFormat& tformat = formats::kDefault_TextColor) const;
      
      void forcePaint() const;
      /*
      FIXME:
         Maybe ato use clrtobot or similar?
      */
      void clear() const;
     
      KeyCode waitKeyDown() const;

      static System* GetInstance();
      static std::shared_ptr<System> TryCreate();
   private:
      static void InitColorPairs();
      static std::shared_ptr<System> s_instance;

      void printf(const TextFormat& tformat, const char* fmt, va_list args) const;

      System() {}
   };
} // namespace tui

#define instance tui::System::GetInstance()