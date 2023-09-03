/* ========================================================================== */
/*              Exp18_1.c : Execution Time by Optimization Level              */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#pragma optimize(9,SPEED)

#include "AT89S52.H"                           // include AT89S52 definition file
#include "OK89S52.H"                           // include OK-89S52 kit function

LCD_5d(unsigned int number)
{                                              /* display 5-digit decimal number */
  unsigned char flag, i;

  flag = 0;
  i = number / 10000;                          // 10^4
  if (i == 0)
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  number = number % 10000;                     // 10^3
  i = number / 1000;
  if ((i == 0) && (flag == 0))
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  number = number % 1000;                      // 10^2
  i = number / 100;
  if ((i == 0) && (flag == 0))
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  number = number % 100;                       // 10^1
  i = number / 10;
  if ((i == 0) && (flag == 0))
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  i = number % 10;                             // 10^0
  LCD_data(i + '0');
}

main()
{
  unsigned int i, j, time;
  float x, y;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  TMOD = 0x01;                                 // Timer 0, mode 1
  TCON = 0x10;                                 // TR0=1
  TH0 = 0;                                     // clear Timer 0
  TL0 = 0;

  LCD_string(0x80, " Execution Time ");        // display title
  LCD_string(0xC0, "   00000 [us]   ");

  for (i = 1, x = 0.0; i <= 20; i++) {
    j = i + 500;                               // integer addition
    j = i * 500;                               // integer multiplication
    x += 12.34;                                // real addition
    y = x * 56.78 * j;                         // real & integer
  }

  time = TH0 * 256 + TL0;                      // read Timer 0
  LCD_command(0xC3);                           // display execution time
  LCD_5d(time / 2);

  while (1) ;
}
