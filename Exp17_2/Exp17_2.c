/* ========================================================================== */
/*           Exp17_2.c : Basic D/A Converter Sinusoidal Wave Output           */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

unsigned char __code sin_data[100] = {         // sinusoidal wave data table
  0x80, 0x88, 0x90, 0x98, 0xA0, 0xA7, 0xAF, 0xB6, 0xBD, 0xC4,
  0xCB, 0xD1, 0xD7, 0xDD, 0xE2, 0xE7, 0xEB, 0xEF, 0xF3, 0xF6,
  0xF9, 0xFB, 0xFD, 0xFE, 0xFF, 0xFF, 0xFF, 0xFE, 0xFD, 0xFB,
  0xF9, 0xF6, 0xF3, 0xEF, 0xEB, 0xE7, 0xE2, 0xDD, 0xD7, 0xD1,
  0xCB, 0xC4, 0xBD, 0xB6, 0xAF, 0xA7, 0xA0, 0x98, 0x90, 0x88,
  0x80, 0x78, 0x70, 0x68, 0x60, 0x59, 0x51, 0x4A, 0x43, 0x3C,
  0x35, 0x2F, 0x29, 0x23, 0x1E, 0x19, 0x15, 0x11, 0x0D, 0x0A,
  0x07, 0x05, 0x03, 0x02, 0x01, 0x01, 0x01, 0x02, 0x03, 0x05,
  0x07, 0x0A, 0x0D, 0x11, 0x15, 0x19, 0x1E, 0x23, 0x29, 0x2F,
  0x35, 0x3C, 0x43, 0x4A, 0x51, 0x59, 0x60, 0x68, 0x70, 0x78
};

void main(void)
{
  unsigned char i;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, "   D/A Output   ");        // display title
  LCD_string(0xC0, "Sinusoidal Wave ");

  while (1) {
    for (i = 0; i <= 99; i++) {
      DAC_CS = sin_data[i];                    // output D/A data
      Delay_us(10);                            // dealy 10 us
    }
  }
}
