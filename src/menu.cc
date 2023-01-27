#include "tui/menu.hpp"

#include "tui/system.hpp"
#include <algorithm>

namespace {
   static int clamp(int val, int min, int max) {
      return val > max ? max :
             val < min ? min : val;
   }
}

namespace cli {
   Menu::Menu(const Point& offset, Color selector_color) :
      m_index{0},
      m_offset{offset},
      m_selector_color{selector_color} {}
 
   void Menu::event(const Event& ev) {
      if(m_options.empty())
         return;

      switch(ev.keycode) {
         case kKeyCode_DownArrow:
            m_options.at(m_index).isSelected(false);
            ++m_index;
            break;
         case kKeyCode_UpArrow:
            m_options.at(m_index).isSelected(false);
            --m_index;
            break;
         case kKeyCode_Enter:
            m_options.at(m_index).select();
            break;
      }

      m_index = clamp(m_index, 0, (int)m_options.size() - 1);
      m_options.at(m_index).isSelected(true);
   }

   void Menu::draw(const System* sys) const {
      auto xy = sys->getXY();

      sys->moveTo(xy + Point(0U, m_offset.y));

      for(const auto& option : m_options) {
         xy = sys->getXY();
         sys->moveTo(xy + Point(m_offset.x, 0));
         sys->put('[');
         sys->put(option.isSelected() ? '*' : ' ', m_selector_color);
         sys->printf("] %s\n", option.text().c_str());
      }
   }
} // namespace cli