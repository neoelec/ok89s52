/* ========================================================================== */
/*                  Exp14_3.c : Digital Clock using DS12C887                  */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include <OK89S52.h>                           // include OK-89S52 kit function

unsigned char cursor;                          // cursor position
unsigned char year;                            // year
unsigned char month;                           // month
unsigned char date;                            // date
unsigned char hour;                            // hour
unsigned char minute;                          // minute
unsigned char second;                          // second

void LCD_2BCD(unsigned char number)
{                                              /* display 2-digit BCD number */
  unsigned char i;

  i = (number >> 4) & 0x0F;                    // 10^1
  LCD_data(i + '0');

  i = number & 0x0F;                           // 10^0
  LCD_data(i + '0');
}

void DSP_RTC(void)
{                                              /* display clock from RTC */
  unsigned char weekday;

  LCD_command(0x0C);                           // cursor OFF

  LCD_command(0x81);                           // display year
  LCD_2BCD(0x20);
  year = RTC_YEAR;
  LCD_2BCD(year);

  LCD_command(0x86);                           // display month
  month = RTC_MONTH;
  LCD_2BCD(month);

  LCD_command(0x89);                           // display date
  date = RTC_DATE;
  LCD_2BCD(date);

  weekday = RTC_WEEKDAY;                       // display weekday
  if (weekday == 1)
    LCD_string(0x8C, "SUN");
  else if (weekday == 2)
    LCD_string(0x8C, "MON");
  else if (weekday == 3)
    LCD_string(0x8C, "TUE");
  else if (weekday == 4)
    LCD_string(0x8C, "WED");
  else if (weekday == 5)
    LCD_string(0x8C, "THU");
  else if (weekday == 6)
    LCD_string(0x8C, "FRI");
  else
    LCD_string(0x8C, "SAT");

  LCD_command(0xC2);                           // display hour
  hour = RTC_HOUR;
  LCD_2BCD(hour & 0x7F);
  LCD_command(0xCB);                           // display AM, PM
  if (hour < 0x80)
    LCD_data('A');
  else
    LCD_data('P');
  hour = hour & 0x7F;

  LCD_command(0xC5);                           // display minute
  minute = RTC_MINUTE;
  LCD_2BCD(minute);

  LCD_command(0xC8);                           // display second
  second = RTC_SECOND;
  LCD_2BCD(second);

  LCD_command(cursor);                         // go cursor position
  LCD_command(0x0F);                           // cursor ON
  Delay_ms(10);                                // time delay for cursor

  if ((minute == 0x00) && (second == 0x00)) {  // beep for each o'clock
    Beep();
    Delay_ms(950);
  }
}

unsigned char BCD_increment(unsigned char number)
{                                              /* BCD increment */
  unsigned char i;

  i = (number >> 4) * 10 + (number & 0x0F);    // convert BCD to binary
  i++;                                         // incrment
  i = ((i / 10) << 4) + (i % 10);              // convert binary to BCD
  return i;
}

unsigned char BCD_decrement(unsigned char number)
{                                              /* BCD decrement */
  unsigned char i;

  i = (number >> 4) * 10 + (number & 0x0F);    // convert BCD to binary
  i--;                                         // decrement
  i = ((i / 10) << 4) + (i % 10);              // convert binary to BCD
  return i;
}

void Cursor_left(void)
{                                              /* go cursor left */
  if (cursor == 0xCF)
    cursor = 0xCC;
  else if (cursor == 0xCC)
    cursor = 0xC9;
  else if (cursor == 0xC9)
    cursor = 0xC6;
  else if (cursor == 0xC6)
    cursor = 0xC3;
  else if (cursor == 0xC3)
    cursor = 0x8E;
  else if (cursor == 0x8E)
    cursor = 0x8A;
  else if (cursor == 0x8A)
    cursor = 0x87;
  else if (cursor == 0x87)
    cursor = 0x84;
  else if (cursor == 0x84)
    cursor = 0xCF;
}

void Cursor_right(void)
{                                              /* go cursor right */
  if (cursor == 0xCF)
    cursor = 0x84;
  else if (cursor == 0x84)
    cursor = 0x87;
  else if (cursor == 0x87)
    cursor = 0x8A;
  else if (cursor == 0x8A)
    cursor = 0x8E;
  else if (cursor == 0x8E)
    cursor = 0xC3;
  else if (cursor == 0xC3)
    cursor = 0xC6;
  else if (cursor == 0xC6)
    cursor = 0xC9;
  else if (cursor == 0xC9)
    cursor = 0xCC;
  else if (cursor == 0xCC)
    cursor = 0xCF;
}

void Increment(void)
{                                              /* increment time */
  unsigned char year, month, date, weekday, hour, minute, second;

  switch (cursor) {
  case 0x84:
    year = RTC_YEAR;                           // in case of year
    if (year == 0x99)
      year = 0x00;
    else
      year = BCD_increment(year);
    RTC_YEAR = year;
    break;
  case 0x87:
    month = RTC_MONTH;                         // in case of month
    if (month == 0x12)
      month = 0x01;
    else
      month = BCD_increment(month);
    RTC_MONTH = month;
    break;
  case 0x8A:
    date = RTC_DATE;                           // in case of date
    if (date == 0x31)
      date = 0x01;
    else
      date = BCD_increment(date);
    RTC_DATE = date;
    break;
  case 0x8E:
    weekday = RTC_WEEKDAY;                     // in case of weekday
    if (weekday == 0x07)
      weekday = 0x01;
    else
      weekday++;
    RTC_WEEKDAY = weekday;
    break;
  case 0xC3:
    hour = RTC_HOUR;                           // in case of hour
    if (hour == 0x12)
      hour = 0x01;
    else if (hour == 0x92)
      hour = 0x81;
    else
      hour = BCD_increment(hour);
    RTC_HOUR = hour;
    break;
  case 0xC6:
    minute = RTC_MINUTE;                       // in case of minute
    if (minute == 0x59)
      minute = 0x00;
    else
      minute = BCD_increment(minute);
    RTC_MINUTE = minute;
    break;
  case 0xC9:
    second = RTC_SECOND;                       // in case of second
    if (second == 0x59)
      second = 0x00;
    else
      second = BCD_increment(second);
    RTC_SECOND = second;
    break;
  case 0xCC:
    hour = RTC_HOUR;                           // in case of AM/PM
    if (hour < 0x80)
      hour |= 0x80;
    else
      hour &= 0x7F;
    RTC_HOUR = hour;
    break;
  default:
    break;
  }
}

void Decrement(void)
{                                              /* decrement time */
  unsigned char year, month, date, weekday, hour, minute, second;

  switch (cursor) {
  case 0x84:
    year = RTC_YEAR;                           // in case of year
    if (year == 0x00)
      year = 0x99;
    else
      year = BCD_decrement(year);
    RTC_YEAR = year;
    break;
  case 0x87:
    month = RTC_MONTH;                         // in case of month
    if (month == 0x01)
      month = 0x12;
    else
      month = BCD_decrement(month);
    RTC_MONTH = month;
    break;
  case 0x8A:
    date = RTC_DATE;                           // in case of date
    if (date == 0x01)
      date = 0x31;
    else
      date = BCD_decrement(date);
    RTC_DATE = date;
    break;
  case 0x8E:
    weekday = RTC_WEEKDAY;                     // in case of weekday
    if (weekday == 0x01)
      weekday = 0x07;
    else
      weekday--;
    RTC_WEEKDAY = weekday;
    break;
  case 0xC3:
    hour = RTC_HOUR;                           // in case of hour
    if (hour == 0x01)
      hour = 0x12;
    else if (hour == 0x81)
      hour = 0x92;
    else
      hour = BCD_decrement(hour);
    RTC_HOUR = hour;
    break;
  case 0xC6:
    minute = RTC_MINUTE;                       // in case of minute
    if (minute == 0x00)
      minute = 0x59;
    else
      minute = BCD_decrement(minute);
    RTC_MINUTE = minute;
    break;
  case 0xC9:
    second = RTC_SECOND;                       // in case of second
    if (second == 0x00)
      second = 0x59;
    else
      second = BCD_decrement(second);
    RTC_SECOND = second;
    break;
  case 0xCC:
    hour = RTC_HOUR;                           // in case of AM/PM
    if (hour < 0x80)
      hour |= 0x80;
    else
      hour &= 0x7F;
    RTC_HOUR = hour;
    break;
  default:
    break;
  }
}

void main(void)
{
  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, " Digital Clock  ");        // display logo
  LCD_string(0xC0, "  by DS12C887   ");
  Delay_ms(2000);

  if (RTC_FLAG != 'G') {                       // RTC data are available ?
    Beep();
    Delay_ms(100);
    Beep();
    RTC_FLAG = 'G';                            // initialize RTC data flag
    RTC_YEAR = 0x06;                           // initialize year(2006)
    RTC_MONTH = 0x01;                          // initialize month(01)
    RTC_DATE = 0x01;                           // initialize date(01)
    RTC_WEEKDAY = 0x01;                        // initialize weekday(SUN)
    RTC_HOUR = 0x12;                           // initialize hour(12)
    RTC_MINUTE = 0x00;                         // initialize minute(00)
    RTC_SECOND = 0x00;                         // initialize second(00)
    RTC_A = 0x2F;                              // oscillator ON, SQW=2Hz
    RTC_B = 0x00;                              // interrupt disable, SQW disable
  } else
    Beep();

  LCD_string(0x80, " 2006/01/01 SUN ");        // display title
  LCD_string(0xC0, "  12:00:00 AM   ");
  LCD_command(0x0F);                           // cursor ON, cursor blink
  cursor = 0xCF;                               // initial cursor position

  while (1) {
    DSP_RTC();                                 // display clock

    switch (Key_input()) {                     // key input
    case 0x0E:
      Cursor_left();                           // if KEY4, go cursor left
      break;
    case 0x16:
      Cursor_right();                          // if KEY3, go cursor right
      break;
    case 0x1A:
      Increment();                             // if KEY2, increment time
      break;
    case 0x1C:
      Decrement();                             // if KEY1, decrement time
      break;
    default:
      break;
    }
  }
}
