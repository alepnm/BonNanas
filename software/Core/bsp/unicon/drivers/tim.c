#include "defs.h"
#include "tim.h"
#include "unicon.h"



uint16_t    BeeperCounter;

/*   */
void BeeperHandler(void){

    if(BeeperCounter > 0){
        LL_TIM_OC_SetCompareCH1(TIM16, ( SysData.Beeper.level ) * 7); // nustatom garso stipruma
        LL_TIM_CC_EnableChannel(TIM16, LL_TIM_CHANNEL_CH1);
        BeeperCounter--;
    }else{
        LL_TIM_CC_DisableChannel(TIM16, LL_TIM_CHANNEL_CH1);
    }
}

/*   */
void StartBeeper(void){
    LL_TIM_EnableCounter(TIM16);
    LL_TIM_EnableAllOutputs(TIM16);
    LL_TIM_CC_EnableChannel(TIM16, LL_TIM_CHANNEL_CH1);
}

/*   */
void StopBeeper(void){
    LL_TIM_DisableCounter(TIM16);
    LL_TIM_DisableAllOutputs(TIM16);
    LL_TIM_CC_DisableChannel(TIM16, LL_TIM_CHANNEL_CH1);
}


/*   */
void StartPWM(void){
    LL_TIM_EnableCounter(TIM15);
    LL_TIM_EnableAllOutputs(TIM15);
    LL_TIM_CC_EnableChannel(TIM15, LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_EnableChannel(TIM15, LL_TIM_CHANNEL_CH2);
}

/*   */
void StopPWM(void){
    LL_TIM_DisableCounter(TIM15);
    LL_TIM_DisableAllOutputs(TIM15);
    LL_TIM_CC_DisableChannel(TIM15, LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_DisableChannel(TIM15, LL_TIM_CHANNEL_CH2);
}
