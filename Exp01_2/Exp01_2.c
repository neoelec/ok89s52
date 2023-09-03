#include <at89s52.h>

#define SEG_PATTERN (*(unsigned char __xdata *)0x8100)
#define DIG_SELECT (*(unsigned char __xdata *)0x8200)

void Delay_ms(unsigned int ms)
{                                              /* time delay for ms[ms] */
  unsigned int i, j;

  for (i = 1; i <= ms; i++)
    for (j = 1; j <= 250; j++) ;
}

void main(void)
{                                              /* main function */
  unsigned char i, LED;

  SEG_PATTERN = 0x00;                          // 7-segment LED off

  while (1) {
    LED = 0x01;                                // shift from LED1 to LED4
    for (i = 1; i <= 4; i++) {
      DIG_SELECT = LED;
      Delay_ms(500);                           // delay 500 ms
      LED <<= 1;                               // shift left
    }
  }
}
