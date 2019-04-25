#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "stm32_assert.h"

#include "main.h"


/* System defines */
#ifndef NULL
    #define NULL ((void *)0)
#endif

#ifndef TRUE
    #define TRUE        (1u)
#endif

#ifndef FALSE
    #define FALSE       (0u)
#endif

#define DUMMY  0
#define UNUSED(x)       ((void)(x))

#define __enter_critical() {uint32_t irq; irq = __get_PRIMASK();
#define __exit_critical() __set_PRIMASK(irq);}
#define ATOMIC_SECTION(X) __enter_critical(); {X}; __exit_critical();

#define ENTER_CRITICAL_SECTION() __enter_critical();
#define EXIT_CRITICAL_SECTION() __exit_critical();


/* Macros */
#define LO8(x)          (uint8_t)( x & 0x00FF )
#define HI8(x)          (uint8_t)((x & 0xFF00 ) >> 8)
#define LO16(x)         (uint16_t)( x & 0x0000FFFF )
#define HI16(x)         (uint16_t)((x & 0xFFFF0000 ) >> 16)

typedef uint8_t         byte;

typedef enum { RES_OK = 0, RES_ERROR, RES_BUSY, RES_TIMEOUT, RES_BAD_PARAMS } eRESULT_TypeDef;


/*  SYSTEM DEFAULTS */

typedef struct {

    uint8_t         TestMode;
    float           temper;

    struct{
        uint16_t    ch0;
        uint16_t    ch1;
        uint16_t    ch2;
    }ADC_Data;

    uint32_t        PauseTimer;
    uint32_t        MotorTimer;
    uint32_t        MotorDriverOffTimerCounter;
    uint8_t         MotorState;
    uint16_t        MotorSpeed;
    uint8_t         WindowState;

    uint8_t         MotorRunTime;
    uint8_t         MotorPauseTime;
    uint8_t         HighTemperature;
    uint8_t         LowTemperature;
    uint16_t        HighHumidity;

}SysData_TypeDef;


enum {Closed = 0, Opened}WindowState;
enum {Stopped = 0, Run_WOpen, Run_WClose }MotorState;


__STATIC_INLINE void Delay_us(__IO uint32_t us){

    us *= (SystemCoreClock / 12000000);
    while(us--) ;
}

#endif /* DEFS_H_INCLUDED */
