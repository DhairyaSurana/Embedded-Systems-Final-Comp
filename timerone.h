
#ifndef TIMERONE_H_
#define TIMERONE_H_

/*STD C Lib Headers*/
#include <stddef.h>

/*User Header Files*/
//#include "debug.h"
#include "sensor_queue.h"

/* Driver Header Files */
#include <ti/drivers/Timer.h>

/* Board Header File */
//#include "Board.h"
#include "ti_drivers_config.h"

#define TIMER1_PERIOD 250000

/*Global Timer Handle*/
Timer_Handle timer1;
/*Sends out time when call back function is called to queue.*/
void timerQuarterCallback(Timer_Handle timerHandle);
/*Initalizes timer one.*/ 
void initTimerOne();

#endif /* TIMERONE_H_ */
