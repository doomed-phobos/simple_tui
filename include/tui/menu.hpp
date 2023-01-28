#pragma once
#include "tui/point.hpp"
#include "tui/color.hpp"

#include <string>
#include <functional>
#include <vector>

namespace cli {
   class System;
   class Event;

   class Menu {
   public:
      class Option {
      public:
         typedef std::function<void()> Listener;

         Option(const char* label) :
            m_label{label},
            m_listener(nullptr) {}
         
         const std::string& label() const {return m_label;}
         void setOnListener(Listener&& l) {m_listener = std::move(l);}
         void select() {if(m_listener) m_listener();}
      private:
         std::string m_label;
         Listener m_listener;
      };

      Menu() :
         m_index{0} {}

      Option& addOption(const char* label) {
         m_options.emplace_back(label);
         return m_options.back();
      }
      bool hasOptions() const {return !m_options.empty();}

      void event(const Event& ev);
      void draw(const System* sys);
   private:
      static constexpr inline const ushort s_default_offset = 3;

      int m_index;
      std::vector<Option> m_options;
   };
} // namespace cli