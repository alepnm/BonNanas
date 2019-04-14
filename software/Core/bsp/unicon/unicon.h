#ifndef UNICON_H_INCLUDED
#define UNICON_H_INCLUDED

#include "defs.h"
#include "io.h"

#define Delay_ms(x) LL_mDelay(x);


extern volatile uint32_t timestamp;


/* Private functions */
void UNI_Start(void);
void UNI_Process(void);
void UNI_SystemIRQ(void);


void UNI_GetID(uint8_t* bufid);
uint16_t UNI_GetFlashSize(void);
uint8_t UNI_CheckUID(uint8_t* bufid);
#endif /* UNICON_H_INCLUDED */
