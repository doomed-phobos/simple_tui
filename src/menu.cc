#include "tui/menu.hpp"

#include "tui/system.hpp"
#include <algorithm>

namespace tui {
   Menu::Menu(TextColor text_color, TextColor pointer_color) :
      m_text_color{text_color},
      m_pointer_color{pointer_color},
      m_current_option{nullptr} {} 

   void Menu::event(const Event& ev) {
      if(!hasOptions() || !m_current_option)
         return;
      
      switch(ev.keycode) {
         case kDownArrow_KeyCode: {
         // FIXME: Possible bug?
            for(auto it = std::vector<Option>::iterator(m_current_option); ++it < m_options.end();) {
               if(it->isEnabled()) {
                  m_current_option->focus(false);
                  m_current_option = &(*it);
                  m_current_option->focus(true);
                  break;
               }
            }
         }
            break;
         case kUpArrow_KeyCode: {
         // FIXME: Possible bug?
            for(auto it = std::vector<Option>::iterator(m_current_option); --it >= m_options.begin();) {
               if(it->isEnabled()) {
                  m_current_option->focus(false);
                  m_current_option = &(*it);
                  m_current_option->focus(true);
                  break;
               }
            }
            break;
         }
         case kEnter_KeyCode:
            m_current_option->select();
            break;
      }
   }

   void Menu::draw(const System* sys) {
      findCurrentOption();
      
      for(const auto& option : m_options)
         drawOption(option, sys);
   }

   void Menu::findCurrentOption() {
      if(m_current_option)
         return;

      for(auto& option : m_options) {
         if(option.isEnabled()) {
            m_current_option = &option;
            m_current_option->focus(true);
            return;
         }
      }
      m_current_option = m_options.data() + m_options.size();
   }

   void Menu::drawOption(const Option& o, const System* sys) {
      auto xy = sys->getXY();
      TextFormat text_format{m_text_color, (o.isEnabled() ? kDefault_TextStyle : kDim_TextStyle)};
      sys->moveTo(xy + Point{s_default_offset, 0});
      sys->put('[', text_format);
      sys->put((o.isFocused() ? '*' : ' '), {m_pointer_color, kBold_TextStyle});
      sys->put(']', text_format);
      sys->printf(text_format, " %s\n", o.label().c_str());
   }
} // namespace tui