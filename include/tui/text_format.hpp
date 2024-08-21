#pragma once

namespace tui {
  enum TextColor : unsigned char {
    kDefault_TextColor       = 0x00,
    kRed_TextColor           = 0x01,
    kGreen_TextColor         = 0x02,
    kYellow_TextColor        = 0x03,
    kBlue_TextColor          = 0x04,
    kMagenta_TextColor       = 0x05,
    kCyan_TextColor          = 0x06,
    kWhite_TextColor         = 0x07,
    kGray_TextColor          = 0x08,
    kLightRed_TextColor     = 0x09,
    kLightGreen_TextColor   = 0x0a,
    kLightYellow_TextColor  = 0x0b,
    kLightBlue_TextColor    = 0x0c,
    kLightMagenta_TextColor = 0x0d,
    kLightCyan_TextColor    = 0x0e,
    kBrightWhite_TextColor  = 0x0f,

    kLastColor_TextColor,
    kNone_TextColor,
  };

  struct TextStyle {
    static const unsigned kNone;
    static const unsigned kUnderline;
    static const unsigned kReverse;
    static const unsigned kBlink;
    static const unsigned kDim;
    static const unsigned kBold;
    static const unsigned kDefault;
  };

  struct TextFormat {
    TextColor color = kDefault_TextColor;
    unsigned style  = TextStyle::kDefault;

    TextFormat operator|(unsigned style) const {
      return {color, this->style | style};
    }
  };
} // namespace tui