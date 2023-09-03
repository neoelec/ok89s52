/* ========================================================================== */
/*               Exp16_2.c : A/D Conversion by Averaging Method               */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

void LCD_2hex(unsigned char number)
{                                              /* display HEX number xxH */
  unsigned char i;

  i = number >> 4;                             // 16^1
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');

  i = number & 0x0F;                           // 16^0
  if (i <= 9)
    LCD_data(i + '0');
  else
    LCD_data(i - 10 + 'A');
}

void main(void)
{
  unsigned char i;
  unsigned int sum;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, " A/D CH0 = 00H  ");        // display title
  LCD_string(0xC0, " A/D CH1 = 00H  ");

  T2CON = 0x04;                                // TR2=1, C/-T2=0
  T2MOD = 0x02;                                // programmable clock out mode
  RCAP2H = 65530 >> 8;                         // clock = 1MHz
  RCAP2L = 65530 & 0x00FF;
  TH2 = 65530 >> 8;
  TL2 = 65530 & 0x00FF;
  Delay_ms(100);                               // wait for ADC stabilization

  while (1) {
    LCD_command(0x8B);                         // cursor position
    sum = 0;                                   // clear total sum
    for (i = 1; i <= 16; i++) {
      ADC_CH0 = 0;                             // select and start ADC0809 IN0
      Delay_us(100);
      sum += ADC_READ;                         // add A/D result to total sum
      Delay_ms(1);                             // delay for interval
    }
    sum >>= 4;                                 // calculate average
    LCD_2hex(sum);                             // display A/D result in hex

    LCD_command(0xCB);                         // cursor position
    sum = 0;                                   // clear total sum
    for (i = 1; i <= 16; i++) {
      ADC_CH1 = 0;                             // select and start ADC0809 IN1
      Delay_us(100);
      sum += ADC_READ;                         // add A/D result to total sum
      Delay_ms(1);                             // delay for interval
    }
    sum >>= 4;                                 // calculate average
    LCD_2hex(sum);                             // display A/D result in hex

    Delay_ms(200);
  }
}
