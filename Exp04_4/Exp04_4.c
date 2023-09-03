/* ========================================================================== */
/*                  Exp04_4.c : Indefinite Loop(2) - Repeat                   */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

void main(void)
{
  unsigned char i, LED;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, "Indefinite Loop ");        // display title
  LCD_string(0xC0, "     Repeat     ");

  while (1) {
    LED = 0x01;                                // shift from LED1 to LED4
    for (i = 1; i <= 4; i++) {
      DIG_SELECT = LED;
      Delay_ms(500);                           // delay 500 ms
      LED <<= 1;                               // shift left
    }
  }
}
