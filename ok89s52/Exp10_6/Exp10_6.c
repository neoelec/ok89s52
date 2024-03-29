/* ========================================================================== */
/*             Exp10_6.c : -INT0 Interrupt Program(Edge Trigger)              */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include <OK89S52.h>                           // include OK-89S52 kit function

void INT0_ISR(void) __interrupt 0              // -INT0 interrupt function
{
  unsigned char i, LED;

  for (i = 1, LED = 0x01; i <= 5; i++) {       // shift from LED1 to LED4
    DIG_SELECT = LED;
    Delay_ms(200);                             // delay 200 ms
    LED <<= 1;
  }
}

void main(void)
{
  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, "-INT0 Interrupt ");        // display title
  LCD_string(0xC0, " (Edge Trigger) ");

  TCON = 0x01;                                 // -INT0=edge trigger(IT0=1)
  IP = 0x01;                                   // interrupt priority
  IE = 0x81;                                   // enable interrupt(EA=EX0=1)

  while (1) ;                                  // wait interrupt
}
