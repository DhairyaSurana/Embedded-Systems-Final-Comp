#include "sensor_state.h"
#include "debug.h"


void printSensorInfo(sensor_struct *curr_sensor, data_struct *new_sens_msg)
{
    /* This is where we get the value of the sensor. */

    timeVal_t timeInc = new_sens_msg->value.time_val;
    sensorVal_t sensorVal = new_sens_msg->value.sensor_val;

    if (timeInc == 0) {
         curr_sensor->total += sensorVal;
         curr_sensor->count++;
    }

    else {

         curr_sensor->curTime += timeInc;
         int sensorAvg = curr_sensor->total/curr_sensor->count;

         char sensorInfoPrintToUART[50] = "";
         sprintf(sensorInfoPrintToUART, "Distance: %d cm\r\n", sensorAvg);

         int i;
         for (i = 0; i < sizeof(sensorInfoPrintToUART) / sizeof(char); i++)
             dbgUARTVal(sensorInfoPrintToUART[i]);

         curr_sensor->total = 0;
         curr_sensor->count = 0;

     }

}

void sensorStructInit(sensor_struct *state){

    state->curTime = 0;
    state->total = 0;
    state->count = 0;

}
