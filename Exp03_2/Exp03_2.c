/* ========================================================================== */
/*                      Exp03_2.c : Basic C Program (2)                       */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

void main(void)
{
  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  while (1) {
    Beep();

    LCD_string(0x80, " OK-89S52  V1.0 ");      // display logo 1
    LCD_string(0xC0, "D.Y.YOON in 2005");
    Delay_ms(2000);

    LCD_string(0x80, "  Ohm Book Co.  ");      // display logo 2
    LCD_string(0xC0, "Tel. 02-776-4868");
    Delay_ms(2000);
  }
}
