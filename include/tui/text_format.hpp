#pragma once

namespace tui {
   enum TextColor : short {
      kDefault_TextColor       = 0x00,
      kRed_TextColor           = 0x01,
      kGreen_TextColor         = 0x02,
      kYellow_TextColor        = 0x03,
      kBlue_TextColor          = 0x04,
      kMagenta_TextColor       = 0x05,
      kCyan_TextColor          = 0x06,
      kWhite_TextColor         = 0x07,
      kGray_TextColor          = 0x08,
      kLight_Red_TextColor     = 0x09,
      kLight_Green_TextColor   = 0x0a,
      kLight_Yellow_TextColor  = 0x0b,
      kLight_Blue_TextColor    = 0x0c,
      kLight_Magenta_TextColor = 0x0d,
      kLight_Cyan_TextColor    = 0x0e,
      kBright_White_TextColor  = 0x0f,

      kLastColor_TextColor     = kBright_White_TextColor,
   };

   enum TextStyle {
      kDefault_TextStyle = 0,
      kBold_TextStyle    = 1 << 1,
      kDim_TextStyle     = 1 << 2, // Half bright
   };  

   class TextFormat {
   public:
      TextFormat();
      TextFormat(TextColor color);
      TextFormat(TextColor color, unsigned style);

      unsigned int ncurses_style() const {return m_style;}
      short ncurses_color() const {return m_color;}
   private:
      unsigned m_style;
      short m_color;
   };
} // namespace tui