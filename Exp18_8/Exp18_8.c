/* ========================================================================== */
/*                Exp18_8.c : Use printf() for Text LCD Module                */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <STDIO.H>
#include <MATH.H>
#include "AT89S52.H"                           // include AT89S52 definition file
#include "OK89S52.H"                           // include OK-89S52 kit function

main()
{
  signed int i;
  float x, y;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "sin(+000)=+0.000");        // display title
  LCD_string(0xC0, "cos(+000)=+0.000");

  while (1) {
    Beep();
    for (i = -360; i <= +360; i += 30) {
      x = i * 3.141592654 / 180.;
      y = sin(x);
      LCD_command(0x80);                       // display sin()
      printf("sin(%+04d)=%+6.3f", i, y);       // printf for sin output
      y = cos(x);
      LCD_command(0xC0);                       // display cos()
      printf("cos(%+04d)=%+6.3f", i, y);       // printf for cos output
      Delay_ms(2000);
    }
  }
}
