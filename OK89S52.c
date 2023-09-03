/*                           OK89S52.H : Designed by Duck-Yong Yoon in 2005.  */
/* -------------------------------------------------------------------------- */
/*        OK-89S52 Kit I/O Address                                            */
/* -------------------------------------------------------------------------- */

#include <at89s52.h>
#include "OK89S52.h"

/* -------------------------------------------------------------------------- */
/*        OK-89S52 Kit User-defined Function                                  */
/* -------------------------------------------------------------------------- */

void Kit_initialize(void)
{                                              /* initialize OK-89S52 kit */
  P3_5 = 1;                                    // buzzer off
  SEG_PATTERN = 0x00;                          // clear 7-segment LED
  DIG_SELECT = 0x00;
}

void Delay_us(unsigned char us)
{                                              /* time delay for us[us] */
  unsigned char i;

  us = us >> 2;
  for (i = 1; i <= us; i++) ;
}

void Delay_ms(unsigned int ms)
{                                              /* time delay for ms[ms] */
  unsigned int i, j;

  for (i = 1; i <= ms; i++)
    for (j = 1; j <= 250; j++) ;
}

void Beep(void)
{                                              /* beep sound for 50 ms */
  P3_5 = 0;
  Delay_ms(50);
  P3_5 = 1;
}

static unsigned char key_flag = 0;

unsigned char Key_input(void)
{                                              /* input key switch KEY4 - KEY1 */
  unsigned char key;

  key = P1 & 0x1E;                             // any key pressed ?
  if (key == 0x1E) {                           // if no key, check key off
    if (key_flag == 0)
      return key;
    else {
      Delay_ms(20);
      key_flag = 0;
      return key;
    }
  } else {                                     // if key input, check continuous key
    if (key_flag != 0)                         // if continuous key, treat as no key input
      return 0x1E;
    else {                                     // if new key, beep and delay for debounce
      Beep();
      key_flag = 1;
      return key;
    }
  }
}

void LCD_command(char command)
{                                              /* write a command on text LCD */
  LCD_WR_INST = command;
  Delay_us(50);
}

void LCD_data(char character)
{                                              /* display a character on text LCD */
  LCD_WR_DATA = character;
  Delay_us(50);
}

void LCD_string(char command, char *string)
{                                              /* display a string on text LCD */
  LCD_command(command);
  while (*string != '\0') {
    LCD_data(*string);
    string++;
  }
}

void LCD_initialize(void)
{                                              /* initialize text LCD module */
  LCD_command(0x38);                           // function set(8 bit, 2 line, 5x7 dot)
  LCD_command(0x0C);                           // display control(display ON, cursor OFF)
  LCD_command(0x06);                           // entry mode set(increment, not shift)
  LCD_command(0x01);                           // clear display
  Delay_ms(2);

  Key_input();                                 // dummy function call to avoid warning
}
