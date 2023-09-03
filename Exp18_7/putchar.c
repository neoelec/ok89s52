/***********************************************************************/
/*                                                                     */
/*     PUTCHAR.C:                                                      */
/*                                                                     */
/***********************************************************************/

#include <at89s52.h>

void TXD_char(unsigned char character)
{                                              /* transmit a character */
  while (!TI) ;                                // transmit ready ?
  TI = 0;                                      // if yes, TI=0
  SBUF = character;                            //      and transmit a character
}

int putchar(int ch)
{
  if (ch == '\n')
    TXD_char((unsigned char)'\r');
  TXD_char((unsigned char)ch);

  return ch;
}