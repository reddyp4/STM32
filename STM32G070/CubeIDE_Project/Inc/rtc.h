#ifndef RTC_H_
#define RTC_H_

#include <stdio.h>
#include "stm32g070xx.h"
#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_rcc.h"

#define RTC_ASYNCH_PREDIV   0x7F    //127
#define RTC_SYNCH_PREDIV    0xF9    //249

#define RTC_BACKUP  0x8888

void rtc_init(void);
void rtc_calendar_config(void);
void rtc_calendar_show(uint8_t *showtime, uint8_t *showdate);

#endif  /* RTC_H_ */
