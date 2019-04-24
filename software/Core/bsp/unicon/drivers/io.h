#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#define LEDS_ON()       LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_0|LL_GPIO_PIN_1|LL_GPIO_PIN_2|LL_GPIO_PIN_10)
#define LEDS_OFF()      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_0|LL_GPIO_PIN_1|LL_GPIO_PIN_2|LL_GPIO_PIN_10)

#define LED2_ON()       LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_1)
#define LED2_OFF()      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_1)
#define LED2_TOGGLE()   LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_1)
#define LED2_CHECK()    (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_1) ? 1 : 0)

#define LED5_ON()       LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_0)
#define LED5_OFF()      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_0)
#define LED5_TOGGLE()   LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_0)
#define LED5_CHECK()    (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_0) ? 1 : 0)

#define LED6_ON()       LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_10)
#define LED6_OFF()      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_10)
#define LED6_TOGGLE()   LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_10)
#define LED6_CHECK()    (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_10) ? 1 : 0)

#define LED7_ON()       LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_2)
#define LED7_OFF()      LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_2)
#define LED7_TOGGLE()   LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_2)
#define LED7_CHECK()    (LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_2) ? 1 : 0)

#endif /* IO_H_INCLUDED */
