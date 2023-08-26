/* ========================================================================== */
/*	           Exp08_6.c : Calculation of sin(x),cos(x)                   */
/* ========================================================================== */
/*			  Designed and programmed by Duck-Yong Yoon in 2005.  */

#include <MATH.H>
#include "AT89S52.H"				// include AT89S52 definition file
#include "OK89S52.H"				// include OK-89S52 kit function

LCD_s3d(int number)				/* display signed decimal number +xxx */
{ signed int i;
  unsigned char flag;

  flag = 0;

  if(number >= 0) LCD_data('+');		// sign
  else            LCD_data('-');

  number = abs(number);

  i = number/100;				// 10^2
  if((i == 0) && (flag == 0))
             LCD_data(' ');
  else {     LCD_data(i + '0');
             flag = 1;
       }

  number = number % 100;			// 10^1
  i = number/10;
  if((i == 0) && (flag == 0))
             LCD_data(' ');
  else       LCD_data(i + '0');

  i = number % 10;				// 10^0
  LCD_data(i + '0');
}

LCD_s1d3(float number)				/* display signed real number +x.xxx */
{ unsigned int i, j;

  if(number >= 0.0) LCD_data('+');		// sign
  else              LCD_data('-');

  number = fabs(number);
  j = (int)(number*1000. + 0.5);

  i = j / 1000;					// 10^0
  LCD_data(i + '0');
  LCD_data('.');

  j = j % 1000;					// 10^-1
  i = j / 100;
  LCD_data(i + '0');

  j = j % 100;					// 10^-2
  i = j / 10;
  LCD_data(i + '0');

  i = j % 10;					// 10^-3
  LCD_data(i + '0');
}

main()
{ signed int i;
  float x;

  Kit_initialize();                             // initialize OK-89S52 kit
  Delay_ms(50);                                 // wait for system stabilization
  LCD_initialize();                             // initialize text LCD module

  LCD_string(0x80,"sin(+000)=+0.000");		// display title
  LCD_string(0xC0,"cos(+000)=+0.000");

  while(1)
    { Beep();
      for(i=-360; i <= +360; i += 30)
        { x = i * 3.141592654 / 180.;
          LCD_command(0x84); LCD_s3d(i);	// display sine
          LCD_command(0x8A); LCD_s1d3(sin(x));
          LCD_command(0xC4); LCD_s3d(i);	// display cosine
          LCD_command(0xCA); LCD_s1d3(cos(x));
          Delay_ms(2000);
        }
    }
}


