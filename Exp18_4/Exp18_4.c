/* ========================================================================== */
/*		      Exp18_4.c : Function Call by C Program		      */
/* ========================================================================== */
/*			  Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "AT89S52.H"				// include AT89S52 definition file

#define SEG_PATTERN   (*(unsigned char xdata *)0x8100)
#define DIG_SELECT    (*(unsigned char xdata *)0x8200)

Delay_ms(unsigned int ms)			/* time delay for ms[ms] */
{ unsigned int i, j;

  for(i = 1; i <= ms; i++)
    for(j = 1; j <= 250; j++);
}

Beep()						/* beep sound for 50 ms */
{ P3_5 = 0;
  Delay_ms(50);
  P3_5 = 1;
}

main()						/* main function */
{ unsigned char i, LED;

  SEG_PATTERN = 0x00;				// 7-segment LED off

  while(1)
    { LED = 0x01;				// shift from LED1 to LED4
      for(i=1; i<=4; i++)  
        { DIG_SELECT = LED;
          Delay_ms(500);			// delay 500 ms
          LED <<= 1;				// shift left
        }
      Beep();					// beep
    }
}

