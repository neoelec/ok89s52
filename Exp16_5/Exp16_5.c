/* ========================================================================== */
/*                Exp16_5.c : Read Light Sensor by ADC0809 IN2                */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                           // include AT89S52 definition file
#include "OK89S52.h"                           // include OK-89S52 kit function

void LCD_2d(unsigned char number)
{                                              /* display 2-digit decimal number */
  unsigned char i;

  i = number / 10;                             // 10^1
  if (i == 0)
    LCD_data(' ');
  else
    LCD_data(i + '0');

  i = number % 10;                             // 10^0
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

  LCD_string(0x80, "  Light Sensor  ");        // display title
  LCD_string(0xC0, "00% :           ");

  T2CON = 0x04;                                // TR2=1, C/-T2=0
  T2MOD = 0x02;                                // programmable clock out mode
  RCAP2H = 65530 >> 8;                         // clock = 1MHz
  RCAP2L = 65530 & 0x00FF;
  TH2 = 65530 >> 8;
  TL2 = 65530 & 0x00FF;
  Delay_ms(100);                               // wait for ADC stabilization

  while (1) {
    sum = 0;                                   // clear total sum
    for (i = 1; i <= 10; i++) {
      ADC_CH2 = 0;                             // select and start ADC0809 IN2
      Delay_us(100);
      sum += ADC_READ;                         // add A/D result to total sum
      Delay_ms(1);                             // delay for interval
    }
    LCD_command(0xC0);                         // cursor position
    i = (sum / 10) * 100 / 255;                // calculate %
    LCD_2d(i);                                 // display %

    if (i < 25)                                // display light message
      LCD_string(0xC6, "Very dark ");
    else if (i < 50)
      LCD_string(0xC6, "  Dark    ");
    else if (i < 75)
      LCD_string(0xC6, "  Light   ");
    else
      LCD_string(0xC6, "Very light");

    Delay_ms(200);
  }
}
