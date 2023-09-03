/* ========================================================================== */
/*                  Exp07_1.c : Numerical Data Comparison(1)                  */
/* ========================================================================== */
/*                        Designed and programmed by Duck-Yong Yoon in 2005.  */

#include "AT89S52.H"                           // include AT89S52 definition file
#include "OK89S52.H"                           // include OK-89S52 kit function

Ucompare(unsigned char a, unsigned char b)
{                                              /* unsigned char compare */
  LCD_command(0xC7);
  if (a == b)
    LCD_data('=');
  else if (a > b)
    LCD_data('>');
  else
    LCD_data('<');
  Delay_ms(2000);
}

Compare(signed char a, signed char b)
{                                              /* signed char compare */
  LCD_command(0xC7);
  if (a == b)
    LCD_data('=');
  else if (a > b)
    LCD_data('>');
  else
    LCD_data('<');
  Delay_ms(2000);
}

main()
{
  Kit_initialize();                            // initialize OK-89S52 kit
  Delay_ms(50);                                // wait for system stabilization
  LCD_initialize();                            // initialize text LCD module

  while (1) {
    Beep();
    LCD_string(0x80, "Unsigned Compare");      // display title
    LCD_string(0xC0, "   100 ? 100    ");      // unsigned 8-bit compare
    Ucompare(100, 100);

    LCD_string(0xC0, "   100 ? 150    ");
    Ucompare(100, 150);

    LCD_string(0xC0, "   200 ? 150    ");
    Ucompare(200, 150);

    Beep();
    LCD_string(0x80, " Signed Compare ");      // display title
    LCD_string(0xC0, "  -100 ? -100   ");      // signed 8-bit compare
    Compare(-100, -100);

    LCD_string(0xC0, "  +100 ? -100   ");
    Compare(+100, -100);

    LCD_string(0xC0, "  -100 ? +100   ");
    Compare(-100, +100);

    LCD_string(0xC0, "  -100 ? -120   ");
    Compare(-100, -120);

    LCD_string(0xC0, "  -120 ? -100   ");
    Compare(-120, -100);
  }
}
