#include "tui/menu.hpp"

#include "tui/system.hpp"

namespace tui {
   void Menu::update() {
      if(!hasOptions())
         return;

      draw();
      instance->forcePaint();
      event();
   }

   void Menu::draw() {
      findCurrentOption();

      for(const auto& option : m_options)
         drawOption(option);
   }

   void Menu::findCurrentOption() {
      if(!m_current_option) {
         m_current_option = &m_options.front();
         m_current_option->focus(true);
      }
   }

   void Menu::drawOption(const Option& o) {
      auto xy = instance->getXY();
      instance->moveTo(xy + Point{s_default_offset, 0});
      instance->put('[', m_text_color);
      instance->put((o.isFocused() ? '+' : ' '), m_pointer_color | formats::kBold_TextStyle);
      instance->put(']', m_text_color);
      instance->printf(m_text_color, " %s\n", o.label().c_str());
   }

   void Menu::event() {
      switch(instance->waitKeyDown()) {
         case kDownArrow_KeyCode: {
            auto it = std::next(std::vector<Option>::iterator(m_current_option));
            if(it != m_options.end()) {
               m_current_option->focus(false);
               m_current_option = &*it;
               m_current_option->focus(true);
            }
         }
         break;
         case kUpArrow_KeyCode: {
            auto it = std::next(std::vector<Option>::iterator(m_current_option), -1);
            if(it >= m_options.begin()) {
               m_current_option->focus(false);
               m_current_option = &*it;
               m_current_option->focus(true);
            }
         }
         break;
         case kEnter_KeyCode:
            m_current_option->select();
            break;
      }
   }
} // namespace tui