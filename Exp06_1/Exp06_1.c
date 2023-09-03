/* ========================================================================== */
/*                   Exp06_1.c : Basic Hexadecimal Addition                   */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include <OK89S52.h>                           // include OK-89S52 kit function

void LCD_2hex(unsigned char number)
{                                              /* display 2-digit hex number */
  unsigned char i;

  i = (number >> 4) & 0x0F;                    // 16^1
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = number & 0x0F;                           // 16^0
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');
}

void LCD_4hex(unsigned int number)
{                                              /* display 4-digit hex number */
  unsigned char i;

  i = (number >> 12) & 0x000F;                 // 16^3
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = (number >> 8) & 0x000F;                  // 16^2
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = (number >> 4) & 0x000F;                  // 16^1
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = number & 0x000F;                         // 16^0
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');
}

void main(void)
{
  unsigned char i, j;
  unsigned int k;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  while (1) {
    Beep();
    LCD_string(0x80, " 8-Bit Addition ");      // display title
    LCD_string(0xC0, "00H + 00H = 00H ");

    for (i = 1, j = 0x11; i <= 7; i++, j += 0x11) { // integer from 0x11 to 0x77
      LCD_command(0xC0);                       // display augend
      LCD_2hex(j);
      LCD_command(0xC6);                       // display addend
      LCD_2hex(j);
      LCD_command(0xCC);                       // display result of addition
      LCD_2hex(j + j);
      Delay_ms(2000);
    }

    Beep();
    LCD_string(0x80, " 0000H + 0000H  ");      // display title
    LCD_string(0xC0, "    = 0000H     ");

    for (i = 1, k = 0x1111; i <= 7; i++, k += 0x1111) { // integer from 0x1111 to 0x7777
      LCD_command(0x81);                       // display augend
      LCD_4hex(k);
      LCD_command(0x89);                       // display addend
      LCD_4hex(k);
      LCD_command(0xC6);                       // display result of addition
      LCD_4hex(k + k);
      Delay_ms(2000);
    }
  }
}
