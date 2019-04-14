#ifndef RTC_H_INCLUDED
#define RTC_H_INCLUDED



void RTC_Init(void);
void RTC_Reset(void);
void RTC_GetDateTime(uint8_t* year, uint8_t* mon, uint8_t* day, uint8_t* hour, uint8_t* minute, uint8_t* second, uint8_t* weekday);
void RTC_SetDateTime(uint8_t year, uint8_t mon, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second, uint8_t weekday);


#endif /* RTC_H_INCLUDED */
