/* ========================================================================== */
/*          Exp11_2.c : 7-Segment LED Display - Different Characters          */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "AT89S52.H"                           // include AT89S52 definition file
#include "OK89S52.H"                           // include OK-89S52 kit function

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

main()
{
  unsigned char i, j, digit;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, " 7-segment LED  ");        // display title
  LCD_string(0xC0, "                ");

  while (1) {
    for (i = 1; i <= 250; i++) {               // display from 0 to 7
      for (j = 0, digit = 0x80; j <= 7; j++) {
        SEG_PATTERN = Bin2LED(j);              // output segment pattern data
        DIG_SELECT = digit;                    // output digit select data
        Delay_ms(1);                           // delay 1ms
        digit >>= 1;
      }
    }

    for (i = 1; i <= 250; i++) {               // display from 8 to F
      for (j = 8, digit = 0x80; j <= 0x0F; j++) {
        SEG_PATTERN = Bin2LED(j);              // output segment pattern data
        DIG_SELECT = digit;                    // output digit select data
        Delay_ms(1);                           // delay 1ms
        digit >>= 1;
      }
    }
  }
}
