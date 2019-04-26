
#include <stdio.h>
#include <string.h>
#include "usart.h"
#include "command.h"
#include "motor.h"


extern const char version[];

/*  */
extern void SetDefaults(SysData_TypeDef *self);


/*  */
void NewMessageHandler(SysData_TypeDef *self) {

    if( !strncmp(ptrPrimaryRxBuffer, "AT+HTEMP=", 9 )) {

        uint8_t tmp = atoi(ptrPrimaryRxBuffer+9);

        if(tmp < 22 || tmp > 32) {

            sprintf(ptrPrimaryTxBuffer, "%s%02u%s", "BAD PARAM: HTEMP=", tmp, "\r\n");
            USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);
            while(RespondWaitingFlag);

            USART_ClearRxBuffer(PRIMARY_PORT);
            return;
        }

        if(tmp <= self->LowTemperature){
            sprintf(ptrPrimaryTxBuffer, "%s", "BAD PARAM: HTEMP<LTEMP\r\n");
            USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);
            USART_ClearRxBuffer(PRIMARY_PORT);
        }else{
            self->HighTemperature = tmp;
            SendOk();
        }

        return;
    }

    if( !strncmp(ptrPrimaryRxBuffer, "AT+HTEMP?", 9 )) {

        sprintf(ptrPrimaryTxBuffer, "%s%02u%s", "HTEMP=", self->HighTemperature, "\r\n");
        USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);
        while(RespondWaitingFlag);

        USART_ClearRxBuffer(PRIMARY_PORT);
        return;
    }


    if( !strncmp(ptrPrimaryRxBuffer, "AT+LTEMP=", 9 )) {

        uint8_t tmp = atoi(ptrPrimaryRxBuffer+9);

        if(tmp < 15 || tmp > 25) {

            sprintf(ptrPrimaryTxBuffer, "%s%02u%s", "BAD PARAM: LTEMP=", tmp, "\r\n");
            USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);
            while(RespondWaitingFlag);

            USART_ClearRxBuffer(PRIMARY_PORT);
            return;
        }

        if(tmp >= self->HighTemperature){
            sprintf(ptrPrimaryTxBuffer, "%s", "BAD PARAM: LTEMP>HTEMP\r\n");
            USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);
            USART_ClearRxBuffer(PRIMARY_PORT);
        }else{
            self->LowTemperature = tmp;
            SendOk();
        }

        return;
    }

    if( !strncmp(ptrPrimaryRxBuffer, "AT+LTEMP?", 9 )) {

        sprintf(ptrPrimaryTxBuffer, "%s%02u%s", "LTEMP=", self->LowTemperature, "\r\n");
        USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);
        while(RespondWaitingFlag);

        USART_ClearRxBuffer(PRIMARY_PORT);
        return;
    }


    if( !strncmp(ptrPrimaryRxBuffer, "AT+HUMLEVEL=", 12 )) {

        uint16_t tmp = atoi(ptrPrimaryRxBuffer+12);

        if(tmp < 200 || tmp > 800) {

            sprintf(ptrPrimaryTxBuffer, "%s%02u%s", "BAD PARAM: HUMLEVEL=", tmp, "\r\n");
            USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);
            while(RespondWaitingFlag);

            USART_ClearRxBuffer(PRIMARY_PORT);
            return;
        }

        self->HighHumidity = tmp;
        USART_ClearRxBuffer(PRIMARY_PORT);
        SendOk();
        return;
    }

    if( !strncmp(ptrPrimaryRxBuffer, "AT+HUMLEVEL?", 12 )) {

        sprintf(ptrPrimaryTxBuffer, "%s%02u%s", "HUMLEVEL=", self->HighHumidity, "\r\n");
        USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);
        while(RespondWaitingFlag);

        USART_ClearRxBuffer(PRIMARY_PORT);
        return;
    }


    if( !strncmp(ptrPrimaryRxBuffer, "AT+SPEED=", 9 )) {

        uint16_t tmp = atoi(ptrPrimaryRxBuffer+9);

        if(tmp < 300 || tmp > 800) {

            sprintf(ptrPrimaryTxBuffer, "%s%02u%s", "BAD PARAM: SPEED=", tmp, "\r\n");
            USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);
            while(RespondWaitingFlag);

            USART_ClearRxBuffer(PRIMARY_PORT);
            return;
        }

        self->MotorSpeed = tmp;

        USART_ClearRxBuffer(PRIMARY_PORT);
        SendOk();

        return;
    }

    if( !strncmp(ptrPrimaryRxBuffer, "AT+SPEED?", 9 )) {

        sprintf(ptrPrimaryTxBuffer, "%s%u%s", "SPEED=", self->MotorSpeed, "\r\n");
        USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);
        while(RespondWaitingFlag);

        USART_ClearRxBuffer(PRIMARY_PORT);

        return;
    }


    if( !strncmp(ptrPrimaryRxBuffer, "AT+RUNTIME=", 11 )) {

        uint8_t tmp = atoi(ptrPrimaryRxBuffer+11);

        if(tmp < 2 || tmp > 10) {

            sprintf(ptrPrimaryTxBuffer, "%s%u%s", "BAD PARAM: RUNTIME=", tmp, "\r\n");
            USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);
            while(RespondWaitingFlag);

            USART_ClearRxBuffer(PRIMARY_PORT);
            return;
        }

        self->MotorRunTime = tmp;
        USART_ClearRxBuffer(PRIMARY_PORT);
        SendOk();
        return;
    }

    if( !strncmp(ptrPrimaryRxBuffer, "AT+RUNTIME?", 11 )) {

        sprintf(ptrPrimaryTxBuffer, "%s%u%s", "RUNTIME=", self->MotorRunTime, "\r\n");
        USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);
        while(RespondWaitingFlag);

        USART_ClearRxBuffer(PRIMARY_PORT);
        return;
    }



    if( !strncmp(ptrPrimaryRxBuffer, "AT+PAUSETIME=", 13 )) {

        uint8_t tmp = atoi(ptrPrimaryRxBuffer+13);

        if(tmp < 1 || tmp > 3) {

            sprintf(ptrPrimaryTxBuffer, "%s%u%s", "BAD PARAM: PAUSETIME=", tmp, "\r\n");
            USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);
            while(RespondWaitingFlag);

            USART_ClearRxBuffer(PRIMARY_PORT);
            return;
        }

        self->MotorPauseTime = tmp;
        USART_ClearRxBuffer(PRIMARY_PORT);
        SendOk();
        return;
    }

    if( !strncmp(ptrPrimaryRxBuffer, "AT+PAUSETIME?", 13 )) {

        sprintf(ptrPrimaryTxBuffer, "%s%u%s", "PAUSETIME=", self->MotorPauseTime, "\r\n");
        USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);
        while(RespondWaitingFlag);

        USART_ClearRxBuffer(PRIMARY_PORT);
        return;
    }


    if( !strncmp(ptrPrimaryRxBuffer, "AT+STATUS", 9 )) {

        sprintf(ptrPrimaryTxBuffer, "%s%02.02f%s%u%s", "TEMP=", self->temper, "\r\nHUM=", self->ADC_Data.ch2, "\r\n");
        USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);

        sprintf(ptrPrimaryTxBuffer, "%s%u%s%u%s", "RV1=", self->ADC_Data.ch0, "\r\nRV2=", self->ADC_Data.ch1, "\r\n");
        USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);

        if(self->WindowState == Closed) sprintf(ptrPrimaryTxBuffer, "%s", "Window is Closed\r\n");
        else sprintf(ptrPrimaryTxBuffer, "%s", "Window is Open\r\n");
        USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);

        if( !L298_ENA_CHECK() ) sprintf(ptrPrimaryTxBuffer, "%s", "Driver Disabled\r\n");
        else sprintf(ptrPrimaryTxBuffer, "%s", "Driver Enabled\r\n");
        USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);

        if( self->TestMode ) sprintf(ptrPrimaryTxBuffer, "%s", "Controller in Test mode\r\n");
        else sprintf(ptrPrimaryTxBuffer, "%s", "Controller in Normal mode\r\n");
        USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);


        // praleidziam eilute
        sprintf(ptrPrimaryTxBuffer, "%s", "\r\n");
        USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);
        while(RespondWaitingFlag);

        USART_ClearRxBuffer(PRIMARY_PORT);

        return;
    }


    if( !strncmp(ptrPrimaryRxBuffer, "AT+RESET", 8 )) {

        SetDefaults(self);

        sprintf(ptrPrimaryTxBuffer, "%s", "System RESET to defaults!\r\n");
        USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);
        while(RespondWaitingFlag);

        USART_ClearRxBuffer(PRIMARY_PORT);

        return;
    }



    if( !strncmp(ptrPrimaryRxBuffer, "AT+VER", 6 )) {

        sprintf(ptrPrimaryTxBuffer, "%s%s", version, "\r\n");
        USART_SendString(PRIMARY_PORT, ptrPrimaryTxBuffer);
        while(RespondWaitingFlag);

        USART_ClearRxBuffer(PRIMARY_PORT);

        return;
    }



    if( !strncmp(ptrPrimaryRxBuffer, "AT+TEST=", 8 )) {

        self->TestMode = atoi(ptrPrimaryRxBuffer+8);

        if(self->TestMode) {
            /* jungiam Testini tezima */
            L298_CloseWindow(self);
            self->WindowState = Closed;
        } else {



        }

        USART_ClearRxBuffer(PRIMARY_PORT);
        SendOk();
        return;
    }


    /* papildomos testinio rezimo komandos */
    if(self->TestMode) {

        if( !strncmp(ptrPrimaryRxBuffer, "AT+OPEN", 7 )) {

            if(self->WindowState != Opened){

                L298_OpenWindow(self);
                self->WindowState = Opened;

                SendOk();
            }else{

                USART_SendString(PRIMARY_PORT, "Window is opened!\r\n");
                while(RespondWaitingFlag);
            }

            return;
        }

        if( !strncmp(ptrPrimaryRxBuffer, "AT+CLOSE", 8 )) {

            if(self->WindowState != Closed){

                L298_CloseWindow(self);
                self->WindowState = Closed;

                SendOk();
            }else{

                USART_SendString(PRIMARY_PORT, "Window is closed!\r\n");
                while(RespondWaitingFlag);
            }

            return;
        }


    }

    USART_SendString(PRIMARY_PORT, "BAD_CMD\r\n");
    while(RespondWaitingFlag);

    USART_ClearRxBuffer(PRIMARY_PORT);
}


/*  */
void SendOk(void) {

    USART_SendString(PRIMARY_PORT, "OK\r\n");
    while(RespondWaitingFlag);
}

