/* ========================================================================== */
/*               Exp15_2.c : RS-232C Communication by Interrupt               */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "AT89S52.H"                           // include AT89S52 definition file
#include "OK89S52.H"                           // include OK-89S52 kit function

unsigned char cursor;                          // LCD cursor position

void TXD_char(unsigned char character)
{                                              /* transmit a character */
  while (!TI) ;                                // transmit ready ?
  TI = 0;                                      // if yes, TI=0
  SBUF = character;                            //      and transmit a character
}

void TXD_string(char *string)
{                                              /* transmit a string */
  while (*string != '\0') {
    TXD_char(*string);
    string++;
  }
}

void TIRI_ISR(void) interrupt 4                /* serial int. service routine */
{
  if (RI) {                                    // receive ready ?
    LCD_data(SBUF);                            // if yes, receive and RI=0
    RI = 0;                                    //      and display a character
    cursor += 1;                               // 16 characters OK ?
    if (cursor == 17) {
      LCD_command(0xC0);                       // if yes, go first column
      cursor = 1;
      Beep();
    }
  }
}

void main(void)
{
  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module
  Beep();

  LCD_string(0x80, "    RS-232C     ");        // display title
  LCD_string(0xC0, "                ");

  T2CON = 0x34;                                // TCLK=RCLK=1, TR2=1, C/-T2=0
  T2MOD = 0x00;                                // (baud rate generator)
  RCAP2H = 65497 >> 8;                         // 19200 bps
  RCAP2L = 65497 & 0x00FF;
  SCON = 0x52;                                 // 8 data, 1 stop, REN=TI=1
  cursor = SBUF;                               // dummy read(clear SBUF)

  IP = 0x10;                                   // interrupt priority
  IE = 0x90;                                   // EA=ES=1

  LCD_command(0x0F);                           // cursor ON
  LCD_command(0xC0);                           // initialize cursor position
  cursor = 1;

  while (1) {
    switch (Key_input()) {                     // key input
    case 0x1C:
      DIG_SELECT = 0x01;
      TXD_string("KEY1 was pressed.");
      TXD_char(0x0D);
      TXD_char(0x0A);
      break;
    case 0x1A:
      DIG_SELECT = 0x02;
      TXD_string("KEY2 was pressed.");
      TXD_char(0x0D);
      TXD_char(0x0A);
      break;
    case 0x16:
      DIG_SELECT = 0x04;
      TXD_string("KEY3 was pressed.");
      TXD_char(0x0D);
      TXD_char(0x0A);
      break;
    case 0x0E:
      DIG_SELECT = 0x08;
      TXD_string("KEY4 was pressed.");
      TXD_char(0x0D);
      TXD_char(0x0A);
      break;
    default:
      break;
    }
  }
}
