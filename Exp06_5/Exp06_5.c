/* ========================================================================== */
/*                      Exp06_5.c : Bit Shift Left/Right                      */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "AT89S52.H"                           // include AT89S52 definition file
#include "OK89S52.H"                           // include OK-89S52 kit function

void LCD_8bin(unsigned char number)
{                                              /* display 8-bit binary number */
  LCD_data(((number >> 7) & 0x01) + '0');      // 2^7
  LCD_data(((number >> 6) & 0x01) + '0');      // 2^6
  LCD_data(((number >> 5) & 0x01) + '0');      // 2^5
  LCD_data(((number >> 4) & 0x01) + '0');      // 2^4
  LCD_data(((number >> 3) & 0x01) + '0');      // 2^3
  LCD_data(((number >> 2) & 0x01) + '0');      // 2^2
  LCD_data(((number >> 1) & 0x01) + '0');      // 2^1
  LCD_data((number & 0x01) + '0');             // 2^0
}

void main(void)
{
  unsigned char i, x, LED;
  signed char y;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  while (1) {
    Beep();
    LCD_string(0x80, "        10011101");      // display title
    LCD_string(0xC0, " << 0 = 00000000");

    x = 0x9D;                                  // unsigned char
    for (i = 0; i <= 8; i++) {                 // shift left
      LCD_command(0xC4);
      LCD_data(i + '0');
      LCD_command(0xC8);
      LCD_8bin(x);
      Delay_ms(2000);
      x <<= 1;
    }

    Beep();
    LCD_string(0x80, "        10011101");      // display title
    LCD_string(0xC0, " >> 0 = 00000000");

    x = 0x9D;                                  // unsigned char
    for (i = 0; i <= 8; i++) {                 // shift right
      LCD_command(0xC4);
      LCD_data(i + '0');
      LCD_command(0xC8);
      LCD_8bin(x);
      Delay_ms(2000);
      x >>= 1;
    }

    Beep();
    LCD_string(0x80, " signed 10011101");      // display title
    LCD_string(0xC0, " >> 0 = 00000000");

    y = 0x9D;                                  // signed char
    for (i = 0; i <= 8; i++) {                 // shift right
      LCD_command(0xC4);
      LCD_data(i + '0');
      LCD_command(0xC8);
      LCD_8bin(y);
      Delay_ms(2000);
      y >>= 1;
    }

    Beep();
    LCD_string(0x80, " signed 01011101");      // display title
    LCD_string(0xC0, " >> 0 = 00000000");

    y = 0x5D;                                  // signed char
    for (i = 0; i <= 8; i++) {                 // shift right
      LCD_command(0xC4);
      LCD_data(i + '0');
      LCD_command(0xC8);
      LCD_8bin(y);
      Delay_ms(2000);
      y >>= 1;
    }

    for (i = 1, LED = 0x01; i <= 5; i++) {     // shift from LED1 to LED4
      DIG_SELECT = LED;
      Delay_ms(500);
      LED <<= 1;
    }
  }
}
