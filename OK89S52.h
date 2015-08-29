/* OK89S52.H : Designed by Duck-Yong Yoon in 2005.                            */
/* -------------------------------------------------------------------------- */
/*                          OK-89S52 Kit I/O Address                          */
/* -------------------------------------------------------------------------- */

#ifndef __OK89S52_H__
#define __OK89S52_H__

#include <stdint.h>

#define RTC_SECOND    (*(uint8_t __xdata *)0x8000)  /* DS12C887 RTC */
#define RTC_SEC_ALM   (*(uint8_t __xdata *)0x8001)
#define RTC_MINUTE    (*(uint8_t __xdata *)0x8002)
#define RTC_MIN_ALM   (*(uint8_t __xdata *)0x8003)
#define RTC_HOUR      (*(uint8_t __xdata *)0x8004)
#define RTC_HOUR_ALM  (*(uint8_t __xdata *)0x8005)
#define RTC_WEEKDAY   (*(uint8_t __xdata *)0x8006)
#define RTC_DATE      (*(uint8_t __xdata *)0x8007)
#define RTC_MONTH     (*(uint8_t __xdata *)0x8008)
#define RTC_YEAR      (*(uint8_t __xdata *)0x8009)
#define RTC_A         (*(uint8_t __xdata *)0x800A)
#define RTC_B         (*(uint8_t __xdata *)0x800B)
#define RTC_C         (*(uint8_t __xdata *)0x800C)
#define RTC_D         (*(uint8_t __xdata *)0x800D)
#define RTC_FLAG      (*(uint8_t __xdata *)0x800F)

#define SEG_PATTERN   (*(uint8_t __xdata *)0x8100)  /* segment pattern data */
#define DIG_SELECT    (*(uint8_t __xdata *)0x8200)  /* digit select data */

#define LCD_WR_INST   (*(uint8_t __xdata *)0x8300)  /* LCD module */
#define LCD_WR_DATA   (*(uint8_t __xdata *)0x8301)

#define ADC_CH0       (*(uint8_t __xdata *)0x8400)  /* select ADC0809 channel */
#define ADC_CH1       (*(uint8_t __xdata *)0x8401)
#define ADC_CH2       (*(uint8_t __xdata *)0x8402)
#define ADC_CH3       (*(uint8_t __xdata *)0x8403)
#define ADC_CH4       (*(uint8_t __xdata *)0x8404)
#define ADC_CH5       (*(uint8_t __xdata *)0x8405)
#define ADC_CH6       (*(uint8_t __xdata *)0x8406)
#define ADC_CH7       (*(uint8_t __xdata *)0x8407)
#define ADC_READ      (*(uint8_t __xdata *)0x8400)  /* read ADC0809 */

#define DAC_CS        (*(uint8_t __xdata *)0x8500)  /* output DAC0800 */

/* -------------------------------------------------------------------------- */
/*                   OK-89S52 Kit User-defined Function                       */
/* -------------------------------------------------------------------------- */

void Kit_initialize(void);

void Delay_us(uint8_t us);

void Delay_ms(uint16_t ms);

void Beep(void);

uint8_t Key_input(void);

void LCD_command(uint8_t command);

void LCD_data(char character);

void LCD_string(uint8_t command, char *string);

void LCD_initialize(void);

#endif /* __OK89S52_H__ */
