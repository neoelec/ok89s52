/* ========================================================================== */
/*              Exp13_3.c : Timer 2, Auto-reload Mode Interrupt               */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

unsigned char int_count;                       // interrupt counter
unsigned char LED;                             // LED output value

void TF2_ISR(void) __interrupt 5               // Timer 2 interrupt function
{
  TF2 = 0;                                     // clear TF2 flag
  int_count--;                                 // interrupt by 20 times ?
  if (int_count == 0) {
    int_count = 20;
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

  LCD_string(0x80, " T2,Auto-reload ");        // display title
  LCD_string(0xC0, " blink LED4 & 1 ");

  T2CON = 0x04;                                // Timer 2, 16-bit auto-reload mode
  T2MOD = 0x00;                                // (up counter)
  RCAP2H = (0 - 50000) >> 8;                   // initialize time constant
  RCAP2L = (0 - 50000) & 0x00FF;               // (24MHz/12/50000 = 40Hz)
  TH2 = (0 - 50000) >> 8;                      // initial Timer 2 value
  TL2 = (0 - 50000) & 0x00FF;
  IP = 0x20;                                   // interrupt priority
  IE = 0xA0;                                   // EA=ET2=1

  int_count = 20;                              // interrupt counter(40Hz/20 = 2Hz)
  LED = 0x01;                                  // initialize LED4, LED1
  DIG_SELECT = LED;

  while (1) ;                                  // infinite loop
}
