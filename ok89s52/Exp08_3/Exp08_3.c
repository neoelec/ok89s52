/* ========================================================================== */
/*                         Exp08_3.c : Real Division                          */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <math.h>

#include <at89s52.h>                           // include AT89S52 definition file
#include <OK89S52.h>                           // include OK-89S52 kit function

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

void LCD_1d2(float number)
{                                              /* display real number x.xx */
  unsigned int i, j;

  j = (int)(number * 100. + 0.5);
  i = j / 100;                                 // 10^0
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

  LCD_string(0x80, " Real Division  ");        // display title
  LCD_string(0xC0, "0.0 / 0.0 = 0.00");

  while (1) {
    Beep();
    for (x = 1.1; x <= 9.9; x += 1.1) {
      for (y = 1.1; y <= 9.9; y += 1.1) {
        LCD_command(0xC0);
        LCD_1d1(x);                            // display dividend
        LCD_command(0xC6);
        LCD_1d1(y);                            // display divisor
        LCD_command(0xCC);
        LCD_1d2(x / y);                        // display quotient
        Delay_ms(2000);
      }
    }
  }
}
