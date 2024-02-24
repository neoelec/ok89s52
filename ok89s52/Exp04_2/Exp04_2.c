/* ========================================================================== */
/*                Exp04_2.c : Hardware Time Delay Application                 */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include <OK89S52.h>                           // include OK-89S52 kit function

void Timer0_ms(unsigned int ms)
{                                              /* time delay for ms[ms] */
  unsigned i, time;

  if (ms == 0)
    return;

  TMOD &= 0xF0;                                // Timer 0, mode 1
  TMOD |= 0x01;
  TR0 = 1;                                     // Timer 0 run enable

  for (i = 1; i <= ms; i++) {
    TH0 = 0x00;                                // initial Timer 0 value
    TL0 = 0x00;
    time = 0;
    while (time < 2000)                        // TH0:TL0 = 2000 ?
      time = TH0 * 256 + TL0;
  }
}

void main(void)
{
  unsigned char mode, LED;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, " H/W Time Delay ");        // display title
  LCD_string(0xC0, "Press KEY4-KEY1!");

  mode = 1;                                    // initial speed mode
  LED = 0x05;                                  // initial LED data

  while (1) {
    switch (Key_input()) {                     // key input
    case 0x1C:
      mode = 1;
      LCD_string(0xC0, "    100 [ms]    ");
      break;
    case 0x1A:
      mode = 2;
      LCD_string(0xC0, "    200 [ms]    ");
      break;
    case 0x16:
      mode = 3;
      LCD_string(0xC0, "    300 [ms]    ");
      break;
    case 0x0E:
      mode = 4;
      LCD_string(0xC0, "    400 [ms]    ");
      break;
    default:
      LED ^= 0x0F;                             // output LED with complement
      DIG_SELECT = LED;
      if (mode == 1)
        Timer0_ms(100);
      else if (mode == 2)
        Timer0_ms(200);
      else if (mode == 3)
        Timer0_ms(300);
      else
        Timer0_ms(400);
      break;
    }
  }
}
