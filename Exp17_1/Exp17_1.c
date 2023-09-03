/* ========================================================================== */
/*           Exp17_1.c : Basic D/A Converter Triangular Wave Output           */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "AT89S52.H"                           // include AT89S52 definition file
#include "OK89S52.H"                           // include OK-89S52 kit function

unsigned char code tri_data[100] = {           // triangular wave data table
  0x80, 0x84, 0x88, 0x8C, 0x90, 0x94, 0x98, 0x9C, 0xA0, 0xA4,
  0xA8, 0xAC, 0xB0, 0xB4, 0xB8, 0xBC, 0xC0, 0xC4, 0xC8, 0xCC,
  0xD0, 0xD4, 0xD8, 0xDC, 0xE0, 0xE4, 0xE0, 0xDC, 0xD8, 0xD4,
  0xD0, 0xCC, 0xC8, 0xC4, 0xC0, 0xBC, 0xB8, 0xB4, 0xB0, 0xAC,
  0xA8, 0xA4, 0xA0, 0x9C, 0x98, 0x94, 0x90, 0x8C, 0x88, 0x84,
  0x80, 0x7C, 0x78, 0x74, 0x70, 0x6C, 0x68, 0x64, 0x60, 0x5C,
  0x58, 0x54, 0x50, 0x4C, 0x48, 0x44, 0x40, 0x3C, 0x38, 0x34,
  0x30, 0x2C, 0x28, 0x24, 0x20, 0x1C, 0x20, 0x24, 0x28, 0x2C,
  0x30, 0x34, 0x38, 0x3C, 0x40, 0x44, 0x48, 0x4C, 0x50, 0x54,
  0x58, 0x5C, 0x60, 0x64, 0x68, 0x6C, 0x70, 0x74, 0x78, 0x7C
};

void main(void)
{
  unsigned char i;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, "   D/A Output   ");        // display title
  LCD_string(0xC0, "Triangular Wave ");

  while (1) {
    for (i = 0; i <= 99; i++) {
      DAC_CS = tri_data[i];                    // output D/A data
      Delay_us(10);                            // dealy 10 us
    }
  }
}
