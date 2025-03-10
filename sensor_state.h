/* State Machine Enumeration Structure*/

#include "com_queue.h"

/* State Machine Structure*/
typedef int timeVal_t;
typedef int sensorVal_t;
typedef struct {int curTime;       // current time
                int total;        // Sum of all sensor values
                int count;}       // Number of sensor values
sensor_struct;

void sensorStructInit(sensor_struct *state);

int getSensorInfo(sensor_struct *curr_sensor, data_struct new_sens_msg);
    
