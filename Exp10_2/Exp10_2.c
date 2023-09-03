/* ========================================================================== */
/*                     Exp10_2.c : Key Input - Debouncing                     */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "at89s52.h"                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

void main(void)
{
  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, "   KEY INPUT    ");        // display title
  LCD_string(0xC0, "Press KEY4-KEY1!");

  while (1) {
    switch (Key_input()) {                     // key input
    case 0x1C:
      LCD_string(0xC0, "  KEY1 is OK !  ");
      DIG_SELECT = 0x01;
      break;
    case 0x1A:
      LCD_string(0xC0, "  KEY2 is OK !  ");
      DIG_SELECT = 0x02;
      break;
    case 0x16:
      LCD_string(0xC0, "  KEY3 is OK !  ");
      DIG_SELECT = 0x04;
      break;
    case 0x0E:
      LCD_string(0xC0, "  KEY4 is OK !  ");
      DIG_SELECT = 0x08;
      break;
    }
  }
}
