/* ========================================================================== */
/*              Exp17_5.c : D/A Converter Output Voltage by Key               */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "AT89S52.H"                           // include AT89S52 definition file
#include "OK89S52.H"                           // include OK-89S52 kit function

LCD_2hex(unsigned char number)
{                                              /* display HEX number xxH */
  unsigned char i;

  i = (number >> 4) & 0x0F;                    // 16^1
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

LCD_s2d1(unsigned char number)
{                                              /* display signed real number +xx.x */
  unsigned char i;
  unsigned int j;
  float voltage;

  if (number >= 0x80) {                        // positive
    number = number - 0x80;
    LCD_data('+');
  } else {                                     // negative
    number = 0x80 - number;
    LCD_data('-');
  }

  voltage = number * 10. / 128.;               // calculate voltage

  j = (int)(voltage * 10. + 0.5);
  i = j / 100;                                 // 10^1
  if (i == 0)
    LCD_data(' ');
  else
    LCD_data(i + '0');
  i = j % 100;
  LCD_data(i / 10 + '0');                      // 10^0
  LCD_data('.');
  LCD_data(i % 10 + '0');                      // 10^-1
}

main()
{
  unsigned char volt;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, "   D/A Output   ");        // display title
  LCD_string(0xC0, " 80H = +00.0[V] ");

  volt = 0x80;                                 // initial voltage 0.0[V]
  DAC_CS = volt;

  while (1) {
    switch (Key_input()) {                     // key input
    case 0x1C:
      volt += 0x10;                            // if KEY1, increment by 0x10
      DAC_CS = volt;
      break;
    case 0x1A:
      volt -= 0x10;                            // if KEY2, decrement by 0x10
      DAC_CS = volt;
      break;
    case 0x16:
      volt += 0x01;                            // if KEY3, increment by 0x01
      DAC_CS = volt;
      break;
    case 0x0E:
      volt -= 0x01;                            // if KEY4, decrement by 0x01
      DAC_CS = volt;
      break;
    default:
      break;
    }

    LCD_command(0xC1);                         // display D/A in HEX format
    LCD_2hex(volt);
    LCD_command(0xC7);                         // display D/A voltage
    LCD_s2d1(volt);
  }
}
