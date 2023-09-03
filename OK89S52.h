/*                           OK89S52.H : Designed by Duck-Yong Yoon in 2005.  */

#ifndef __OK89S52_H__
#define __OK89S52_H__

/* -------------------------------------------------------------------------- */
/*        OK-89S52 Kit I/O Address                                            */
/* -------------------------------------------------------------------------- */

#define RTC_SECOND (*(unsigned char __xdata *)0x8000) /* DS12C887 RTC */
#define RTC_SEC_ALM (*(unsigned char __xdata *)0x8001)
#define RTC_MINUTE (*(unsigned char __xdata *)0x8002)
#define RTC_MIN_ALM (*(unsigned char __xdata *)0x8003)
#define RTC_HOUR (*(unsigned char __xdata *)0x8004)
#define RTC_HOUR_ALM (*(unsigned char __xdata *)0x8005)
#define RTC_WEEKDAY (*(unsigned char __xdata *)0x8006)
#define RTC_DATE (*(unsigned char __xdata *)0x8007)
#define RTC_MONTH (*(unsigned char __xdata *)0x8008)
#define RTC_YEAR (*(unsigned char __xdata *)0x8009)
#define RTC_A (*(unsigned char __xdata *)0x800A)
#define RTC_B (*(unsigned char __xdata *)0x800B)
#define RTC_C (*(unsigned char __xdata *)0x800C)
#define RTC_D (*(unsigned char __xdata *)0x800D)
#define RTC_FLAG (*(unsigned char __xdata *)0x800F)

#define SEG_PATTERN (*(unsigned char __xdata *)0x8100)  /* segment pattern data */
#define DIG_SELECT (*(unsigned char __xdata *)0x8200) /* digit select data */

#define LCD_WR_INST (*(unsigned char __xdata *)0x8300)  /* LCD module */
#define LCD_WR_DATA (*(unsigned char __xdata *)0x8301)

#define ADC_CH0 (*(unsigned char __xdata *)0x8400)  /* select ADC0809 channel */
#define ADC_CH1 (*(unsigned char __xdata *)0x8401)
#define ADC_CH2 (*(unsigned char __xdata *)0x8402)
#define ADC_CH3 (*(unsigned char __xdata *)0x8403)
#define ADC_CH4 (*(unsigned char __xdata *)0x8404)
#define ADC_CH5 (*(unsigned char __xdata *)0x8405)
#define ADC_CH6 (*(unsigned char __xdata *)0x8406)
#define ADC_CH7 (*(unsigned char __xdata *)0x8407)
#define ADC_READ (*(unsigned char __xdata *)0x8400) /* read ADC0809 */

#define DAC_CS (*(unsigned char __xdata *)0x8500) /* output DAC0800 */

/* -------------------------------------------------------------------------- */
/*        OK-89S52 Kit User-defined Function                                  */
/* -------------------------------------------------------------------------- */

extern void Kit_initialize(void);              /* initialize OK-89S52 kit */
extern void Delay_us(unsigned char us);        /* time delay for us[us] */
extern void Delay_ms(unsigned int ms);         /* time delay for ms[ms] */
extern void Beep(void);                        /* beep sound for 50 ms */
extern unsigned char Key_input(void);          /* input key switch KEY4 - KEY1 */
extern void LCD_command(char command);         /* write a command on text LCD */
extern void LCD_data(char character);          /* display a character on text LCD */
extern void LCD_string(char command, char *string); /* display a string on text LCD */
extern void LCD_initialize(void);              /* initialize text LCD module */

#endif /* __OK89S52_H__ */
