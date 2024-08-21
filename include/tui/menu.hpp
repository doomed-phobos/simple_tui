#pragma once
// #include "tui/point.hpp"
// #include "tui/text_format.hpp"
// #include "tui/key.hpp"

#include <string>
#include <vector>

typedef struct tagMENU MENU;
typedef struct tagITEM ITEM;

namespace tui {
  class Menu {
  public:
    Menu(std::initializer_list<std::string> list);
    ~Menu();

    auto handle() const {return m_handle;}
  private:
    MENU* m_handle;
    std::vector<ITEM*> m_items;
  };
} // namespace tui