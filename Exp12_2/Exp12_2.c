/* ========================================================================== */
/*		    Exp12_2.c : Telephone Bell Sound                          */
/* ========================================================================== */
/*			  Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "AT89S52.H"				// include AT89S52 definition file
#include "OK89S52.H"				// include OK-89S52 kit function

main()
{ unsigned char i,j;

  Kit_initialize();                             // initialize OK-89S52 kit
  Delay_ms(50);                                 // wait for system stabilization
  LCD_initialize();                             // initialize text LCD module
  Beep();

  LCD_string(0x80,"  *  SOUND  *   ");		// display title
  LCD_string(0xC0," Telephone Bell ");

  T2CON = 0x04;					// TR2=1, C/-T2=0

  while(1)
    { for(i=1; i<=3; i++)			// repeat 3 times
        { T2MOD = 0x02;				// speaker on(T2OE=1)
          for(j=1; j<=20; j++)
            { RCAP2H = 46786 >> 8;		// 320Hz
              RCAP2L = 46786 & 0x00FF;
              Delay_ms(25);
              RCAP2H = 53036 >> 8;		// 480Hz
              RCAP2L = 53036 & 0x00FF;
              Delay_ms(25);
            }
          T2MOD = 0x00;				// speaker off(T2OE=0)
          Delay_ms(1000);
        }
      Delay_ms(2000);
    }
}

