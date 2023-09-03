/* ========================================================================== */
/*                  Exp14_1.c : Digital Clock using Timer 0                   */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include <OK89S52.h>                           // include OK-89S52 kit function

unsigned int int_count;                        // interrupt counter
unsigned char second;                          // second
unsigned char minute;                          // minute
unsigned char hour;                            // hour
unsigned char ampm;                            // AM='A', PM='P'

void LCD_2d(unsigned char number)
{                                              /* display time xx */
  LCD_data(number / 10 + '0');                 // 10^1
  LCD_data(number % 10 + '0');                 // 10^0
}

void TF0_ISR(void) __interrupt 1               /* Timer 0 int. service routine */
{
  int_count--;
  if (int_count != 0)
    return;                                    // __interrupt 8000 times ?
  int_count = 8000;
  second++;                                    // if yes, increment second
  if (second == 60) {                          // 60 seconds ?
    second = 0;                                // if yes, clear seconds
    minute++;                                  //         and increment minute
    if (minute == 60) {                        // 60 minutes ?
      minute = 0;                              // if yes, clear minutes
      hour++;                                  //         and inrement hour
      if ((hour == 12) && (ampm == 'A'))       // 12 hours ?
        ampm = 'P';                            // if yes, decide AM/PM
      else if ((hour == 12) && (ampm == 'P'))
        ampm = 'A';
      else if (hour == 13)
        hour = 1;
    }
  }
  LCD_command(0xC2);                           // display hour
  LCD_2d(hour);
  LCD_command(0xC5);                           // display minute
  LCD_2d(minute);
  LCD_command(0xC8);                           // display second
  LCD_2d(second);
  LCD_command(0xCB);                           // display AM/PM
  LCD_data(ampm);
}

void main(void)
{
  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, " Digital Clock  ");        // display title
  LCD_string(0xC0, "  12:00:00 AM   ");

  hour = 12;                                   // initial time
  minute = 0;
  second = 0;
  ampm = 'A';

  TMOD = 0x02;                                 // Timer 0, mode 2
  TCON = 0x10;                                 // TR0=1
  TH0 = 0 - 250;                               // initialize time constant
  TL0 = 0 - 250;                               // (24MHz/12/250 = 8000Hz)
  IP = 0x02;                                   // interrupt priority
  IE = 0x82;                                   // EA=ET0=1

  int_count = 8000;                            // software counter
  // (8000Hz/8000 = 1Hz)
  while (1) ;
}
