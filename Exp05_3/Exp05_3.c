/* ========================================================================== */
/*                     Exp05_3.c : Integer Number Display                     */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "AT89S52.H"                           // include AT89S52 definition file
#include "OK89S52.H"                           // include OK-89S52 kit function

void LCD_3d(unsigned int number)
{                                              /* display 3-digit decimal number */
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

void LCD_8bin(unsigned char number)
{                                              /* display 8-bit binary number */
  LCD_data(((number >> 7) & 0x01) + '0');      // 2^7
  LCD_data(((number >> 6) & 0x01) + '0');      // 2^6
  LCD_data(((number >> 5) & 0x01) + '0');      // 2^5
  LCD_data(((number >> 4) & 0x01) + '0');      // 2^4
  LCD_data(((number >> 3) & 0x01) + '0');      // 2^3
  LCD_data(((number >> 2) & 0x01) + '0');      // 2^2
  LCD_data(((number >> 1) & 0x01) + '0');      // 2^1
  LCD_data((number & 0x01) + '0');             // 2^0
}

void main(void)
{
  unsigned char i;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, " INTEGER = 000  ");        // display title
  LCD_string(0xC0, "= 00H = 00000000");

  for (i = 1; i > 0; i++) {                    // integer number from 1 to 255
    LCD_command(0x8B);                         // display decimal number
    LCD_3d((unsigned int)i);
    LCD_command(0xC2);                         // display hexadecimal number
    LCD_2hex(i);
    LCD_command(0xC8);                         // display binary number
    LCD_8bin(i);
    Delay_ms(1000);
  }

  while (1) ;
}
