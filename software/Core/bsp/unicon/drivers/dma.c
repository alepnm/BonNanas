#include "defs.h"
#include "dma.h"
#include "usart.h"


void DMA_Init(void){

    /* USART TX per DMA */
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_4);
    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_4, (uint32_t)&(usart_handle[NEXTION_PORT]->TDR));
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_4, (uint32_t)ptrSecondaryTxBuffer);
    LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_4, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_4, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4, TX_BUFFER_SIZE);

    LL_DMA_DisableIT_HT(DMA1, LL_DMA_CHANNEL_4);
    LL_DMA_DisableIT_TE(DMA1, LL_DMA_CHANNEL_4);
    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_4);

    LL_USART_EnableDMAReq_TX(usart_handle[NEXTION_PORT]);
}
