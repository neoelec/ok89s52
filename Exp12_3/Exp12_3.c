/* ========================================================================== */
/*                      Exp12_3.c : 119 Ambulance Sound                       */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "at89s52.h"                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

void main(void)
{
  unsigned char i;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, "  *  SOUND  *   ");        // display title
  LCD_string(0xC0, " 119 Ambulance  ");

  T2CON = 0x04;                                // TR2=1, C/-T2=0

  while (1) {
    T2MOD = 0x02;                              // speaker on(T2OE=1)
    for (i = 1; i <= 5; i++) {                 // repeat 3 times
      RCAP2H = 53036 >> 8;                     // 480Hz
      RCAP2L = 53036 & 0x00FF;
      Delay_ms(500);
      RCAP2H = 48869 >> 8;                     // 360Hz
      RCAP2L = 48869 & 0x00FF;
      Delay_ms(500);
    }
    T2MOD = 0x00;                              // speaker off(T2OE=0)
    Delay_ms(1000);
  }
}
