
#include <stdio.h>
#include "unicon.h"


uint8_t UnitID[12];


/*   */
static void UNI_SystemShutdown(void);


void UNI_Start(void) {

    /* startuojam */
    UNI_GetID(UnitID);

    LEDS_OFF();

}


/* sisteminiu procesu hendleris */
void UNI_Process(void) {

    static uint32_t delay = 0;

    if(delay <= timestamp) {

        delay = timestamp + 300;


    }

}


/* in Kb */
uint16_t UNI_GetFlashSize(void) {
    return *(uint16_t *)(FLASHSIZE_BASE);
}


/*  */
void UNI_GetID(uint8_t* bufid) {

    uint8_t i = 0;

    do {
        *(bufid + i) = *(uint8_t*)(UID_BASE + i);
    } while(++i < 12);

}


/*  */
uint8_t UNI_CheckUID(uint8_t* bufid) {

    uint8_t temp_buf[12];
    uint8_t i = 0;

    UNI_GetID(temp_buf);

    do {
        if( *(temp_buf + i) != *(bufid + i) ) return 1;
    } while(++i < 12);

    return 0;
}



/* Sisteminis IRQ hendleris. Vykdomas kas 1 ms is Systiko */
void UNI_SystemIRQ(void) {

    static uint32_t delay = 0;

    if(delay < timestamp) {
        delay = timestamp + 1000;
        //SysData.WTime++;
    }


}


/*  */
static void UNI_SystemShutdown(void) {

    NVIC_SystemReset();
}
