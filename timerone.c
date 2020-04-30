
#include "timerone.h"
#include "com_queue.h"
#include "uart_term.h"

void timerQuarterCallback(Timer_Handle timerHandle)
{
    //dbgOutputLoc(MAIN_TASK_DLOC_ENTER_TIMERONE_ISR);
    //dbgOutputLoc(MAIN_TASK_DLOC_BEFORE_COMM_WITH_QUEUE_IN_TIMERONE_ISR);
    uint32_t timerCount = Timer_getCount(timerHandle);
    sendTimeMsgToQ(timerCount);
//    mqtt_data_struct time_data;
//    time_data.type = message_data;
//    time_data.message = createNewMsg(0, 0, 0, timerCount);
//    sendStatisticsToPublishQueue(time_data);
    //sendTimeMsgToQ1(timerCount);
    //dbgOutputLoc(MAIN_TASK_DLOC_LEAVE_TIMERONE_ISR);
    //dbgOutputLoc(MAIN_TASK_DLOC_AFTER_COMM_WITH_QUEUE_IN_TIMERONE_ISR);
} /*Sends out time when call back function is called to queue.*/

void initTimerOne()
{

    UART_PRINT("Entered initTimerOne \r\n");
    Timer_Params params1;
    Timer_Params_init(&params1);
    
    /* Initalizing params */
    params1.period = TIMER1_PERIOD;
    params1.periodUnits = Timer_PERIOD_US;
    params1.timerMode = Timer_CONTINUOUS_CALLBACK;
    params1.timerCallback = timerQuarterCallback;
    
    /*Opening Timer*/
    timer1 = Timer_open(Board_TIMER0, &params1);
    
    if (timer1 == NULL)
    {
        //fatalError(MAIN_TASK_DLOC_FAILED_TIMERONE_OPEN);
        UART_PRINT("Error: NULL timer1\r\n");
    }

    if (Timer_start(timer1) == Timer_STATUS_ERROR)
    {
        //fatalError(MAIN_TASK_DLOC_FAILED_TIMERONE_START);
        UART_PRINT("Error: timer1 didn't start properly\r\n");
    }
} /*Initalizes timer one.*/
