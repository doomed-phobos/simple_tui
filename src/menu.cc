#include "tui/menu.hpp"

#include "tui/system.hpp"
#include <algorithm>

namespace {
   template<typename T>
   static inline const T& clamp(const T& val, const T& min, const T& max) {
      return (val > max) ? max :
             (val < min) ? min : val;
   }
}

namespace cli {
   void Menu::event(const Event& ev) {
      if(!hasOptions())
         return;

      switch(ev.keycode) {
         case kKeyCode_DownArrow: ++m_index; break;
         case kKeyCode_UpArrow: --m_index; break;
         case kKeyCode_Enter:
            m_options.at(m_index).select();
            break;
      }

      m_index = clamp<int>(m_index, 0, m_options.size() - 1);
   }

   void Menu::draw(const System* sys) {
      for(size_t i = 0; i < m_options.size(); ++i) {
         Option& option = m_options.at(i);
         auto xy = sys->getXY();
         sys->moveTo(xy + Point(s_default_offset, 0));
         sys->printf("[%c] %s\n",
            (m_index == i ? '*' : ' '),
            option.label().c_str());
      }
   }
} // namespace cli