/***********************************************************************/
/*                                                                     */
/*	 PUTCHAR.C:  Modified by D.Y.Yoon for Text LCD module.	       */
/*                                                                     */
/***********************************************************************/

#define LCD_WR_DATA (*(unsigned char xdata *)0x8301)

void Delay_us(unsigned char us);

char putchar(char c)
{
  if(c == '\n')				// if CR, return
    return(c);

  LCD_WR_DATA = c;			// output c
  Delay_us(50);

  return(c);
}
