/* ========================================================================== */
/*                    Exp13_5.c : Stop Watch using Timer 0                    */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

unsigned int time;                             // time = second * 100
unsigned char run_flag;                        // stop watch operation flag

void LCD_3d2(unsigned int number)
{                                              /* display time xxx.xx */
  unsigned char i, flag;

  flag = 0;
  i = number / 10000;                          // 10^2
  if (i == 0)
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  number = number % 10000;                     // 10^1
  i = number / 1000;
  if ((i == 0) && (flag == 0))
    LCD_data(' ');
  else {
    LCD_data(i + '0');
    flag = 1;
  }

  number = number % 1000;                      // 10^0
  i = number / 100;
  LCD_data(i + '0');
  LCD_data('.');

  number = number % 100;                       // 10^-1
  i = number / 10;
  LCD_data(i + '0');

  i = number % 10;                             // 10^-2
  LCD_data(i + '0');
}

void TF0_ISR(void) __interrupt 1               /* Timer 0 int. service routine */
{
  TH0 = (0 - 20000) >> 8;                      // initial Timer 0 value
  TL0 = (0 - 20000) & 0x00FF;                  // (24MHz/12/20000 = 100Hz)

  time++;                                      // increment interrupt counter
  LCD_command(0xC2);                           // display stop watch time
  LCD_3d2(time);
}

void main(void)
{
  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, " STOP WATCH(T0) ");        // display title
  LCD_string(0xC0, "  000.00 [SEC]  ");

  time = 0;                                    // clear time
  run_flag = 0;                                // run_flag=0
  DIG_SELECT = 0x04;                           // LED3 on

  while (1) {
    switch (Key_input()) {
    case 0x1C:
      if (run_flag == 1)
        break;                                 // if KEY1, start
      TMOD = 0x01;                             // Timer 0, mode 1
      TCON = 0x10;                             // TR0=1
      TH0 = (0 - 20000) >> 8;                  // initial Timer 0 value
      TL0 = (0 - 20000) & 0x00FF;              // (24MHz/12/20000 = 100Hz)
      IP = 0x02;                               // interrupt priority
      IE = 0x82;                               // EA=ET0=1
      DIG_SELECT = 0x01;                       // LED1 on
      run_flag = 1;                            // run_flag=1
      break;
    case 0x16:
      if (run_flag == 1)
        break;                                 // if KEY3, reset
      LCD_string(0xC0, "  000.00 [SEC]  ");
      time = 0;                                // clear time
      DIG_SELECT = 0x04;                       // LED3 on
      break;
    case 0x0E:
      if (run_flag == 0)
        break;                                 // if KEY4, stop
      ET0 = 0;
      DIG_SELECT = 0x08;                       // LED4 on
      run_flag = 0;                            // run_flag=0
      break;
    default:
      break;
    }
  }
}
