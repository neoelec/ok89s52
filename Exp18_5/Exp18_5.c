/* ========================================================================== */
/*              Exp18_5.c : Sample Program for C & Assembly Link              */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

void LCD_2d(unsigned char number)
{                                              /* display 2-digit decimal number */
  unsigned char i;

  i = number / 10;                             // 10^1
  if (i == 0)
    LCD_data(' ');
  else
    LCD_data(i + '0');

  i = number % 10;                             // 10^0
  LCD_data(i + '0');
}

void main(void)
{
  unsigned int i, j, k;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, " Multiplication ");        // display title
  LCD_string(0xC0, "   0 * 0 = 00   ");

  while (1) {
    for (i = 2; i <= 9; i++) {
      for (j = 1; j <= 9; j++) {
        LCD_command(0xC3);                     // display multiplicand
        LCD_data(i + '0');
        LCD_command(0xC7);                     // display multiplier
        LCD_data(j + '0');
        k = i * j;
        LCD_command(0xCB);                     // display multiplication
        LCD_2d(k);
        Delay_ms(1000);
      }
      Beep();
    }
  }
}
