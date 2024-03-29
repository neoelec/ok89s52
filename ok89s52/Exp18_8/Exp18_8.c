/* ========================================================================== */
/*                Exp18_8.c : Use printf() for Text LCD Module                */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <at89s52.h>                           // include AT89S52 definition file
#include <OK89S52.h>                           // include OK-89S52 kit function

void main(void)
{
  signed int i;
  float x, y;
  signed int y_int, y_placed;

  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  LCD_string(0x80, "sin(+000)=+0.000");        // display title
  LCD_string(0xC0, "cos(+000)=+0.000");

  while (1) {
    Beep();
    for (i = -360; i <= +360; i += 30) {
      x = i * 3.141592654 / 180.;
      y = sinf(x);
      y_int = (int)y;
      y_placed = abs((int)(y * 10000)) - abs(y_int * 10000) + 5;
      y_placed /= 10;
      LCD_command(0x80);                       // display sin()
      printf("sin(%+04d)=%+01d.%03d", i, y_int, y_placed);  // printf for sin output
      y = cosf(x);
      y_int = (int)y;
      y_placed = abs((int)(y * 10000)) - abs(y_int * 10000) + 5;
      y_placed /= 10;
      LCD_command(0xC0);                       // display cos()
      printf("cos(%+04d)=%+01d.%03d", i, y_int, y_placed);  // printf for cos output
      Delay_ms(2000);
    }
  }
}
