/* ========================================================================== */
/*             Exp13_4.c : Nested Interrupt of Timer 0 & Timer 1              */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "AT89S52.H"                           // include AT89S52 definition file
#include "OK89S52.H"                           // include OK-89S52 kit function

unsigned int int0_count, int1_count;           // interrupt counter
unsigned char LED;                             // LED output value

void TF0_ISR(void) interrupt 1                 // Timer 0 interrupt function
{
  int0_count--;                                // interrupt by 1000 times ?
  if (int0_count == 0) {
    int0_count = 1000;
    LED ^= 0x01;                               // if yes, blink LED1
    DIG_SELECT = LED;
  }
}

void TF1_ISR(void) interrupt 3                 // Timer 1 interrupt function
{
  int1_count--;                                // interrupt by 4000 times ?
  if (int1_count == 0) {
    int1_count = 4000;
    LED ^= 0x08;                               // if yes, blink LED4
    DIG_SELECT = LED;
  }
}

void main(void)
{
  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, "Timer 1  Timer 0");        // display title
  LCD_string(0xC0, " LED4      LED1 ");

  TMOD = 0x22;                                 // Timer 0 and 1, mode 2
  TCON = 0x50;                                 // TR0=TR1=1
  TH0 = (0 - 200);                             // initialize time constant of Timer 0
  TL0 = (0 - 200);                             // (24MHz/12/200 = 10000Hz)
  TH1 = (0 - 250);                             // initialize time constant of Timer 1
  TL1 = (0 - 250);                             // (24MHz/12/250 = 8000Hz)

  IP = 0x0A;                                   // interrupt priority
  IE = 0x8A;                                   // EA=ET1=ET0=1

  int0_count = 1000;                           // int. counter(10000Hz/1000 = 10Hz)
  int1_count = 4000;                           // int. counter(8000Hz/4000 = 2Hz)

  LED = 0x00;                                  // initialize LED4, LED1
  DIG_SELECT = LED;

  while (1) ;                                  // infinite loop
}
