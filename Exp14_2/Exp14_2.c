/* ========================================================================== */
/*                  Exp14_2.c : Digital Clock using Timer 2                   */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "AT89S52.H"                           // include AT89S52 definition file
#include "OK89S52.H"                           // include OK-89S52 kit function

unsigned char int_count;                       // interrupt counter
unsigned char colon_flag;                      // colon blink flag
unsigned char second;                          // second
unsigned char minute;                          // minute
unsigned char hour;                            // hour
unsigned char ampm;                            // AM='A', PM='P'

void LCD_2d(unsigned char number)
{                                              /* display time xx */
  LCD_data(number / 10 + '0');                 // 10^1
  LCD_data(number % 10 + '0');                 // 10^0
}

void TF2_ISR(void) interrupt 5                 /* Timer 2 int. service routine */
{
  unsigned char colon;

  TF2 = 0;                                     // clear TF2 flag
  int_count--;
  if (int_count != 0)
    return;                                    // interrupt 20 times ?
  int_count = 20;
  colon_flag ^= 0x01;                          // colon on or off ?
  if (colon_flag == 0)
    colon = ' ';
  else
    colon = ':';
  LCD_command(0xC4);
  LCD_data(colon);
  LCD_command(0xC7);
  LCD_data(colon);
  if (colon == ':')
    return;
  second++;                                    // increment second
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

  T2CON = 0x04;                                // Timer 2, 16-bit reload mode
  T2MOD = 0x00;                                // (up counter)
  RCAP2H = (0 - 50000) >> 8;                   // initialize time constant
  RCAP2L = (0 - 50000) & 0x00FF;               // (24MHz/12/50000 = 40Hz)
  TH2 = (0 - 50000) >> 8;                      // initial Timer 2 value
  TL2 = (0 - 50000) & 0x00FF;
  IP = 0x20;                                   // interrupt priority
  IE = 0xA0;                                   // EA=ET2=1

  colon_flag = 1;                              // colon blink flag
  int_count = 20;                              // software counter
  // (40Hz/20 = 2Hz)
  while (1) ;
}
