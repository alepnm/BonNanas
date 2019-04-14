#include "defs.h"
#include "pwm.h"



void PWM_Set(uint8_t ch, uint8_t value) {

    switch(ch) {

    case PWM_CH1:
        LL_TIM_OC_SetCompareCH1(TIM15, value);
        break;
    case PWM_CH2:
        LL_TIM_OC_SetCompareCH2(TIM15, value);
        break;
    }
}
