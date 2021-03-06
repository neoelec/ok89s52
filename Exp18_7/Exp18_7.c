/* ========================================================================== */
/*                  Exp18_7.c : Use printf() for Serial Port                  */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <at89s52.h>                            // include AT89S52 definition file
#include <OK89S52.h>                            // include OK-89S52 kit function

static void TXD_char(uint8_t character)
{                                               /* transmit a character */
    while (!TI) ;                               // transmit ready ?
    TI = 0;                                     // if yes, TI=0
    SBUF = character;                           //      and transmit a character
}

int putchar(int ch)
{
    if (ch == '\n')
        TXD_char((uint8_t)'\r');
    TXD_char((uint8_t)ch);

    return ch;
}

static void LCD_s3d(int number)
{                                               /* display signed decimal number +xxx */
    signed int i;
    uint8_t flag;

    flag = 0;

    if (number >= 0)
        LCD_data('+');                          // sign
    else
        LCD_data('-');

    number = abs(number);

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
    else
        LCD_data(i + '0');

    i = number % 10;                            // 10^0
    LCD_data(i + '0');
}

static void LCD_s1d3(float number)
{                                               /* display signed real number +x.xxx */
    uint16_t i, j;

    if (number >= 0.0)
        LCD_data('+');                          // sign
    else
        LCD_data('-');

    number = fabsf(number);
    j = (int)(number * 1000. + 0.5);

    i = j / 1000;                               // 10^0
    LCD_data(i + '0');
    LCD_data('.');

    j = j % 1000;                               // 10^-1
    i = j / 100;
    LCD_data(i + '0');

    j = j % 100;                                // 10^-2
    i = j / 10;
    LCD_data(i + '0');

    i = j % 10;                                 // 10^-3
    LCD_data(i + '0');
}

void main(void)
{
    signed int i;
    float x, y;

    Kit_initialize();                           // initialize OK-89S52 kit
    Delay_ms(50);                               // wait for system stabilization
    LCD_initialize();                           // initialize text LCD module

    LCD_string(0x80, "sin(+000)=+0.000");       // display title
    LCD_string(0xC0, "cos(+000)=+0.000");

    T2CON = 0x34;                               // TCLK=RCLK=1, TR2=1, C/-T2=0
    T2MOD = 0x00;                               // (baud rate generator)
    RCAP2H = (uint8_t)(65497 >> 8);             // 19200 bps
    RCAP2L = (uint8_t)(65497 & 0x00FF);
    SCON = 0x52;                                // 8 data, 1 stop, REN=TI=1
    i = SBUF;                                   // dummy read(clear SBUF)

    while (1) {
        Beep();
        for (i = -360; i <= +360; i += 30) {
            x = i * 3.141592654 / 180.;
            y = sinf(x);
            LCD_command(0x84);
            LCD_s3d(i);                         // display sin()
            LCD_command(0x8A);
            LCD_s1d3(y);
            printf_fast_f("sin(%c%03d)=%c%1.3f\n",
                    i >= 0 ? '+' : '-', abs(i),
                    y >= 0. ? '+' : '-', fabsf(y));  // printf for sin output
            y = cosf(x);
            LCD_command(0xC4);
            LCD_s3d(i);                         // display cos()
            LCD_command(0xCA);
            LCD_s1d3(cosf(x));
            printf_fast_f("cos(%c%03d)=%c%1.3f\n\n",
                    i >= 0 ? '+' : '-', abs(i),
                    y >= 0. ? '+' : '-', fabsf(y));  // printf for cos output
            Delay_ms(2000);
        }
    }
}
