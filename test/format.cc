#include "tui/system.hpp"
#include "tui/text_format.hpp"

int main() {
  using namespace tui;
  auto sys = System::GetOrTryCreate();
  if(!sys) {
    fputs("Error al iniciar sistema", stderr);
    return 1;
  }

  sys->setTextFormat({.style = TextStyle::kUnderline}); sys->draw("This is a test\n");
  sys->setTextFormat({.color = kMagenta_TextColor});
  sys->setTextFormat({.style = TextStyle::kReverse}); sys->draw("This is a test\n");
  sys->setTextFormat({.color = kCyan_TextColor});
  sys->setTextFormat({.style = TextStyle::kBlink}); sys->draw("This is a test\n");
  sys->setTextFormat({.color = kYellow_TextColor});
  sys->setTextFormat({.style = TextStyle::kDim}); sys->draw("This is a test\n");
  sys->setTextFormat({.color = kLightRed_TextColor});
  sys->setTextFormat({.style = TextStyle::kBold}); sys->draw("This is a test\n");
  sys->setTextFormat({.color = kNone_TextColor});
  sys->setTextFormat({.style = TextStyle::kNone}); sys->draw("This is a test\n");

  sys->waitKeyDown();

  return 0;
}