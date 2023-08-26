/* OK89S52.H : Designed by Duck-Yong Yoon in 2005.			      */
/* -------------------------------------------------------------------------- */
/*		OK-89S52 Kit I/O Address				      */
/* -------------------------------------------------------------------------- */

#define RTC_SECOND    (*(unsigned char xdata *)0x8000)	/* DS12C887 RTC */
#define RTC_SEC_ALM   (*(unsigned char xdata *)0x8001)
#define RTC_MINUTE    (*(unsigned char xdata *)0x8002)
#define RTC_MIN_ALM   (*(unsigned char xdata *)0x8003)
#define RTC_HOUR      (*(unsigned char xdata *)0x8004)
#define RTC_HOUR_ALM  (*(unsigned char xdata *)0x8005)
#define RTC_WEEKDAY   (*(unsigned char xdata *)0x8006)
#define RTC_DATE      (*(unsigned char xdata *)0x8007)
#define RTC_MONTH     (*(unsigned char xdata *)0x8008)
#define RTC_YEAR      (*(unsigned char xdata *)0x8009)
#define RTC_A         (*(unsigned char xdata *)0x800A)
#define RTC_B         (*(unsigned char xdata *)0x800B)
#define RTC_C         (*(unsigned char xdata *)0x800C)
#define RTC_D         (*(unsigned char xdata *)0x800D)
#define RTC_FLAG      (*(unsigned char xdata *)0x800F)

#define SEG_PATTERN   (*(unsigned char xdata *)0x8100)	/* segment pattern data */
#define DIG_SELECT    (*(unsigned char xdata *)0x8200)	/* digit select data */

#define LCD_WR_INST   (*(unsigned char xdata *)0x8300)	/* LCD module */
#define LCD_WR_DATA   (*(unsigned char xdata *)0x8301)

#define ADC_CH0       (*(unsigned char xdata *)0x8400)	/* select ADC0809 channel */
#define ADC_CH1       (*(unsigned char xdata *)0x8401)
#define ADC_CH2       (*(unsigned char xdata *)0x8402)
#define ADC_CH3       (*(unsigned char xdata *)0x8403)
#define ADC_CH4       (*(unsigned char xdata *)0x8404)
#define ADC_CH5       (*(unsigned char xdata *)0x8405)
#define ADC_CH6       (*(unsigned char xdata *)0x8406)
#define ADC_CH7       (*(unsigned char xdata *)0x8407)
#define ADC_READ      (*(unsigned char xdata *)0x8400)	/* read ADC0809 */

#define DAC_CS        (*(unsigned char xdata *)0x8500)	/* output DAC0800 */

/* -------------------------------------------------------------------------- */
/*		OK-89S52 Kit User-defined Function			      */
/* -------------------------------------------------------------------------- */

Kit_initialize()				/* initialize OK-89S52 kit */
{
  P3_5 = 1;					// buzzer off
  SEG_PATTERN = 0x00;				// clear 7-segment LED
  DIG_SELECT = 0x00;
}

Delay_us(unsigned char us)			/* time delay for us[us] */
{ unsigned char i;

  us = us >> 2;
  for(i = 1; i <= us; i++);
}

Delay_ms(unsigned int ms)			/* time delay for ms[ms] */
{ unsigned int i, j;

  for(i = 1; i <= ms; i++)
    for(j = 1; j <= 250; j++);
}

Beep()						/* beep sound for 50 ms */
{ P3_5 = 0;
  Delay_ms(50);
  P3_5 = 1;
}

unsigned char key_flag = 0;

unsigned char Key_input()			/* input key switch KEY4 - KEY1 */
{ unsigned char key;

  key = P1 & 0x1E;				// any key pressed ?
  if(key == 0x1E)				// if no key, check key off
    { if(key_flag == 0)
        return key;
      else
        { Delay_ms(20);
          key_flag = 0;
          return key;
        }
    }
  else						// if key input, check continuous key
    { if(key_flag != 0)				// if continuous key, treat as no key input
        return 0x1E;
      else					// if new key, beep and delay for debounce
        { Beep();
          key_flag = 1;
          return key;
        }
    }
}

LCD_command(char command)			/* write a command on text LCD */
{ 
  LCD_WR_INST = command;
  Delay_us(50);
}

LCD_data(char character)			/* display a character on text LCD */
{ 
  LCD_WR_DATA = character;
  Delay_us(50);
}

LCD_string(char command, char *string)		/* display a string on text LCD */
{ 
  LCD_command(command);
  while(*string != '\0')
     { LCD_data(*string);
       string++;
     }
}

LCD_initialize()				/* initialize text LCD module */
{
  LCD_command(0x38);				// function set(8 bit, 2 line, 5x7 dot)
  LCD_command(0x0C);				// display control(display ON, cursor OFF)
  LCD_command(0x06);				// entry mode set(increment, not shift)
  LCD_command(0x01);				// clear display
  Delay_ms(2);

  Key_input();					// dummy function call to avoid warning
}

