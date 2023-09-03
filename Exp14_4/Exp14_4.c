/* ========================================================================== */
/*                  Exp14_4.c : Digital Clock with Calendar                   */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "AT89S52.H"                           // include AT89S52 definition file
#include "OK89S52.H"                           // include OK-89S52 kit function

unsigned char cursor;                          // cursor position
unsigned char year;                            // year
unsigned char month;                           // month
unsigned char date;                            // date
unsigned char hour;                            // hour
unsigned char minute;                          // minute
unsigned char second;                          // second
unsigned char old_second;                      // old second
unsigned char blink;                           //

LCD_2BCD(unsigned char number)
{                                              /* display 2-digit BCD number */
  unsigned char i;

  i = (number >> 4) & 0x0F;                    // 10^1
  LCD_data(i + '0');

  i = number & 0x0F;                           // 10^0
  LCD_data(i + '0');
}

DSP_RTC()
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
  Delay_ms(2);                                 // time delay for cursor

  if ((minute == 0x00) && (second == 0x00)) {  // beep for each o'clock
    Beep();
    Delay_ms(950);
  }
}

unsigned char Bin2LED(unsigned char number)
{                                              /* convert binary to LED pattern */
  if (number == 0)
    return 0xFC;
  else if (number == 1)
    return 0x60;
  else if (number == 2)
    return 0xDA;
  else if (number == 3)
    return 0xF2;
  else if (number == 4)
    return 0x66;
  else if (number == 5)
    return 0xB6;
  else if (number == 6)
    return 0xBE;
  else if (number == 7)
    return 0xE4;
  else if (number == 8)
    return 0xFE;
  else if (number == 9)
    return 0xF6;
  else if (number == 10)
    return 0xEE;
  else if (number == 11)
    return 0x3E;
  else if (number == 12)
    return 0x9C;
  else if (number == 13)
    return 0x7A;
  else if (number == 14)
    return 0x9E;
  else if (number == 15)
    return 0x8E;
  else if (number == 'H')
    return 0x6E;
  else if (number == '-')
    return 0x02;
  else if (number == '.')
    return 0x01;
  else if (number == 0x27)
    return 0x40;
  else
    return 0x00;
}

DSP_LED()
{                                              /* display clock on LED */
  unsigned char i;

  if (second == old_second)                    // check 0.5 sec
    blink++;
  else {
    blink = 0;
    old_second = second;
  }

  i = second & 0x1F;
  if ((i < 0x11) || (i > 0x15)) {
    SEG_PATTERN = Bin2LED(hour >> 4);          // display hour
    DIG_SELECT = 0x80;
    Delay_ms(1);
    SEG_PATTERN = Bin2LED(hour & 0x0F);
    DIG_SELECT = 0x40;
    Delay_ms(1);
    if (blink < 50)
      SEG_PATTERN = Bin2LED('-');              // if before 0.5 sec, display "-"
    else
      SEG_PATTERN = 0x00;                      // if after 0.5 sec, display " "
    DIG_SELECT = 0x20;
    Delay_ms(1);
    SEG_PATTERN = Bin2LED(minute >> 4);        // display minute
    DIG_SELECT = 0x10;
    Delay_ms(1);
    SEG_PATTERN = Bin2LED(minute & 0x0F);
    DIG_SELECT = 0x08;
    Delay_ms(1);
    if (blink < 50)
      SEG_PATTERN = Bin2LED('-');              // if before 0.5 sec, display "-"
    else
      SEG_PATTERN = 0x00;                      // if after 0.5 sec, display " "
    DIG_SELECT = 0x04;
    Delay_ms(1);
    SEG_PATTERN = Bin2LED(second >> 4);        // display second
    DIG_SELECT = 0x02;
    Delay_ms(1);
    SEG_PATTERN = Bin2LED(second & 0x0F);
    DIG_SELECT = 0x01;
    Delay_ms(1);
  } else {
    SEG_PATTERN = Bin2LED(0x20 >> 4);          // display year
    DIG_SELECT = 0x80;
    Delay_ms(1);
    SEG_PATTERN = Bin2LED(0x20 & 0x0F);
    DIG_SELECT = 0x40;
    Delay_ms(1);
    SEG_PATTERN = Bin2LED(year >> 4);
    DIG_SELECT = 0x20;
    Delay_ms(1);
    if (blink < 50)
      SEG_PATTERN = Bin2LED(year & 0x0F) + 0x01;
    else
      SEG_PATTERN = Bin2LED(year & 0x0F);
    DIG_SELECT = 0x10;
    Delay_ms(1);
    SEG_PATTERN = Bin2LED(month >> 4);         // display month
    DIG_SELECT = 0x08;
    Delay_ms(1);
    if (blink < 50)
      SEG_PATTERN = Bin2LED(month & 0x0F) + 0x01;
    else
      SEG_PATTERN = Bin2LED(month & 0x0F);
    DIG_SELECT = 0x04;
    Delay_ms(1);
    SEG_PATTERN = Bin2LED(date >> 4);          // display date
    DIG_SELECT = 0x02;
    Delay_ms(1);
    SEG_PATTERN = Bin2LED(date & 0x0F);
    DIG_SELECT = 0x01;
    Delay_ms(1);
  }

  DIG_SELECT = 0x00;                           // clear 7-segment LED
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

Cursor_left()
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

Cursor_right()
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

Increment()
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

Decrement()
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

main()
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
    DSP_RTC();                                 // display clock on LCD module
    DSP_LED();                                 // display clock on 7-segment LED

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
