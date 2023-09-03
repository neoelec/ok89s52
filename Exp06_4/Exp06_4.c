/* ========================================================================== */
/*                       Exp06_4.c : Bit-Wise Operation                       */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "at89s52.h"                           // include AT89S52 definition file
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
  unsigned char x, LED;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LED = 0x00;                                  // intial LED
  DIG_SELECT = LED;

  while (1) {
    Beep();
    LCD_string(0x80, "        10011101");      // display title
    LCD_string(0xC0, "AND 0F =00000000");

    x = 0x9D;                                  // 0x9D & 0x0F = 0x0D
    LCD_command(0xC8);
    LCD_8bin(x & 0x0F);
    LED ^= 0x01;
    DIG_SELECT = LED;
    Delay_ms(3000);

    LCD_string(0x80, "        10011101");      // display title
    LCD_string(0xC0, " OR 0F =00000000");

    x = 0x9D;                                  // 0x9D | 0x0F = 0x9F
    LCD_command(0xC8);
    LCD_8bin(x | 0x0F);
    LED ^= 0x02;
    DIG_SELECT = LED;
    Delay_ms(3000);

    LCD_string(0x80, "        10011101");      // display title
    LCD_string(0xC0, "XOR 0F =00000000");

    x = 0x9D;                                  // 0x9D ^ 0x0F = 0x92
    LCD_command(0xC8);
    LCD_8bin(x ^ 0x0F);
    LED ^= 0x04;
    DIG_SELECT = LED;
    Delay_ms(3000);
  }
}
