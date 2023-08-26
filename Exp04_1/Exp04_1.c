/* ========================================================================== */
/*	          Exp04_1.c : Software Time Delay Application                 */
/* ========================================================================== */
/*			  Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "AT89S52.H"				// include AT89S52 definition file
#include "OK89S52.H"				// include OK-89S52 kit function

main()
{ unsigned char mode, LED;

  Kit_initialize();                             // initialize OK-89S52 kit
  Delay_ms(50);                                 // wait for system stabilization
  LCD_initialize();                             // initialize text LCD module
  Beep();

  LCD_string(0x80," S/W Time Delay ");		// display title
  LCD_string(0xC0,"Press KEY4-KEY1!");

  mode = 1;					// initial speed mode
  LED = 0x05;					// initial LED data

  while(1)
    { switch(Key_input())			// key input
        { case 0x1C : mode = 1;
                      LCD_string(0xC0,"    100 [ms]    ");
                      break;
          case 0x1A : mode = 2;
                      LCD_string(0xC0,"    200 [ms]    ");
                      break;
          case 0x16 : mode = 3;
                      LCD_string(0xC0,"    300 [ms]    ");
                      break;
          case 0x0E : mode = 4;
                      LCD_string(0xC0,"    400 [ms]    ");
                      break;
          default   : LED ^= 0x0F;		// output LED with complement
                      DIG_SELECT = LED;
                      if(mode == 1)      Delay_ms(100);
                      else if(mode == 2) Delay_ms(200);
                      else if(mode == 3) Delay_ms(300);
                      else               Delay_ms(400);
                      break;
        }
    }
}

