#include "rtc.h"

RTC_HandleTypeDef hrtc;

uint8_t time[15]={0};
uint8_t date[15]={0};

void rtc_init(void)
{
    //Select clock
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    /* Oscillator type, turn off LSE and turn on LSI */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.LSEState = RCC_LSE_OFF;       //low speed external off
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;        //Low speed internal on
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    //Set RTC clock source to LSI
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
    HAL_RCCEx_GetPeriphCLKConfig(&PeriphClkInitStruct);

    //Enable clock to RTC module
    __HAL_RCC_RTC_ENABLE();

    //Configure calendar
    hrtc.Instance = RTC;
    hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
    hrtc.Init.AsynchPrediv = RTC_ASYNCH_PREDIV;
	hrtc.Init.SynchPrediv = RTC_SYNCH_PREDIV;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
    HAL_RTC_Init(&hrtc);
}

/* Configure calendar */
void rtc_calendar_config(void)
{
    //Configure date and time
    RTC_DateTypeDef sdate;
    RTC_TimeTypeDef stime;
    //Set date: Monday November 4, 2024
    sdate.Year = 0x24;
    sdate.Month = RTC_MONTH_NOVEMBER;
    sdate.Date = 0x4;
    sdate.WeekDay = RTC_WEEKDAY_MONDAY;
    HAL_RTC_SetDate(&hrtc,&sdate,RTC_FORMAT_BCD);
    //Set time to 1pm
    stime.Hours = 0x01;
    stime.Minutes = 0x00;
    stime.Seconds = 0x00;
    stime.TimeFormat = RTC_HOURFORMAT12_AM;
    stime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    stime.StoreOperation = RTC_STOREOPERATION_RESET;
    HAL_RTC_SetTime(&hrtc,&stime,RTC_FORMAT_BCD);

    //Write the time to backup register
    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR0, RTC_BACKUP);
}

/* Display real time clock */
void rtc_calendar_show(uint8_t *showtime, uint8_t *showdate)
{
    RTC_DateTypeDef sdate;
    RTC_TimeTypeDef stime;
    HAL_RTC_GetDate(&hrtc, &sdate, RTC_FORMAT_BCD);
    HAL_RTC_GetTime(&hrtc, &stime, RTC_FORMAT_BCD);

    /* display time format, format: hh:mm:ss */
    sprintf((char *)showtime, "Time: %02d:%02d:%02d",stime.Hours, stime.Minutes, stime.Seconds);
    /* printf version to realterm */
    printf((char *)showtime, "Time: %02d:%02d:%02d\n",stime.Hours, stime.Minutes, stime.Seconds);

    /* display date format, format: mm-dd-yy */
    sprintf((char *)showtime, "Date: %02d:%02d:%02d",sdate.Month, sdate.Date, 2000+sdate.Year);
    printf((char *)showtime, "Date: %02d:%02d:%02d\n",sdate.Month, sdate.Date, 2000+sdate.Year);
}
