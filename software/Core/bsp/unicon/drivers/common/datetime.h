#ifndef DATETIME_H_INCLUDED
#define DATETIME_H_INCLUDED


typedef struct{
    uint8_t Seconds;
    uint8_t Minutes;
    uint8_t Hours;
    uint8_t WeekDay;
    uint8_t Date;
    uint8_t Month;
    uint8_t Year;
}DateTime_TypeDef;

extern DateTime_TypeDef DateTime;



#endif /* DATETIME_H_INCLUDED */
