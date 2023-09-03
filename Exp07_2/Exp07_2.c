/* ========================================================================== */
/*                  Exp07_2.c : Numerical Data Comparison(2)                  */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <math.h>
#include <at89s52.h>                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

void LCD_3d(unsigned char number)
{                                              /* unsigned 3-digit decimal number */
  unsigned char i, flag;

  flag = 0;
  i = number / 100;                            // 10^2
  if (i == 0)
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

void LCD_s3d(signed char number)
{                                              /* signed 3-digit decimal number */
  unsigned char i, flag, absolute;

  if (number >= 0)
    LCD_data('+');                             // sign
  else
    LCD_data('-');

  absolute = abs(number);                      // calculate absolute

  flag = 0;
  i = absolute / 100;                          // 10^2
  if (i == 0)
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  absolute = absolute % 100;                   // 10^1
  i = absolute / 10;
  if ((i == 0) && (flag == 0))
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  i = absolute % 10;                           // 10^0
  LCD_data(i + '0');
}

void Ucompare(unsigned char a, unsigned char b)
{                                              /* unsigned char compare */
  LCD_command(0xC3);                           // display first data
  LCD_3d(a);
  LCD_command(0xC9);                           // display second data
  LCD_3d(b);
  LCD_command(0xC7);                           // display comparison
  if (a == b)
    LCD_data('=');
  else if (a > b)
    LCD_data('>');
  else
    LCD_data('<');
  Delay_ms(2000);
}

void Compare(signed char a, signed char b)
{                                              /* signed char compare */
  LCD_command(0xC2);                           // display first data
  LCD_s3d(a);
  LCD_command(0xC9);                           // display second data
  LCD_s3d(b);
  LCD_command(0xC7);                           // display comparison
  if (a == b)
    LCD_data('=');
  else if (a > b)
    LCD_data('>');
  else
    LCD_data('<');
  Delay_ms(2000);
}

void main(void)
{
  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  while (1) {
    Beep();
    LCD_string(0x80, "Unsigned Compare");      // display title
    LCD_string(0xC0, "                ");      // unsigned 8-bit compare
    Ucompare(100, 100);
    Ucompare(100, 150);
    Ucompare(200, 150);

    Beep();
    LCD_string(0x80, " Signed Compare ");      // display title
    LCD_string(0xC0, "                ");      // signed 8-bit compare
    Compare(-100, -100);
    Compare(+100, -100);
    Compare(-100, +100);
    Compare(-100, -120);
    Compare(-120, -100);
  }
}
