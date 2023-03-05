#pragma once
#include <cstdint>

namespace tui {
   class TextFormat {
   public:
      uint8_t color() const {return (uint8_t) ((m_value >> 28) & 0xff);}
      uint32_t style() const {return (uint32_t) (m_value & 0xfffffff);}

      TextFormat operator|(const uint32_t style) const {
         return TextFormat(m_value | style);
      }

      static TextFormat MakeFromColor(uint8_t color) {
         return TextFormat((uint64_t)color << 28);
      }
   private:
      TextFormat(uint64_t value) :
         m_value{value} {}

      uint64_t m_value;
   };

   namespace formats {
      const TextFormat kDefault_TextColor       = TextFormat::MakeFromColor(0x00); 
      const TextFormat kRed_TextColor           = TextFormat::MakeFromColor(0x01);
      const TextFormat kGreen_TextColor         = TextFormat::MakeFromColor(0x02);
      const TextFormat kYellow_TextColor        = TextFormat::MakeFromColor(0x03);
      const TextFormat kBlue_TextColor          = TextFormat::MakeFromColor(0x04);
      const TextFormat kMagenta_TextColor       = TextFormat::MakeFromColor(0x05);
      const TextFormat kCyan_TextColor          = TextFormat::MakeFromColor(0x06);
      const TextFormat kWhite_TextColor         = TextFormat::MakeFromColor(0x07);
      const TextFormat kGray_TextColor          = TextFormat::MakeFromColor(0x08);
      const TextFormat kLight_Red_TextColor     = TextFormat::MakeFromColor(0x09);
      const TextFormat kLight_Green_TextColor   = TextFormat::MakeFromColor(0x0a);
      const TextFormat kLight_Yellow_TextColor  = TextFormat::MakeFromColor(0x0b);
      const TextFormat kLight_Blue_TextColor    = TextFormat::MakeFromColor(0x0c);
      const TextFormat kLight_Magenta_TextColor = TextFormat::MakeFromColor(0x0d);
      const TextFormat kLight_Cyan_TextColor    = TextFormat::MakeFromColor(0x0e);
      const TextFormat kBright_White_TextColor  = TextFormat::MakeFromColor(0x0f);

      extern const uint32_t kBold_TextStyle;
      extern const uint32_t kDim_TextStyle;

      const TextFormat colors[] = {
         kDefault_TextColor,
         kRed_TextColor,
         kGreen_TextColor,
         kYellow_TextColor,
         kBlue_TextColor,
         kBlue_TextColor,
         kMagenta_TextColor,
         kCyan_TextColor,
         kWhite_TextColor,
         kGray_TextColor,
         kLight_Red_TextColor,
         kLight_Green_TextColor,
         kLight_Yellow_TextColor,
         kLight_Magenta_TextColor,
         kLight_Blue_TextColor,
         kLight_Magenta_TextColor,
         kLight_Cyan_TextColor,
         kBright_White_TextColor,
      };
   } // namespace formats
} // namespace tui