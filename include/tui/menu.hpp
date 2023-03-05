#pragma once
#include "tui/point.hpp"
#include "tui/text_format.hpp"
#include "tui/key.hpp"

#include <string>
#include <functional>
#include <vector>

namespace tui {
   class System;

   class Menu {
   public:
      class Option {
      public:
         typedef std::function<void(Option&)> Listener;

         Option(const char* label) :
            m_label{label},
            m_listener{nullptr},
            m_focused{false} {}
         
         Option& setOnListener(Listener&& l) {m_listener = std::move(l); return *this;}
         bool isFocused() const {return m_focused;}
         void select() {if(m_listener) m_listener(*this);}
         
         const std::string& label() const {return m_label;}
      private:
         friend class Menu;
         void focus(bool b) {m_focused = b;}
         
         std::string m_label;
         Listener m_listener;
         bool m_focused;
      };

      Menu() :
         m_text_color{s_default_text_color},
         m_pointer_color{s_default_pointer_color},
         m_offset{s_default_offset},
         m_current_option{nullptr} {}

      void setOffset(ushort offset) {m_offset = offset;}
      void setTextColor(const TextFormat& color) {m_text_color = color;}
      void setPointerColor(const TextFormat& color) {m_pointer_color = color;}

      Option& addOption(const char* label) {
         m_options.emplace_back(label);
         return m_options.back();
      }
      bool hasOptions() const {return !m_options.empty();}

      void update();
   private:
      static constexpr inline const ushort s_default_offset = 3;
      static constexpr inline const TextFormat& s_default_text_color = formats::kDefault_TextColor;
      static constexpr inline const TextFormat& s_default_pointer_color = formats::kYellow_TextColor;
      void findCurrentOption();
      void drawOption(const Option& o);
      
      void event();
      void draw();

      TextFormat m_text_color;
      TextFormat m_pointer_color;
      Option* m_current_option;
      ushort m_offset {s_default_offset};
      std::vector<Option> m_options;
   };
} // namespace tui