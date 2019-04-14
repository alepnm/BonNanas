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

void SystickDelay_ms(uint32_t delay);
void Delay_ms(uint32_t delay);

#endif /* DEFS_H_INCLUDED */
