/* ========================================================================== */
/*		    Exp18_3.c : Inline Assemble in C Program		      */
/* ========================================================================== */
/*			  Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "AT89S52.H"				// include AT89S52 definition file
#include "OK89S52.H"				// include OK-89S52 kit function

unsigned char LED;

main()
{ unsigned char i;

  Kit_initialize();                             // initialize OK-89S52 kit
  Delay_ms(50);                                 // wait for system stabilization
  LCD_initialize();                             // initialize text LCD module
  Beep();

  LCD_string(0x80,"Inline Assemble ");		// display title
  LCD_string(0xC0,"   LED Shift    ");

  while(1)
    { LED = 0x01;
      for(i = 1; i <= 4; i++)			// LED from 1 to 4
        { 
          #pragma asm
           LED_CS EQU 8200H			; LED4-LED1 output address
           MOV    DPTR,#LED_CS
           MOV    A,LED				; LED is global variable 
           MOVX   @DPTR,A
          #pragma endasm
           Delay_ms(300);
           LED <<= 1;
        }

      LED = 0x08;
      for(i = 1; i <= 4; i++)			// LED from 4 to 1
        { 
          #pragma asm
           MOV    DPTR,#LED_CS
           MOV    A,LED				; LED is global variable 
           MOVX   @DPTR,A
          #pragma endasm
           Delay_ms(300);
           LED >>= 1; 
        }
    }
}

