/* ========================================================================== */
/*                      Exp07_3.c : Comparison & Branch                       */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include <OK89S52.h>                           // include OK-89S52 kit function

void main(void)
{
  unsigned char key;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, "   KEY INPUT    ");        // display title
  LCD_string(0xC0, "Press KEY4-KEY1!");

  while (1) {
    key = Key_input();                         // key input
    if (key == 0x1C) {                         // KEY1 ?
      LCD_string(0xC0, "      KEY1      ");
      DIG_SELECT = 0x01;
    } else if (key == 0x1A) {                  // KEY2 ?
      LCD_string(0xC0, "      KEY2      ");
      DIG_SELECT = 0x02;
    } else if (key == 0x16) {                  // KEY3 ?
      LCD_string(0xC0, "      KEY3      ");
      DIG_SELECT = 0x04;
    } else if (key == 0x0E) {                  // KEY4 ?
      LCD_string(0xC0, "      KEY4      ");
      DIG_SELECT = 0x08;
    }
  }
}
