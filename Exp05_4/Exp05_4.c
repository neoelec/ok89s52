/* ========================================================================== */
/*                 Exp05_4.c : Floating Point Number Display                  */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "at89s52.h"                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

void LCD_1d1(float number)
{                                              /* display floating point number x.x */
  unsigned char i, j;

  j = (int)(number * 10. + 0.5);
  i = j / 10;                                  // 10^0
  LCD_data(i + '0');
  LCD_data('.');
  i = j % 10;                                  // 10^-1
  LCD_data(i + '0');
}

void main(void)
{
  unsigned char i;
  unsigned int sum;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, "  VR1 Voltage   ");        // display title
  LCD_string(0xC0, "   + 0.0 [V]    ");

  T2CON = 0x04;                                // TR2=1, C/-T2=0
  T2MOD = 0x02;                                // clock on
  RCAP2H = 65528 >> 8;
  RCAP2L = 65528 & 0xFF;
  Delay_ms(100);

  while (1) {
    LCD_command(0xC5);                         // set cursor position
    sum = 0;                                   // clear total value
    for (i = 1; i <= 10; i++) {
      ADC_CH0 = 0;                             // select ADC0 and start
      Delay_us(200);
      sum += ADC_READ;                         // read A/D data
    }
    i = sum / 10;                              // display voltage x.x [V]
    LCD_1d1((float)i * 5. / 256.);

    Delay_ms(200);
  }
}
