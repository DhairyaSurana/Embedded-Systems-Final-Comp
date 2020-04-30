#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
//#include "Timer.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#include <strings.h>
#include <stdio.h>
#include "ti_drivers_config.h"
////#include "system_config/default/system_config.h"
//#include "system_config/default/system_definitions.h"

//Initialization
#define DBG_mainThread_BEFOREWHILE      0x01
#define DBG_mainThread_DISCONNECTED     0x02
//Timer 1 activated (starts with 1)
#define DBG_MqttClient_START            0x10
#define DBG_MqttClient_WAITFORSIG       0x11
#define DBG_MqttClient_PUBLISH          0x12
#define DBG_MqttClient_RECIEVE          0x13
//Timer 2 activated (starts with 2)
#define MqttClient_start_START          0x20


//Queue (Starts with 3)
#define DBG_MqttClientThread_START      0X30



//State Machine (Starts with 4)
#define DBG_MqttClientCallback_START    0x40


//ERRORS (starts with 6)
// Timer 1 errors
#define DLOC_TIMERONE_FAILED_INIT       0x60
#define DLOC_TIMERONE_FAILED_START      0x61

// Timer 2 errors
#define DLOC_TIMERTWO_FAILED_INIT        0x63
#define DLOC_TIMERTWO_FAILED_START      0x64
#define DLOC_TIMERTWO_ADC_FAILED        0x65


#define DLOC_FATAL_ERROR                0x66
#define DLOC_UART_FAILED                0x67
#define DLOC_OVER127_ERROR              0x68


UART_Handle uart;
/*
void Init_Debug();
void dbgUARTVal(unsigned char outVal);
void dbgUARTStr(char outVal[]);
*/
void dbgOutputLoc(unsigned int outLoc);


void dbgHaltAll(unsigned int outLoc);
void dbgTestOut();

//UART_Handle uart;

void dbgUARTVal(unsigned char outVal);
void dbgOutputLoc(unsigned int outLoc);
void fatalError(unsigned int outLoc);
void initUART();
void initGPIO();

