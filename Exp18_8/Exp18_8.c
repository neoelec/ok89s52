/* ========================================================================== */
/*                Exp18_8.c : Use printf() for Text LCD Module                */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <at89s52.h>                            // include AT89S52 definition file
#include <OK89S52.h>                            // include OK-89S52 kit function

int putchar(int ch)
{
    LCD_data(ch);

    return 0;
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

    while (1) {
        Beep();
        for (i = -360; i <= 360; i += 30) {
            x = i * 3.141592654 / 180.;
            y = sinf(x);
            LCD_command(0x80);                  // display sin()
            printf_fast_f("sin(%c%03d)=%c%1.3f",
                    i >= 0 ? '+' : '-', abs(i),
                    y >= 0. ? '+' : '-', fabsf(y));  // printf for sin output
            y = cosf(x);
            LCD_command(0xC0);                  // display cos()
            printf_fast_f("cos(%c%03d)=%c%1.3f",
                    i >= 0 ? '+' : '-', abs(i),
                    y >= 0. ? '+' : '-', fabsf(y));  // printf for cos output
            Delay_ms(2000);
        }
    }
}
