#include "tui/system.hpp"
#include "tui/text_format.hpp"

int main() {
  auto sys = tui::System::GetOrTryCreate();
  if(!sys) {
    fputs("Error al iniciar sistema", stderr);
    return 1;
  }

  sys->draw({.position = tui::kTop_TextPosition | tui::kLeft_TextPosition}, "This\nis\na\ntest");
  sys->draw({.position = tui::kTop_TextPosition | tui::kCenter_TextPosition}, "This\nis\na\ntest");
  sys->draw({.position = tui::kTop_TextPosition | tui::kRight_TextPosition}, "This\nis\na\ntest");
  sys->draw({.position = tui::kMiddle_TextPosition | tui::kLeft_TextPosition}, "This\nis\na\ntest");
  sys->draw({.position = tui::kMiddle_TextPosition | tui::kRight_TextPosition}, "This\nis\na\ntest");
  sys->draw({.position = tui::kMiddle_TextPosition | tui::kCenter_TextPosition}, "This\nis\na\ntest");
  sys->draw({.position = tui::kBottom_TextPosition | tui::kLeft_TextPosition}, "This\nis\na\ntest");
  sys->draw({.position = tui::kBottom_TextPosition | tui::kCenter_TextPosition}, "This\nis\na\ntest");
  sys->draw({.position = tui::kBottom_TextPosition | tui::kRight_TextPosition}, "This\nis\na\ntest");
  sys->waitKeyDown();

  return 0;
}