#ifndef TIM_H_INCLUDED
#define TIM_H_INCLUDED

#include "pwm.h"

///* Beeper defines */
//#define     BEEPER_LEVEL_MSK        0b0000000000000111000000000000
//#define     BEEPER_TONE_MSK         0b0000000000000000011100000000
//#define     BEEPER_COUNT_MSK        0b0000000000000000000011111111
//#define     SET_BEEPER_LEVEL(x)     ( Beeper ^= (Beeper & BEEPER_LEVEL_MSK); Beeper |= (x<<12) )
//#define     GET_BEEPER_LEVEL()      ( (Beeper & BEEPER_LEVEL_MSK)>>12 )
//#define     SET_BEEPER_TONE(x)      ( Beeper ^= (Beeper & BEEPER_TONE_MSK); Beeper |= (x<<8) )
//#define     GET_BEEPER_TONE()       ( (Beeper & BEEPER_TONE_MSK)>>8 )
//#define     SET_BEEPER_COUNTER(x)   ( Beeper ^= (Beeper & BEEPER_COUNT_MSK); Beeper |= x )
//#define     GET_BEEPER_COUNTER()    ( Beeper & BEEPER_COUNT_MSK )
//
//extern uint32_t Beeper;


#define     BEEP_OFF            0
#define     BEEP_LOW            1
#define     BEEP_MID            3
#define     BEEP_HIGH           7

#define     BEEP()              BeeperCounter = 10;

extern uint16_t    BeeperCounter;


void BeeperHandler(void);
void StartBeeper(void);
void StopBeeper(void);

void StartPWM(void);
void StopPWM(void);

#endif /* TIM_H_INCLUDED */
