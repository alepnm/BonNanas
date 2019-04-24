#ifndef MOTOR_H_INCLUDED
#define MOTOR_H_INCLUDED

#include "stm32f0xx_ll_gpio.h"
#include "defs.h"

#define L298_IN1_Reset()    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_7)
#define L298_IN1_Set()      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_7)
#define L298_IN1_CHECK()    (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_7) ? 1 : 0)

#define L298_IN2_Reset()    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_8)
#define L298_IN2_Set()      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_8)
#define L298_IN2_CHECK()    (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_8) ? 1 : 0)

#define L298_ENA_Reset()    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_9)
#define L298_ENA_Set()      LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_9)
#define L298_ENA_CHECK()    (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_9) ? 1 : 0)


#define MOTOR_SPEED_DEF         400
#define MOTOR_RUNTIME_DEF       3
#define MOTOR_DELAY_TIME_DEF    3       // sekundes
#define MOTOR_PAUSE_TIME_DEF    1       // sekundes


void L298_Init(SysData_TypeDef *self);
void L298_Process(SysData_TypeDef *self);

void L298_OpenWindow(SysData_TypeDef *self);
void L298_CloseWindow(SysData_TypeDef *self);
void L298_MotorStop(SysData_TypeDef *self);

#endif /* MOTOR_H_INCLUDED */
