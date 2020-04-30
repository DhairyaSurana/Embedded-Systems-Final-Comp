
#include "timertwo.h"
#include "timerone.h"
#include "debug.h"
#include "com_queue.h"
#include "uart_term.h"

int getDistInCM(uint32_t duration) {
    return duration/(TWO * CONVERSION_FACTOR * 100);
}


/* Calculates distance and sends that data to the queue */
// timerHandle is the interrupt
void sensorCallback(Timer_Handle handle) {

    static uint32_t prev_count, curr_count;
    int dist;
    //mqtt_data_struct data;

    if (GPIO_read(Board_GPIO9_Echo) == 1) {
        prev_count = Timer_getCount(timer1);        // Change this to timerHandle
    }
    else {

        curr_count = Timer_getCount(timer1);
        dist = getDistInCM(curr_count - prev_count); // Calculates distance

        sendSensMsgToQ(dist);
    }
}

void trigCallback(Timer_Handle handle){

    GPIO_write(Board_GPIO8_TRIG, 1);
    GPIO_write(Board_GPIO8_TRIG, 0);
}

void initTimerTwo() {

    UART_PRINT("Entered initTimerTwo\r\n");

    Timer_Params params2;
    Timer_Params_init(&params2);

    params2.period = TIMER2_PERIOD;
    params2.periodUnits = Timer_PERIOD_US;
    params2.timerMode = Timer_CONTINUOUS_CALLBACK;
    params2.timerCallback = trigCallback;       // activates the sensor trigger

    timer2 = Timer_open(Board_TIMER1, &params2);

//    if (timer2 == NULL)
//       UART_PRINT("Timer 2 is NULL\r\n");
//
//    if (Timer_start(timer2) == Timer_STATUS_ERROR)
//        UART_PRINT("Timer 2 start error\r\n");

    Timer_start(timer2);
    UART_PRINT("Timer 2 exiting");
}

/* Assigns the sensorCallback function to GPIO 9*/
void initUSSensor() {

    //UART_PRINT("Entered initUSSensor\r\n");

    GPIO_setCallback(Board_GPIO9_Echo, sensorCallback); // bind sensor callback to echo (GPIO 9) pin interrupt (Change-notice)
    GPIO_enableInt(Board_GPIO9_Echo);   // enable echo interrupt
}
