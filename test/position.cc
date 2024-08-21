#include "tui/system.hpp"
#include "tui/text_position.hpp"

int main() {
  auto sys = tui::System::GetOrTryCreate();
  if(!sys) {
    fputs("Error al iniciar sistema", stderr);
    return 1;
  }

  sys->draw(tui::kTop_TextPosition | tui::kLeft_TextPosition, "This\nis\na\ntest");
  sys->draw(tui::kTop_TextPosition | tui::kCenter_TextPosition, "This\nis\na\ntest");
  sys->draw(tui::kTop_TextPosition | tui::kRight_TextPosition, "This\nis\na\ntest");
  sys->draw(tui::kMiddle_TextPosition | tui::kLeft_TextPosition, "This\nis\na\ntest");
  sys->draw(tui::kMiddle_TextPosition | tui::kRight_TextPosition, "This\nis\na\ntest");
  sys->draw(tui::kMiddle_TextPosition | tui::kCenter_TextPosition, "This\nis\na\ntest");
  sys->draw(tui::kBottom_TextPosition | tui::kLeft_TextPosition, "This\nis\na\ntest");
  sys->draw(tui::kBottom_TextPosition | tui::kCenter_TextPosition, "This\nis\na\ntest");
  sys->draw(tui::kBottom_TextPosition | tui::kRight_TextPosition, "This\nis\na\ntest");
  sys->waitKeyDown();

  return 0;
}