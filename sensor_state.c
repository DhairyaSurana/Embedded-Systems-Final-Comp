#include "sensor_state.h"
#include "debug.h"
#include "uart_term.h"


int getSensorInfo(sensor_struct *curr_sensor, data_struct *new_sens_msg)
{
    /* This is where we get the value of the sensor. */

    timeVal_t timeInc = new_sens_msg->value.time_val;
    sensorVal_t sensorVal = new_sens_msg->value.sensor_val;

    static int sens_avg = 0;

    if (timeInc == 0) {
         curr_sensor->total += sensorVal;
         curr_sensor->count++;
    }

    else {

         curr_sensor->curTime += timeInc;
         sens_avg = curr_sensor->total/curr_sensor->count;

         curr_sensor->total = 0;
         curr_sensor->count = 0;

     }

     return sens_avg;

}

void sensorStructInit(sensor_struct *state){

    state->curTime = 0;
    state->total = 0;
    state->count = 0;

}
