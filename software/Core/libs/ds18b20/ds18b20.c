
#include "one_wire.h"
#include "ds18b20.h"


#define DS_QUANTITY     3


static LL_GPIO_InitTypeDef GPIO_InitStruct = {0};



static uint8_t dt[DS_QUANTITY][8];




static uint8_t DS18B20_Reset(void);
static uint8_t DS18B20_ReadBit(void);
static uint8_t DS18B20_ReadByte(void);
static void DS18B20_WriteBit(uint8_t bit);
static void DS18B20_WriteByte(uint8_t dt);

/*  */
void DS18B20_PortInit(void) {

    GPIO_InitStruct.Pin = LL_GPIO_PIN_12;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}


/*  */
uint8_t DS18B20_Init(uint8_t mode) {

    if(DS18B20_Reset()) return 1;

    if( mode==SKIP_ROM ) {

        DS18B20_WriteByte(0xCC);    // Skip ROM
    }

    DS18B20_WriteByte(0x4E);    // Write stratchpad

    DS18B20_WriteByte(0x64);    // TH register = 100C
    DS18B20_WriteByte(0x9E);    // TL register = -30C
    //DS18B20_WriteByte(RESOLUTION_9BIT);

    return 0;
}



/*  */
static uint8_t DS18B20_Reset(void) {

    uint8_t state = 0;

    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_12);
    Delay_us(480);
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_12);

    Delay_us(65);

    state = ( LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_12) ? 1 : 0);

    Delay_us(420);

    return state;
}



/*  */
static uint8_t DS18B20_ReadBit(void) {

    uint8_t bit = 0;

    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_12);
    Delay_us(3);
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_12);

    Delay_us(15);

    bit = ( LL_GPIO_IsInputPinSet(GPIOB, LL_GPIO_PIN_12) ? 1 : 0);

    Delay_us(50);

    return bit;
}


/*  */
static uint8_t DS18B20_ReadByte(void) {

    uint8_t data = 0;

    for (uint8_t i = 0; i <= 7; i++)

        data += DS18B20_ReadBit() << i;

    return data;
}



/*  */
static void DS18B20_WriteBit(uint8_t bit) {

    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_12);
    Delay_us(bit ? 3 : 65);

    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_12);
    Delay_us(bit ? 65 : 3);
}


/*  */
static void DS18B20_WriteByte(uint8_t dt) {

    for (uint8_t i = 0; i < 8; i++) {

        DS18B20_WriteBit(dt >> i & 1);
        Delay_us(5);
    }
}


/*  */
void DS18B20_MeasureTemperCmd(uint8_t dev, uint8_t mode) {

    DS18B20_Reset();

    if(mode==SKIP_ROM) {

        DS18B20_WriteByte(0xCC);    // Skip ROM
    }

    DS18B20_WriteByte(0x44);    // Convert T
}



/*  */
void DS18B20_ReadStratchpad(uint8_t dev, uint8_t mode) {

    uint8_t i;

    DS18B20_Reset();

    if(mode==SKIP_ROM) {

        DS18B20_WriteByte(0xCC);    // Skip ROM
    }

    DS18B20_WriteByte(0xBE);    // Read stratchpad

    for(i=0; i<8; i++) {

        dt[dev][i] = DS18B20_ReadByte();
    }

}


/*  */
uint8_t DS18B20_GetSign(uint8_t dev) {

    return(dt[dev][1] & 0x01) ? 1 : 0;
}


/*  */
float DS18B20_Convert(uint8_t dev) {

    float t = (dt[dev][1] & 0x07)<<4 | dt[dev][0]>>4;

    if(dt[dev][0] & 0x0F) t += 0.5;

    return t;
}
