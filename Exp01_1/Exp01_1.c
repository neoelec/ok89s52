#include <stdint.h>

#include <at89s52.h>

#define SEG_PATTERN   (*(uint8_t __xdata *)0x8100)
#define DIG_SELECT    (*(uint8_t __xdata *)0x8200)

static void Delay_ms(uint16_t ms)
{                                               /* time delay for ms[ms] */
    uint16_t i, j;

    for (i = 1; i <= ms; i++)
        for (j = 1; j <= 230; j++) ;
}

void main(void)
{                                               /* main function */
    uint8_t LED = 0x03;

    SEG_PATTERN = 0x00;                         // 7-segment LED off

    while (1) {
        LED = LED ^ 0x0F;                       // blink LED4 - LED1
        DIG_SELECT = LED;
        Delay_ms(500);                          // delay 500 ms
    }
}
