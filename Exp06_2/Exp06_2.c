/* ========================================================================== */
/*                     Exp06_2.c : Basic Decimal Addition                     */
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

void main(void)
{
  unsigned char i, j;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, " 8-Bit Addition ");        // display title
  LCD_string(0xC0, "000 + 000 = 000 ");

  for (i = 10; i <= 200; i += 10)              // i = from 10 to 200
    for (j = 10; j <= 200; j += 10) {          // j = from 10 to 200
      LCD_command(0xC0);                       // display augend
      LCD_3d((unsigned int)i);
      LCD_command(0xC6);                       // display addend
      LCD_3d((unsigned int)j);
      LCD_command(0xCC);                       // display result of addition
      LCD_3d((unsigned int)(i + j));
      Delay_ms(500);
    }

  while (1) ;
}
