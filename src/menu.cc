#include "tui/menu.hpp"

#include <menu.h>
#include <algorithm>
#include <utility>
#include <ranges>

namespace tui {
  Menu::Menu(std::initializer_list<std::string> list) :
    m_options{list.begin(), list.end()},
    m_items{m_options | std::views::transform(&Option::handle) | std::ranges::to<std::vector<ITEM*>>()} {
    m_items.push_back(nullptr);
    m_handle = new_menu(&m_items[0]);
  }

  Menu::~Menu() {
    if(m_handle) free_menu(m_handle);
  }
  
  /*void Menu::build() {
    if(!hasOptions())
        return;

    findCurrentOption();
  }

  void Menu::findCurrentOption() {
    for(auto& option : m_options) {
        if(option.isEnabled()) {
          m_current_option = &option;
          m_current_option->focus(true);
          break;
        }
    }
  }

  void Menu::draw() {
    if(!m_current_option)
        return;

    for(const auto& option : m_options)
        drawOption(option);
  }

  void Menu::drawOption(const Option& o) {
    auto xy = instance->getXY();
    
    uint32_t style = o.isEnabled() ? 0 : formats::kDim_TextStyle;

    instance->moveTo(xy + Point{s_default_offset, 0});
    instance->put('[', m_text_color | style);
    instance->put((o.isFocused() ? '+' : ' '), m_pointer_color | formats::kBold_TextStyle);
    instance->put(']', m_text_color | style);
    instance->printf(m_text_color | style, " %s\n", o.label().c_str());
  }

  void Menu::event(const KeyCode& key) {
    if(!m_current_option)
        return;

    switch(key) {
        case kDownArrow_KeyCode: {
          for(auto it = ++std::vector<Option>::iterator(m_current_option); it != m_options.end(); ++it) {
              if(it->isEnabled()) {
                m_current_option->focus(false);
                m_current_option = &*it;
                m_current_option->focus(true);
                break;
              } else {
                continue;
              }
          }
        }
        break;
        case kUpArrow_KeyCode: {
          for(auto it = --std::vector<Option>::iterator(m_current_option); it >= m_options.begin(); --it) {
              if(it->isEnabled()) {
                m_current_option->focus(false);
                m_current_option = &*it;
                m_current_option->focus(true);
                break;
              } else {
                continue;
              }
          }
        }
        break;
        case kEnter_KeyCode:
          m_current_option->select();
          break;
    }
  }*/
} // namespace tui