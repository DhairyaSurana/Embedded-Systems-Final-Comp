#include "sensor_queue.h"

int sendToQueue(data_struct data){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t result = xQueueSendToBackFromISR(sensor_queue_handle,
                                                &data, &xHigherPriorityTaskWoken);
    return  (pdPASS == result);
}

int sendTimeMsgToQ1(unsigned int timeVal){
    data_struct data = {.type=time_data, .value.sensor_val=0, 
    .value.time_val=timeVal};
    return sendToQueue(data);
}

/* Might be blocking based on the Project Specifications.*/
int sendSensorMsgToQ1(int mmDist){
    data_struct data = {.type=sensor_data, .value.sensor_val=mmDist, 
    .value.time_val=0};
    return sendToQueue(data);
}


data_struct readMsgFromQ1(){

    data_struct data;
    xQueueReceive(sensor_queue_handle, &data, portMAX_DELAY);

    return data;
}

void initMessageQueue()
{
    sensor_queue_handle = xQueueCreate(QUEUE_LENGTH, sizeof(data_struct));
}
