#pragma once
#include "tui/point.hpp"
#include "tui/text_format.hpp"

#include <string>
#include <functional>
#include <vector>

namespace tui {
   class System;
   class Event;

   class Menu {
   public:
      class Option {
      public:
         typedef std::function<void()> Listener;

         Option(const char* label) :
            m_label{label},
            m_listener{nullptr},
            m_focused{false},
            m_enabled{true} {}
         
         void setOnListener(Listener&& l) {m_listener = std::move(l);}
         void enable(bool b) {m_enabled = b;}
         void focus(bool b) {if(isEnabled()) m_focused = b;}
         bool isFocused() const {return m_focused;}
         void select() {if(isEnabled() && m_listener) m_listener();}
         
         const std::string& label() const {return m_label;}
         bool isEnabled() const {return m_enabled;}
      private:
         std::string m_label;
         Listener m_listener;
         bool m_enabled;
         bool m_focused;
      };

      Menu(TextColor text_color = s_default_text_color, TextColor pointer_color = s_default_pointer_color);

      void setOffset(ushort offset) {m_offset = offset;}

      Option& addOption(const char* label) {
         m_options.emplace_back(label);
         return m_options.back();
      }
      bool hasOptions() const {return !m_options.empty();}

      void event(const Event& ev);
      void draw(const System* sys);
   private:
      static constexpr inline const ushort s_default_offset = 3;
      static constexpr inline const TextColor s_default_text_color = kDefault_TextColor;
      static constexpr inline const TextColor s_default_pointer_color = kYellow_TextColor;
      void findCurrentOption();
      void drawOption(const Option& o, const System* sys);

      TextColor m_text_color;
      TextColor m_pointer_color;
      Option* m_current_option;
      ushort m_offset {s_default_offset};
      std::vector<Option> m_options;
   };
} // namespace tui