/* ========================================================================== */
/*                      Exp06_3.c : Sequential Addition                       */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "at89s52.h"                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

void LCD_5d(unsigned int number)
{                                              /* display 5-digit decimal number */
  unsigned char i, flag;

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

void main(void)
{
  unsigned char i;
  unsigned int sum;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  while (1) {
    Beep();
    LCD_string(0x80, "1+2+3+ ... +100 ");      // display title
    LCD_string(0xC0, "    = 00000     ");

    for (i = 1, sum = 0; i <= 100; i++)        // integer from 1 to 100
      sum += i;

    LCD_command(0xC6);                         // display total sum
    LCD_5d(sum);
    Delay_ms(2000);

    Beep();
    LCD_string(0x80, "1+2+3+ ... +255 ");      // display title
    LCD_string(0xC0, "    = 00000     ");

    for (i = 1, sum = 0; i > 0; i++)           // integer from 1 to 255
      sum += i;

    LCD_command(0xC6);                         // display total sum
    LCD_5d(sum);
    Delay_ms(2000);
  }
}
