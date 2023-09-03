/* ========================================================================== */
/*                 Exp08_5.c : Calculation of log(x),log10(x)                 */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <math.h>

#include <at89s52.h>                           // include AT89S52 definition file
#include <OK89S52.h>                           // include OK-89S52 kit function

void LCD_2d0(float number)
{                                              /* display real number xx. */
  unsigned int i, j;

  j = (int)number;
  i = j / 10;                                  // 10^1
  if (i == 0)
    LCD_data(' ');
  else
    LCD_data(i + '0');

  i = j % 10;                                  // 10^0
  LCD_data(i + '0');
  LCD_data('.');
}

void LCD_1d3(float number)
{                                              /* display real number x.xxx */
  unsigned int i, j;

  j = (int)(number * 1000. + 0.5);
  i = j / 1000;                                // 10^0
  LCD_data(i + '0');
  LCD_data('.');

  j = j % 1000;                                // 10^-1
  i = j / 100;
  LCD_data(i + '0');

  j = j % 100;                                 // 10^-2
  i = j / 10;
  LCD_data(i + '0');

  i = j % 10;                                  // 10^-3
  LCD_data(i + '0');
}

void main(void)
{
  float x;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "  log(00.)=0.000");        // display title
  LCD_string(0xC0, "log10(00.)=0.000");

  while (1) {
    Beep();
    for (x = 5.0; x <= 95.0; x += 5.0) {
      LCD_command(0x86);
      LCD_2d0(x);                              // display natural logarithm
      LCD_command(0x8B);
      LCD_1d3(logf(x));
      LCD_command(0xC6);
      LCD_2d0(x);                              // display common logarithm
      LCD_command(0xCB);
      LCD_1d3(log10f(x));
      Delay_ms(2000);
    }
  }
}
