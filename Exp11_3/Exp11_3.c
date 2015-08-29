/* ========================================================================== */
/*             Exp11_3.c : 7-Segment LED Display - Numerical Data             */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <at89s52.h>                            // include AT89S52 definition file
#include <OK89S52.h>                            // include OK-89S52 kit function

static void LCD_2hex(uint8_t number)
{                                               /* display 2-digit hex number */
    uint8_t i;

    i = (number >> 4) & 0x0F;                   // 16^1
    if (i <= 9)
        LCD_data(i + '0');
    else
        LCD_data(i - 10 + 'A');

    i = number & 0x0F;                          // 16^0
    if (i <= 9)
        LCD_data(i + '0');
    else
        LCD_data(i - 10 + 'A');
}

static void LCD_3d(uint16_t number)
{                                               /* display 3-digit decimal number */
    uint8_t i, flag;

    flag = 0;
    i = number / 100;                           // 10^2
    if (i == 0)
        LCD_data(' ');
    else {
        LCD_data(i + '0');
        flag = 1;
    }

    number = number % 100;                      // 10^1
    i = number / 10;
    if ((i == 0) && (flag == 0))
        LCD_data(' ');
    else {
        LCD_data(i + '0');
        flag = 1;
    }

    i = number % 10;                            // 10^0
    LCD_data(i + '0');
}

static uint8_t Bin2LED(uint8_t number)
{                                               /* convert binary to LED pattern */
    if (number == 0)
        return 0xFC;
    else if (number == 1)
        return 0x60;
    else if (number == 2)
        return 0xDA;
    else if (number == 3)
        return 0xF2;
    else if (number == 4)
        return 0x66;
    else if (number == 5)
        return 0xB6;
    else if (number == 6)
        return 0xBE;
    else if (number == 7)
        return 0xE4;
    else if (number == 8)
        return 0xFE;
    else if (number == 9)
        return 0xF6;
    else if (number == 10)
        return 0xEE;
    else if (number == 11)
        return 0x3E;
    else if (number == 12)
        return 0x9C;
    else if (number == 13)
        return 0x7A;
    else if (number == 14)
        return 0x9E;
    else if (number == 15)
        return 0x8E;
    else if (number == 'H')
        return 0x6E;
    else if (number == '-')
        return 0x02;
    else if (number == '.')
        return 0x01;
    else if (number == 0x27)
        return 0x40;
    else
        return 0x00;
}

static uint8_t pattern[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };   // 7-segment LED pattern data

static void LED_2hex(uint8_t number)
{                                               /* display 2-digit hex number */
    pattern[0] = Bin2LED(number >> 4);          // 16^1
    pattern[1] = Bin2LED(number & 0x0F);        // 16^0
    pattern[2] = Bin2LED('H');
}

static void LED_3d(uint16_t number)
{                                               /* display 3-digit decimal number */
    uint8_t i, flag;

    flag = 0;
    i = number / 100;                           // 10^2
    if (i == 0)
        pattern[5] = 0x00;
    else {
        pattern[5] = Bin2LED(i);
        flag = 1;
    }

    number = number % 100;                      // 10^1
    i = number / 10;
    if ((i == 0) && (flag == 0))
        pattern[6] = 0x00;
    else {
        pattern[6] = Bin2LED(i);
        flag = 1;
    }

    i = number % 10;                            // 10^0
    pattern[7] = Bin2LED(i);
}

void main(void)
{
    uint8_t i, j, k, digit;

    Kit_initialize();                           // initialize OK-89S52 kit
    Delay_ms(50);                               // wait for system stabilization
    LCD_initialize();                           // initialize text LCD module
    Beep();

    LCD_string(0x80, "   LCD & LED    ");       // display title
    LCD_string(0xC0, "   00H = 000    ");

    while (1) {
        for (i = 1; i > 0; i++) {               // display from 1 to 255
            LCD_command(0xC3);                  // display hexadecimal on LCD
            LCD_2hex(i);
            LCD_command(0xC9);                  // display decimal on LCD
            LCD_3d(i);

            LED_2hex(i);                        // convert hex to LED pattern
            LED_3d(i);                          // convert decimal to LED pattern

            for (j = 1; j <= 125; j++)          // display 7-segment LED
                for (k = 0, digit = 0x80; k <= 7; k++) {
                    SEG_PATTERN = pattern[k];   // output segment pattern data
                    DIG_SELECT = digit;         // output digit select data
                    Delay_ms(1);                // delay 1ms
                    digit >>= 1;
                }
        }
    }
}
