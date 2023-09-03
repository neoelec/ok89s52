/* ========================================================================== */
/*           Exp10_8.c : -INT0 Interrupt Count Program(Debouncing)            */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

void LCD_3d(unsigned int number)
{                                              /* display 3-digit decimal number */
  unsigned char i, flag;

  flag = 0;
  i = number / 100;                            // 10^2
  if (i == 0)
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  number = number % 100;                       // 10^1
  i = number / 10;
  if ((i == 0) && (flag == 0))
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  i = number % 10;                             // 10^0
  LCD_data(i + '0');
}

unsigned char int_count = 0;                   // interrupt counter

void INT0_ISR(void) __interrupt 0              // -INT0 interrupt function
{
  Beep();                                      // beep and delay for debouncing
  int_count++;                                 // increment interrupt count
  LCD_command(0xC6);                           // display interrupt count
  LCD_3d(int_count);
loop:while (!P3_2) ;                          // wait until SW2 off(-INT0=1)
  Delay_ms(50);                                // delay for debouncing
  if (!P3_2)
    goto loop;
  IE0 = 0;                                     // clear another interrupt
}

void main(void)
{
  unsigned char i, LED;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, "  -INT0 Count   ");        // display title
  LCD_string(0xC0, "      000       ");

  TCON = 0x01;                                 // -INT0=edge trigger(IT0=1)
  IP = 0x01;                                   // interrupt priority
  IE = 0x81;                                   // enable interrupt(EA=EX0=1)

  while (1) {
    for (i = 1, LED = 0x01; i <= 4; i++) {     // shift from LED1 to LED4
      DIG_SELECT = LED;
      Delay_ms(200);                           // delay 200 ms
      LED <<= 1;
    }
  }
}
