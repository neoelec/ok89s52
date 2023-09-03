/* ========================================================================== */
/*                    Exp13_6.c : Stop Watch using Timer 2                    */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

unsigned int second;                           // second * 100
unsigned char minute;                          // minute
unsigned char hour;                            // hour
unsigned char run_flag;                        // stop watch operation flag

void LCD_2d(unsigned char number)
{                                              /* display time xx */
  LCD_data(number / 10 + '0');                 // 10^1
  LCD_data(number % 10 + '0');                 // 10^0
}

void TF2_ISR(void) interrupt 5                 /* Timer 2 int. service routine */
{
  TF2 = 0;                                     // clear TF2 flag
  second++;                                    // increment interrupt counter
  if (second == 6000) {                        // second = 60 ?
    second = 0;                                // if yes, second = 0
    minute++;                                  //         and increment minute
    if (minute == 60) {                        // minute = 60 ?
      minute = 0;                              // if yes, minute = 0
      hour++;                                  //         and increment hour
      if (hour == 100)                         // hour = 100 ?
        hour = 0;                              // if yes, hour = 0
    }
  }
  LCD_command(0xC2);                           // display stop watch time
  LCD_2d(hour);
  LCD_command(0xC5);
  LCD_2d(minute);
  LCD_command(0xC8);
  LCD_2d(second / 100);
  LCD_command(0xCB);
  LCD_2d(second % 100);
}

void main(void)
{
  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, " STOP WATCH(T2) ");        // display title
  LCD_string(0xC0, "  00:00:00.00   ");

  second = 0;                                  // clear time
  minute = 0;
  hour = 0;
  run_flag = 0;                                // run_flag=0
  DIG_SELECT = 0x04;                           // LED3 on

  while (1) {
    switch (Key_input()) {
    case 0x1C:
      if (run_flag == 1)
        break;                                 // if KEY1, start
      T2CON = 0x04;                            // Timer 2, 16-bit reload mode
      T2MOD = 0x00;                            // (up counter)
      RCAP2H = (0 - 20000) >> 8;               // initialize time constant
      RCAP2L = (0 - 20000) & 0x00FF;           // (24MHz/12/20000 = 100Hz)
      TH2 = (0 - 20000) >> 8;                  // initial Timer 2 value
      TL2 = (0 - 20000) & 0x00FF;
      IP = 0x20;                               // interrupt priority
      IE = 0xA0;                               // EA=ET2=1
      DIG_SELECT = 0x01;                       // LED1 on
      run_flag = 1;                            // run_flag=1
      break;
    case 0x16:
      if (run_flag == 1)
        break;                                 // if KEY3, reset
      LCD_string(0xC0, "  00:00:00.00   ");
      second = 0;                              // clear time
      minute = 0;
      hour = 0;
      DIG_SELECT = 0x04;                       // LED3 on
      break;
    case 0x0E:
      if (run_flag == 0)
        break;                                 // if KEY4, stop
      ET2 = 0;
      DIG_SELECT = 0x08;                       // LED4 on
      run_flag = 0;                            // run_flag=0
      break;
    default:
      break;
    }
  }
}
