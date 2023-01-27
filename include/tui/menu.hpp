#pragma once
#include "tui/point.hpp"
#include "tui/color.hpp"

#include <vector>
#include <string>
#include <functional>

namespace cli {
   class System;
   class Event;

   class Menu {
   public:
      class Option {
      public:
         typedef std::function<void()> Listener;
         
         Option(const char* text) :
            m_text{text},
            m_selected{false} {}
      
         void setOnSelected(Listener&& l) {m_listener = std::move(l);}
         bool isSelected() const {return m_selected;}
      
         const std::string& text() const {return m_text;}
      private:
         friend class Menu;
      
         void isSelected(bool selected) {m_selected = selected;}
         void select() const {if(m_listener) m_listener();}
         Listener m_listener;
         bool m_selected;
         std::string m_text;
      };

      Menu(const Point& offset = {0, 0}, Color selector_color = kColor_Default);

      Option& addOption(const char* text) {
         m_options.emplace_back(text);
         return m_options.back();
      }

      void event(const Event& ev);
      /// Required paint
      void draw(const System* sys) const;
   private:
      int m_index;
      Point m_offset;
      Color m_selector_color;
      std::vector<Option> m_options;
   };
} // namespace cli