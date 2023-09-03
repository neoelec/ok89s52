/* ========================================================================== */
/*               Exp16_3.c : Read Voltage Sensor by ADC0809 IN0               */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "AT89S52.H"                           // include AT89S52 definition file
#include "OK89S52.H"                           // include OK-89S52 kit function

LCD_1d1(float number)
{                                              /* display real number x.x */
  unsigned char i;
  unsigned int j;

  j = (int)(number * 10. + 0.5);
  i = j / 10;                                  // 10^0
  LCD_data(i + '0');
  LCD_data('.');
  i = j % 10;                                  // 10^-1
  LCD_data(i + '0');
}

main()
{
  unsigned char i;
  unsigned int sum;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, "  VR1 Voltage   ");        // display title
  LCD_string(0xC0, "     0.0[V]     ");

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
      ADC_CH0 = 0;                             // select and start ADC0809 IN0
      Delay_us(100);
      sum += ADC_READ;                         // add A/D result to total sum
      Delay_ms(1);                             // delay for interval
    }
    LCD_command(0xC5);                         // cursor position
    LCD_1d1((float)sum * 5. / 10. / 256.);     // display A/D result in x.x

    Delay_ms(200);
  }
}
