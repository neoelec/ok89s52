/* ========================================================================== */
/*                Exp10_3.c : Key Input Count - No Debouncing                 */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

void LCD_2d(unsigned char number)
{                                              /* display 2-digit decimal number */
  unsigned char i;

  i = number / 10;                             /* 10^1 */
  if (i == 0)
    LCD_data(' ');
  else
    LCD_data(i + '0');

  i = number % 10;                             /* 10^0 */
  LCD_data(i + '0');
}

void main(void)
{
  unsigned char key1 = 0, key2 = 0, key3 = 0, key4 = 0;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, "KEY1=00  KEY2=00");        // display title
  LCD_string(0xC0, "KEY3=00  KEY4=00");

  while (1) {
    switch (P1 & 0x1E) {                       // key input without debouncing
    case 0x1C:
      DIG_SELECT = 0x01;
      key1++;                                  // display key1 count
      if (key1 > 99)
        key1 = 0;
      LCD_command(0x85);
      LCD_2d(key1);
      break;
    case 0x1A:
      DIG_SELECT = 0x02;
      key2++;                                  // display key2 count
      if (key2 > 99)
        key2 = 0;
      LCD_command(0x8E);
      LCD_2d(key2);
      break;
    case 0x16:
      DIG_SELECT = 0x04;
      key3++;                                  // display key3 count
      if (key3 > 99)
        key3 = 0;
      LCD_command(0xC5);
      LCD_2d(key3);
      break;
    case 0x0E:
      DIG_SELECT = 0x08;
      key4++;                                  // display key4 count
      if (key4 > 99)
        key4 = 0;
      LCD_command(0xCE);
      LCD_2d(key4);
      break;
    }
  }
}
