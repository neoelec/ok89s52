/* ========================================================================== */
/*                       Exp03_1.c : Basic C Program (1)                      */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <stdint.h>

#include <at89s52.h>                            // include AT89S52 definition file

#define SEG_PATTERN   (*(uint8_t __xdata *)0x8100)  /* segment pattern data */
#define DIG_SELECT    (*(uint8_t __xdata *)0x8200)  /* digit select data */

#define LCD_WR_INST   (*(uint8_t __xdata *)0x8300)  /* LCD module */
#define LCD_WR_DATA   (*(uint8_t __xdata *)0x8301)

static void Kit_initialize(void)
{                                               /* initialize OK-89S52 kit */
    P3_5 = 1;                                   // buzzer off
    SEG_PATTERN = 0x00;                         // clear 7-segment LED
    DIG_SELECT = 0x00;
}

static void Delay_us(uint8_t us)
{                                               /* time delay for us[us] */
    uint8_t i;

    us = us >> 2;
    for (i = 1; i <= us; i++) ;
}

static void Delay_ms(uint16_t ms)
{                                               /* time delay for ms[ms] */
    uint16_t i, j;

    for (i = 1; i <= ms; i++)
        for (j = 1; j <= 250; j++) ;
}

static void Beep(void)
{                                               /* beep sound for 50 ms */
    P3_5 = 0;
    Delay_ms(50);
    P3_5 = 1;
}

static void LCD_command(char command)
{                                               /* write a command on text LCD */
    LCD_WR_INST = command;
    Delay_us(50);
}

static void LCD_data(char character)
{                                               /* display a character on text LCD */
    LCD_WR_DATA = character;
    Delay_us(50);
}

static void LCD_string(char command, char *string)
{                                               /* display a string on text LCD */
    LCD_command(command);
    while (*string != '\0') {
        LCD_data(*string);
        string++;
    }
}

static void LCD_initialize(void)
{                                               /* initialize text LCD module */
    LCD_command(0x38);                          // function set(8 bit, 2 line, 5x7 dot)
    LCD_command(0x0C);                          // display control(display ON, cursor OFF)
    LCD_command(0x06);                          // entry mode set(increment, not shift)
    LCD_command(0x01);                          // clear display
    Delay_ms(2);
}

void main(void)
{
    Kit_initialize();                           // initialize OK-89S52 kit
    Delay_ms(50);                               // wait for system stabilization
    LCD_initialize();                           // initialize text LCD module

    while (1) {
        Beep();

        LCD_string(0x80, " OK-89S52  V1.0 ");   // display logo 1
        LCD_string(0xC0, "D.Y.YOON in 2005");
        Delay_ms(2000);

        LCD_string(0x80, "  Ohm Book Co.  ");   // display logo 2
        LCD_string(0xC0, "Tel. 02-776-4868");
        Delay_ms(2000);
    }
}
