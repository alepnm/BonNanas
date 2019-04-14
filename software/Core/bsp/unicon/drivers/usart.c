#include "defs.h"
#include "usart.h"
#include "io.h"
#include "nextion.h"

#if defined(MODBUS_PORT)
    #include "mbport.h"
#endif


USART_TypeDef * usart_handle[2u] = {USART1, USART2};
PortConfig_TypeDef port_config[2u];
PortRegister_TypeDef port_register[2u];

uint8_t TxState = USART_STATE_IDLE;


char* ptrPrimaryRxBuffer = port_register[PRIMARY_PORT].RxBuffer;
char* ptrPrimaryTxBuffer = port_register[PRIMARY_PORT].TxBuffer;
char* ptrSecondaryRxBuffer = port_register[SECONDARY_PORT].RxBuffer;
char* ptrSecondaryTxBuffer = port_register[SECONDARY_PORT].TxBuffer;

const uint32_t baudrates[6u] = { 2400u, 4800u, 9600u, 19200u, 38400u, 57600u };


/*  */
void USART_Config(uint8_t ucPORT, uint32_t ulBaudRate, uint32_t ulDataBits,  uint8_t ulParity ) {

    LL_USART_InitTypeDef USART_InitStruct = {
        .BaudRate = 19200,
        .DataWidth = LL_USART_DATAWIDTH_8B,
        .StopBits = LL_USART_STOPBITS_1,
        .Parity = LL_USART_PARITY_NONE,
        .TransferDirection = LL_USART_DIRECTION_TX_RX,
        .HardwareFlowControl = LL_USART_HWCONTROL_NONE,
        .OverSampling = LL_USART_OVERSAMPLING_16
    };

    UNUSED(ulDataBits);

    do {
        LL_USART_Disable(usart_handle[ucPORT]);
    } while( LL_USART_IsEnabled(usart_handle[ucPORT]) );

    /* cia reiketu patikrinti baudreito reiksme - ar ji standartine? */
    USART_InitStruct.BaudRate = ulBaudRate;

    switch(ulParity) {
    case USART_PAR_ODD:
        USART_InitStruct.Parity = LL_USART_PARITY_ODD;
    case USART_PAR_EVEN:
        USART_InitStruct.Parity = LL_USART_PARITY_EVEN;
        USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_9B;
        break;
    default:
        USART_InitStruct.Parity = LL_USART_PARITY_NONE;
        USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
    }

    LL_USART_Init(usart_handle[ucPORT], &USART_InitStruct);

    do {
        LL_USART_Enable(usart_handle[ucPORT]);
    } while( !LL_USART_IsEnabled(usart_handle[ucPORT]) );

    LL_USART_EnableIT_RXNE(usart_handle[ucPORT]);
    LL_USART_DisableIT_TC(usart_handle[ucPORT]);
}


/*  */
void USART_Send( uint8_t ucPORT, void* data, size_t len ) {

    while(len--) {
        while(!LL_USART_IsActiveFlag_TC(usart_handle[ucPORT]));
        LL_USART_TransmitData8(usart_handle[ucPORT], *((uint8_t*)data++));
    }
}


/*  */
void USART_Send_DMA(size_t len){
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4, len);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_4);
}


/*  */
void USART_SendByte(uint8_t ucPORT, char data) {
    LL_USART_TransmitData8(usart_handle[ucPORT], data);
}

/*  */
void USART_SendString( uint8_t ucPORT, const char* str ) {

    uint8_t i = 0;

    while( *(str+i) ) {
        while(!LL_USART_IsActiveFlag_TC(usart_handle[ucPORT]));
        LL_USART_TransmitData8(usart_handle[ucPORT], *(str+i));
        i++;
    }
}


/*  */
void USART_ClearRxBuffer(uint8_t ucPORT) {

    uint8_t i = 0;

    while(i < RX_BUFFER_SIZE) {
        port_register[ucPORT].RxBuffer[i++] = 0;
    }

    port_register[ucPORT].RxBufferIndex = 0;
    port_register[ucPORT].ReceivedData = 0;
}


/*  */
uint8_t CheckBaudrate( uint32_t baudrate) {

    uint8_t i = 0;


    while( i < sizeof(baudrates)/sizeof(baudrate) ) {

        if( baudrate == baudrates[i] ) return i;
        i++;
    }

    return 0xFF;
}


/*  */
void USART_IRQ_Handler(void) {

    if( LL_USART_IsActiveFlag_RXNE(usart_handle[PRIMARY_PORT]) && LL_USART_IsEnabledIT_RXNE(usart_handle[PRIMARY_PORT]) ) {

        port_register[PRIMARY_PORT].ReceivedData = LL_USART_ReceiveData8(usart_handle[PRIMARY_PORT]);

        *(ptrPrimaryRxBuffer + port_register[PRIMARY_PORT].RxBufferIndex) = port_register[PRIMARY_PORT].ReceivedData;

        port_register[PRIMARY_PORT].RxBufferIndex++;

        port_register[PRIMARY_PORT].PortState = USART_STATE_ANSWER_WAITING;

        port_register[PRIMARY_PORT].PortTimer = 10;  //ms

        //LED2_ON();
    }

#if defined(MODBUS_PORT)
    if( LL_USART_IsActiveFlag_RXNE(usart_handle[MODBUS_PORT]) && LL_USART_IsEnabledIT_RXNE(usart_handle[MODBUS_PORT]) ) {
        (void)pxMBFrameCBByteReceived();
    }

    if( LL_USART_IsActiveFlag_TC(usart_handle[MODBUS_PORT]) && LL_USART_IsEnabledIT_TC(usart_handle[MODBUS_PORT]) ) {
        (void)pxMBFrameCBTransmitterEmpty();
    }
#else

    if( LL_USART_IsActiveFlag_RXNE(usart_handle[SECONDARY_PORT]) && LL_USART_IsEnabledIT_RXNE(usart_handle[SECONDARY_PORT]) ) {

        port_register[SECONDARY_PORT].ReceivedData = LL_USART_ReceiveData8(usart_handle[SECONDARY_PORT]);

        *(ptrSecondaryRxBuffer + port_register[SECONDARY_PORT].RxBufferIndex) = port_register[SECONDARY_PORT].ReceivedData;

        port_register[SECONDARY_PORT].RxBufferIndex++;

        port_register[SECONDARY_PORT].PortState = USART_STATE_ANSWER_WAITING;

        port_register[SECONDARY_PORT].PortTimer = 10;  //ms
    }
#endif
}



