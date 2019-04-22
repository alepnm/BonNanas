#ifndef DS18B20_H_INCLUDED
#define DS18B20_H_INCLUDED


#define SKIP_ROM        0
#define NO_SKIP_ROM     1


#define RESOLUTION_9BIT     0x1F
#define RESOLUTION_10BIT    0x3F
#define RESOLUTION_11BIT    0x5F
#define RESOLUTION_12BIT    0x7F





void    DS18B20_PortInit(void);
uint8_t DS18B20_Init(uint8_t mode);
void    DS18B20_MeasureTemperCmd(uint8_t dev, uint8_t mode);
void    DS18B20_ReadStratchpad(uint8_t dev, uint8_t mode);
uint8_t DS18B20_GetSign(uint8_t dev);
float   DS18B20_Convert(uint8_t dev);


__STATIC_INLINE void Delay_us(__IO uint32_t us){

    us *= (SystemCoreClock / 12000000);
    while(us--) ;
}



#endif /* DS18B20_H_INCLUDED */
