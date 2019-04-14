#include "defs.h"
#include "rtc.h"

LL_RTC_TimeTypeDef RTC_Time;
LL_RTC_DateTypeDef RTC_Date;


/*  */
void RTC_Init(void) {

    if(LL_RTC_BAK_GetRegister(RTC, LL_RTC_BKP_DR0) != 0x32F2) {

        RTC_Time.Hours = 0;
        RTC_Time.Minutes = 0;
        RTC_Time.Seconds = 0;
        LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_Time);
        RTC_Date.WeekDay = LL_RTC_WEEKDAY_TUESDAY;
        RTC_Date.Day = 1;
        RTC_Date.Month = LL_RTC_MONTH_JANUARY;
        RTC_Date.Year = 19;
        LL_RTC_DATE_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_Date);
        LL_RTC_BAK_SetRegister(RTC,LL_RTC_BKP_DR0,0x32F2);
    }
}


/*  */
void RTC_Reset(void){

    LL_RTC_BAK_SetRegister(RTC, LL_RTC_BKP_DR0, 0);

    RTC_Init();
}


/*  */
void RTC_GetDateTime(uint8_t* year, uint8_t* mon, uint8_t* day, uint8_t* hour, uint8_t* minute, uint8_t* second, uint8_t* weekday) {

    *year = __LL_RTC_CONVERT_BCD2BIN( LL_RTC_DATE_GetYear(RTC) );
    *mon = __LL_RTC_CONVERT_BCD2BIN( LL_RTC_DATE_GetMonth(RTC) );
    *day = __LL_RTC_CONVERT_BCD2BIN( LL_RTC_DATE_GetDay(RTC) );
    *weekday = __LL_RTC_CONVERT_BCD2BIN( LL_RTC_DATE_GetWeekDay(RTC) );

    *hour = __LL_RTC_CONVERT_BCD2BIN( LL_RTC_TIME_GetHour(RTC) );
    *minute = __LL_RTC_CONVERT_BCD2BIN( LL_RTC_TIME_GetMinute(RTC) );
    *second = __LL_RTC_CONVERT_BCD2BIN( LL_RTC_TIME_GetSecond(RTC) );
}


/*  */
void RTC_SetDateTime(uint8_t year, uint8_t mon, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t weekday) {

    RTC_Time.Hours = hour;
    RTC_Time.Minutes = minute;
    RTC_Time.Seconds = second;
    RTC_Time.TimeFormat = LL_RTC_TIME_FORMAT_AM_OR_24;

    LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BIN, &RTC_Time);

    RTC_Date.Year = year;
    RTC_Date.Month = mon;
    RTC_Date.Day = day;
    RTC_Date.WeekDay = weekday;

    LL_RTC_DATE_Init(RTC, LL_RTC_FORMAT_BIN, &RTC_Date);
}
