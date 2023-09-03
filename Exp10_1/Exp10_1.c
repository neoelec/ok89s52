/* ========================================================================== */
/*                   Exp10_1.c : Key Input - No Debouncing                    */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

void LCD_8bin(unsigned char number)
{                                              /* display 8-bit binary number */
  LCD_data(((number >> 7) & 0x01) + '0');      // 2^7
  LCD_data(((number >> 6) & 0x01) + '0');      // 2^6
  LCD_data(((number >> 5) & 0x01) + '0');      // 2^5
  LCD_data(((number >> 4) & 0x01) + '0');      // 2^4
  LCD_data(((number >> 3) & 0x01) + '0');      // 2^3
  LCD_data(((number >> 2) & 0x01) + '0');      // 2^2
  LCD_data(((number >> 1) & 0x01) + '0');      // 2^1
  LCD_data((number & 0x01) + '0');             // 2^0
}

void main(void)
{
  unsigned char key;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, "   KEY INPUT    ");        // display title
  LCD_string(0xC0, " P1 = 00011110  ");

  while (1) {
    LCD_command(0xC6);                         // cursor position
    key = P1 & 0x1E;                           // key input
    LCD_8bin(key);                             // display binary data
    DIG_SELECT = (key >> 1) ^ 0x0F;            // display LED
  }
}
