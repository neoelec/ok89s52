/* ========================================================================== */
/*                   Exp18_4.c : Function Call by C Program                   */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <stdint.h>

#include <at89s52.h>                            // include AT89S52 definition file

#define SEG_PATTERN   (*(uint8_t __xdata *)0x8100)
#define DIG_SELECT    (*(uint8_t __xdata *)0x8200)

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

void main(void)
{                                               /* main function */
    uint8_t i, LED;

    SEG_PATTERN = 0x00;                         // 7-segment LED off

    while (1) {
        LED = 0x01;                             // shift from LED1 to LED4
        for (i = 1; i <= 4; i++) {
            DIG_SELECT = LED;
            Delay_ms(500);                      // delay 500 ms
            LED <<= 1;                          // shift left
        }
        Beep();                                 // beep
    }
}
