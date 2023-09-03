/* ========================================================================== */
/*                     Exp08_4.c : Calculation of sqrt(x)                     */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <MATH.H>
#include "AT89S52.H"                           // include AT89S52 definition file
#include "OK89S52.H"                           // include OK-89S52 kit function

LCD_2d1(float number)
{                                              /* display real number xx.x */
  unsigned int i, j;

  j = (int)(number * 10. + 0.5);
  i = j / 100;                                 // 10^1
  if (i == 0)
    LCD_data(' ');
  else
    LCD_data(i + '0');

  j = j % 100;                                 // 10^0
  i = j / 10;
  LCD_data(i + '0');
  LCD_data('.');

  i = j % 10;                                  // 10^-1
  LCD_data(i + '0');
}

LCD_1d3(float number)
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

main()
{
  float x;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, " Real Function  ");        // display title
  LCD_string(0xC0, "sqrt(00.0)=0.000");

  while (1) {
    Beep();
    for (x = 0.0; x <= 97.5; x += 2.5) {
      LCD_command(0xC5);
      LCD_2d1(x);                              // display argument
      LCD_command(0xCB);
      LCD_1d3(sqrt(x));                        // display sqrt
      Delay_ms(2000);
    }
  }
}
