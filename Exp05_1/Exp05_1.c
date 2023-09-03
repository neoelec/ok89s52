/* ========================================================================== */
/*                    Exp05_1.c : Basic LCD Module Display                    */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

void main(void)
{
  unsigned char i;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  while (1) {
    Beep();
    LCD_string(0x80, " OK-89S52  V1.0 ");      // display logo
    LCD_string(0xC0, "  AT89S52-24PC  ");      // display message 1
    Delay_ms(2000);
    LCD_string(0xC0, "   2006/01/01   ");      // display message 2
    Delay_ms(2000);

    Beep();
    LCD_string(0x80, "0123456789ABCDEF0123456789ABCDEF"); // display long line
    LCD_string(0xC0, "Go shift left and right 16 times");
    Delay_ms(1000);

    for (i = 0; i < 16; i++) {                 // shift left
      LCD_command(0x18);
      Delay_ms(300);                           // by 300ms time interval
    }
    Delay_ms(1000);

    for (i = 0; i < 16; i++) {                 // shift right
      LCD_command(0x1C);
      Delay_ms(300);                           // by 300ms time interval
    }
    Delay_ms(1000);
  }
}
