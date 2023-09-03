/* ========================================================================== */
/*                 Exp08_1.c : Real Number Multiplication(1)                  */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "AT89S52.H"                           // include AT89S52 definition file
#include "OK89S52.H"                           // include OK-89S52 kit function

LCD_1d1(float number)
{                                              /* display real number x.x */
  unsigned int i, j;

  j = (int)(number * 10. + 0.5);
  i = j / 10;                                  // 10^0
  LCD_data(i + '0');
  LCD_data('.');
  i = j % 10;                                  // 10^-1
  LCD_data(i + '0');
}

LCD_2d2(float number)
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

main()
{
  unsigned char i, j;
  float x, y;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, " Real Multi(1)  ");        // display title
  LCD_string(0xC0, "0.0 x 0.0 =00.00");

  while (1) {
    Beep();
    for (i = 1, x = 0.0; i <= 9; i++) {        // multiplicand from 1.1 to 9.9
      x += 1.1;
      for (j = 1, y = 0.0; j <= 9; j++) {      // multiplier from 1.1 to 9.9
        y += 1.1;
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
