/* ========================================================================== */
/*                 Exp08_2.c : Real Number Multiplication(2)                  */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "at89s52.h"                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

void LCD_1d1(float number)
{                                              /* display real number x.x */
  unsigned int i, j;

  j = (int)(number * 10. + 0.5);
  i = j / 10;                                  // 10^0
  LCD_data(i + '0');
  LCD_data('.');
  i = j % 10;                                  // 10^-1
  LCD_data(i + '0');
}

void LCD_2d2(float number)
{                                              /* display real number xx.xx */
  unsigned int i, j;

  j = (int)(number * 100. + 0.5);
  i = j / 1000;                                // 10^1
  if (i == 0)
    LCD_data(' ');
  else
    LCD_data(i + '0');

  j = j % 1000;                                // 10^0
  i = j / 100;
  LCD_data(i + '0');
  LCD_data('.');

  j = j % 100;                                 // 10^-1
  i = j / 10;
  LCD_data(i + '0');

  i = j % 10;                                  // 10^-2
  LCD_data(i + '0');
}

void main(void)
{
  float x, y;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, " Real Multi(2)  ");        // display title
  LCD_string(0xC0, "0.0 x 0.0 =00.00");

  while (1) {
    Beep();
    for (x = 1.1; x <= 9.9; x += 1.1) {        // multiplicand from 1.1 to 9.9
      for (y = 1.1; y <= 9.9; y += 1.1) {      // multiplier from 1.1 to 9.9
        LCD_command(0xC0);
        LCD_1d1(x);                            // display multiplicand
        LCD_command(0xC6);
        LCD_1d1(y);                            // display multiplier
        LCD_command(0xCB);
        LCD_2d2(x * y);                        // display multiplication
        Delay_ms(2000);
      }
    }
  }
}
