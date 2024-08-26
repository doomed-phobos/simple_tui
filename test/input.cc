#include "tui/system.hpp"
#include <print>

int main() {
  using namespace tui;
  auto sys = System::GetOrTryCreate();
  if(!sys) {
    fputs("Error al iniciar sistema", stderr);
    return 1;
  }
  auto str = sys->waitString(L"Holaキスの練習ちゃん_竿咥え差→分");
  // sys->draw(str);
  sys->waitKeyDown();

  return 0;
}