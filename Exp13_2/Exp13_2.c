/* ========================================================================== */
/*                   Exp13_2.c : Timer 0, Mode 2 Interrupt                    */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

unsigned int int_count;                        // interrupt counter
unsigned char LED;                             // LED output value

void TF0_ISR(void) __interrupt 1               // Timer 0 interrupt function
{
  int_count--;                                 // interrupt by 4000 times ?
  if (int_count == 0) {
    int_count = 4000;
    LED ^= 0x09;                               // if yes, blink LED4, LED1
    DIG_SELECT = LED;
  }
}

void main(void)
{
  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, " Timer 0,Mode 2 ");        // display title
  LCD_string(0xC0, " blink LED4 & 1 ");

  TMOD = 0x02;                                 // Timer 0, mode 2
  TCON = 0x10;                                 // TR0=1
  TH0 = (0 - 250);                             // initialize time constant
  TL0 = (0 - 250);                             // (24MHz/12/250 = 8000Hz)
  IP = 0x02;                                   // interrupt priority
  IE = 0x82;                                   // EA=ET0=1

  int_count = 4000;                            // int. counter(8000Hz/4000 = 2Hz)
  LED = 0x01;                                  // initialize LED4, LED1
  DIG_SELECT = LED;

  while (1) ;                                  // infinite loop
}
