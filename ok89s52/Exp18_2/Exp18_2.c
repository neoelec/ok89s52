/* ========================================================================== */
/*                Exp18_2.c : Modify Startup File STARTUP.A51                 */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include <OK89S52.h>                           // include OK-89S52 kit function

#define LED1 (*(unsigned char __data *)0x30)   // internal SRAM address
#define LED2 (*(unsigned char __data *)0x31)

void main(void)
{
  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, " Modify Startup ");        // display title
  LCD_string(0xC0, "   STARTUP.A51  ");

  while (1) {
    DIG_SELECT = LED1;                         // LED data 1 of 0x30 address
    Delay_ms(500);
    DIG_SELECT = LED2;                         // LED data 2 of 0x31 address
    Delay_ms(500);
  }
}
