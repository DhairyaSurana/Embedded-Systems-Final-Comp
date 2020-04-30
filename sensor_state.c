#include "sensor_state.h"
#include "debug.h"
#include "uart_term.h"


int getSensorInfo(sensor_struct *curr_sensor, data_struct *new_sens_msg)
{
    /* This is where we get the value of the sensor. */

    timeVal_t timeInc = new_sens_msg->value.time_val;
    //UART_PRINT("timeInc: %d\r\n", timeInc);
    sensorVal_t sensorVal = new_sens_msg->value.sensor_val;
    //UART_PRINT("sensorVal: %d\r\n", new_sens_msg->value.sensor_val);
    static int sensorAvg = 0;

    if (timeInc == 0) {
         curr_sensor->total += sensorVal;
         curr_sensor->count++;
    }

    else {
        // UART_PRINT("total: %d\r\n", curr_sensor->total);
        // UART_PRINT("count: %d\r\n", curr_sensor->count);
         curr_sensor->curTime += timeInc;
         sensorAvg = curr_sensor->total/curr_sensor->count;

         curr_sensor->total = 0;
         curr_sensor->count = 0;

     }

     return sensorAvg;

}

void sensorStructInit(sensor_struct *state){

    state->curTime = 0;
    state->total = 0;
    state->count = 0;

}
