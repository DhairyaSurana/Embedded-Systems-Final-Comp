
#ifndef TIMERTWO_H_
#define TIMERTWO_H_

/* STD Header Files*/
#include <stddef.h>
#include <stdint.h>
#include <math.h>

/* POSIX Header files */
#include <pthread.h>

/* Driver Header files */
#include <ti/drivers/ADC.h>
#include <ti/drivers/Timer.h>
#include <ti/drivers/GPIO.h>

/* Board Header file */
//#include "Board.h"
#include "ti_drivers_config.h"

/* User Header Files*/
//#include "debug.h"
#include "com_queue.h"

/*ADC microvolt to mm conversion constants*/
#define DISTANCE_CONVERSION 1000000
#define POWER_NUMBER -1.15
#define DISTANCE_FACTOR 27.86
#define ZERO_0 0
#define NEGATIVE_ONE -1
#define TIMER2_PERIOD 100000
#define TWO 2
#define CONVERSION_FACTOR 29.1

/* Handles */
Timer_Handle timer2;
ADC_Handle adc;

/* ADC sample count */
#define ADC_SAMPLE_COUNT  (10)
#define THREADSTACKSIZE   (768)

/* conversion result variables */
uint16_t adcValue0;
uint32_t adcValue0MicroVolt;

static bool trigMode = true;
static bool clearTrig = true;

/*Sends to queue with the amount of time passed since the last callback */
void trigCallback(Timer_Handle timerHandle);

/*edge triggered callback for sensor*/
void sensorCallback(Timer_Handle timerHandle);

/*Converts sensor reading value into distance in mm*/
int convertToCM(uint32_t duration);

/*Initializes timer two*/
void initTimerTwo();

void initUSSensor();

#endif /* TIMERTWO_H_ */
