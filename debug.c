//tesst2
//#include "ti_drivers_config.h"
#include "debug.h"
#include "FreeRTOS.h"
#include "task.h"



#include <ti/drivers/GPIO.h>
#include <ti/drivers/dpl/HwiP.h>
#include <ti/devices/cc32xx/inc/hw_types.h>
#include <ti/devices/cc32xx/driverlib/gpio.h>
#include <ti/devices/cc32xx/inc/hw_memmap.h>
#include <ti/devices/cc32xx/inc/hw_gpio.h>

//#include "string.h"



/*
void Init_Debug()
{
    //UART_init();

    UART_Params uartParams_Debug;
    UART_Params_init(&uartParams_Debug);

    uartParams_Debug.writeMode = UART_MODE_BLOCKING;
    uartParams_Debug.readMode = UART_MODE_BLOCKING;
    uartParams_Debug.writeDataMode = UART_DATA_BINARY;
    uartParams_Debug.readDataMode = UART_DATA_BINARY;
    uartParams_Debug.baudRate = 9600;
    uartParams_Debug.readEcho = UART_ECHO_OFF;
    uartParams_Debug.readReturnMode = UART_RETURN_FULL;

    uart_Debug = UART_open(cout_pin, &uartParams_Debug);

    if (uart_Debug == NULL){
        //GPIO_write(Board_GPIO1, 1);
        //dbgHaltAll(DLOC_UART_FAILED);
        while(1);
    }


}


// receives a value and outputs to UART

void dbgUARTVal(unsigned char outVal)
{
    UART_write(uart_Debug, &outVal, sizeof(outVal));
}


void dbgUARTStr(char outVal[])
{
    char ender[2] = "\r\n";
    size_t length = strlen(outVal);
    size_t i;
    for(i = 0; i < length; i++) {
        UART_write(uart_Debug, &outVal[i], sizeof(outVal[i]));

    }

    UART_write(uart_Debug, ender, sizeof(ender));
}

*/


void dbgHaltAll(unsigned int outLoc){
    dbgOutputLoc(outLoc);

    //SYS_INT_Disable();
    //stop all tasks
    vTaskSuspendAll();
    //output that all tasks have been stopped (disable all iterrupts)
    //Timer_stop(TimerOne);
    //Timer_stop(TimerTwo);

    HwiP_disable();


}

static void int_to_bin_digit(unsigned int in, int count, int* out)
{
    unsigned int mask = 1U << (count-1);
    int i;
    for (i = 0; i < count; i++) {
        out[i] = (in & mask) ? 1 : 0;
        in <<= 1;
    }
}

void dbgOutputLoc(unsigned int outLoc)
{
    if(outLoc>127)
    {
        dbgHaltAll(DLOC_OVER127_ERROR);

    }

    int binLoc[8] = {0};

    int_to_bin_digit(outLoc, 8, binLoc);


    GPIO_write(CONFIG_GPIO_0, binLoc[7]);
    GPIO_write(CONFIG_GPIO_1, binLoc[6]);
    GPIO_write(CONFIG_GPIO_2, binLoc[5]);
    GPIO_write(CONFIG_GPIO_3, binLoc[4]);
    GPIO_write(CONFIG_GPIO_4, binLoc[3]);
    GPIO_write(CONFIG_GPIO_5, binLoc[2]);
    GPIO_write(CONFIG_GPIO_6, binLoc[1]);
    //GPIO_write(CONFIG_GPIO_7, binLoc[0]);
    GPIO_toggle(CONFIG_GPIO_7);



    //better output scheme, only need one digiview cable in total (9 ports), but requires rewiring
    /////
    /*
    GPIO_write(Board_GPIO0, binLoc[7]);
    GPIO_write(Board_GPIO1, binLoc[6]);
    GPIO_write(Board_GPIO2, binLoc[5]);
    GPIO_write(Board_GPIO3, binLoc[4]);
    GPIO_write(Board_GPIO4, binLoc[3]);
    GPIO_write(Board_GPIO5, binLoc[2]);
    GPIO_write(Board_GPIO6, binLoc[1]);
    GPIO_toggle(Board_GPIO7);
    */
     ////


}

void dbgTestOut(){

    GPIO_write(CONFIG_GPIO_0, 1);
    GPIO_write(CONFIG_GPIO_1, 1);
    GPIO_write(CONFIG_GPIO_2, 1);
    GPIO_write(CONFIG_GPIO_3, 1);
    GPIO_write(CONFIG_GPIO_4, 1);
    GPIO_write(CONFIG_GPIO_5, 1);
    GPIO_write(CONFIG_GPIO_6, 1);
    GPIO_write(CONFIG_GPIO_7, 1);
    GPIO_write(CONFIG_GPIO_8, 1);

}

void DebugGPIO_init() {
    GPIO_init();
    GPIO_setConfig(CONFIG_GPIO_1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_2, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_3, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_4, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_5, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_6, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_7, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_8, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_write(CONFIG_GPIO_0, 0);
    GPIO_write(CONFIG_GPIO_1, 0);
    GPIO_write(CONFIG_GPIO_2, 0);
    GPIO_write(CONFIG_GPIO_3, 0);
    GPIO_write(CONFIG_GPIO_4, 0);
    GPIO_write(CONFIG_GPIO_5, 0);
    GPIO_write(CONFIG_GPIO_6, 0);
    GPIO_write(CONFIG_GPIO_7, 0);
    GPIO_write(CONFIG_GPIO_8, 0);
}

