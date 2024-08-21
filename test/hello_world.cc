#include "tui/system.hpp"
// #include "tui/text_format.hpp"
#include "tui/menu.hpp"
// #include <iostream>

// using namespace tui::formats;
// #include <ncurses.h>

#include <print>

int main() {
  auto sys = tui::System::GetOrTryCreate();
  if(!sys) {
    fputs("Error al iniciar sistema", stderr);
    return 1;
  }

  tui::Menu a{
    {"Hola mundo"},
    {"Hola mundo"},
    {"Hola mundo"},
    {"Hola mundo"},
  };
  sys->draw(a);
  sys->waitKeyDown();

  return 0;
}