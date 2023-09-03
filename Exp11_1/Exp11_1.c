/* ========================================================================== */
/*            Exp11_1.c : 7-Segment LED Display - Same Characters             */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

unsigned char Bin2LED(unsigned char number)
{                                              /* convert binary to LED pattern */
  if (number == 0)
    return 0xFC;
  else if (number == 1)
    return 0x60;
  else if (number == 2)
    return 0xDA;
  else if (number == 3)
    return 0xF2;
  else if (number == 4)
    return 0x66;
  else if (number == 5)
    return 0xB6;
  else if (number == 6)
    return 0xBE;
  else if (number == 7)
    return 0xE4;
  else if (number == 8)
    return 0xFE;
  else if (number == 9)
    return 0xF6;
  else if (number == 10)
    return 0xEE;
  else if (number == 11)
    return 0x3E;
  else if (number == 12)
    return 0x9C;
  else if (number == 13)
    return 0x7A;
  else if (number == 14)
    return 0x9E;
  else if (number == 15)
    return 0x8E;
  else if (number == 'H')
    return 0x6E;
  else if (number == '-')
    return 0x02;
  else if (number == '.')
    return 0x01;
  else if (number == 0x27)
    return 0x40;
  else
    return 0x00;
}

void main(void)
{
  unsigned char i, j, digit;
  unsigned char random[8] = { 0x04, 0x80, 0x40, 0x02, 0x08, 0x10, 0x20, 0x02 };

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, " 7-segment LED  ");        // display title
  LCD_string(0xC0, "                ");

  while (1) {
    DIG_SELECT = 0xFF;                         // select all digits
    for (i = 0; i <= 0x0F; i++) {              // display from 0 to F
      SEG_PATTERN = Bin2LED(i);
      Delay_ms(1000);
    }
    SEG_PATTERN = Bin2LED('H');                // display "H"
    Delay_ms(1000);
    SEG_PATTERN = Bin2LED('-');                // display "-"
    Delay_ms(1000);
    SEG_PATTERN = Bin2LED('.');                // display "."
    Delay_ms(1000);
    SEG_PATTERN = Bin2LED(0x27);               // display "'"
    Delay_ms(1000);

    for (i = 1, digit = 0x80; i <= 8; i++) {   // display random pattern
      DIG_SELECT = digit;
      for (j = 0; j <= 7; j++) {
        SEG_PATTERN = random[j];
        Delay_ms(100);
      }
      digit >>= 1;
    }
  }
}
