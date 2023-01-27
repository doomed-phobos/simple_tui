#pragma once

namespace cli {
   enum Color : short {
      kColor_Default       = 0x00,
      kColor_Red           = 0x01,
      kColor_Green         = 0x02,
      kColor_Yellow        = 0x03,
      kColor_Blue          = 0x04,
      kColor_Magenta       = 0x05,
      kColor_Cyan          = 0x06,
      kColor_White         = 0x07,
      kColor_Gray          = 0x08,
      kColor_Light_Red     = 0x09,
      kColor_Light_Green   = 0x0a,
      kColor_Light_Yellow  = 0x0b,
      kColor_Light_Blue    = 0x0c,
      kColor_Light_Magenta = 0x0d,
      kColor_Light_Cyan    = 0x0e,
      kColor_Bright_White  = 0x0f,

      kColor_LastColor     = kColor_Bright_White,
   };
} // namespace cli