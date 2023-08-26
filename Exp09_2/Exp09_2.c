/* ========================================================================== */
/*	              Exp09_2.c : Watchdog Timer - Timeout                    */
/* ========================================================================== */
/*			  Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "AT89S52.H"				// include AT89S52 definition file
#include "OK89S52.H"				// include OK-89S52 kit function

main()
{ unsigned char i,j,LED; 

  Kit_initialize();                             // initialize OK-89S52 kit
  Delay_ms(50);                                 // wait for system stabilization
  LCD_initialize();                             // initialize text LCD module
  Beep();

  LCD_string(0x80,"  Watchdog Off  ");		// display title
  LCD_string(0xC0,"                ");
  Delay_ms(1000);

  for(i=1, LED=0x01; i<=5; i++)			// shift LED by 500ms step
    { DIG_SELECT = LED;
      Delay_ms(500);
      LED <<= 1;
    }

  LCD_string(0x80,"  Watchdog On   ");		// display title
  LCD_string(0xC0,"    Timeout     ");
  Delay_ms(1000);

  while(1)
    { for(i=1, LED=0x01; i<=5; i++)		// shift LED by 100ms step
        { DIG_SELECT = LED;
          for(j=1; j<=10; j++)
            { WDTRST = 0x1E;			// reset watchdog timer
              WDTRST = 0xE1;
              Delay_ms(10);
            }
          LED <<= 1;
        }
    }
}

