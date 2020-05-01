#include "com_queue.h"
#include "cJSON.h"
#include "uart_term.h"


int sendToQ(data_struct data){

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t result = xQueueSendFromISR(publish_queue_handle, &data,
                                         &xHigherPriorityTaskWoken);
    return (pdPASS == result);
}

int sendTimeMsgToQ(unsigned int timeVal) {

    data_struct data = {.type=time_data, .value.sensor_val=0,
        .value.time_val=timeVal};
        return sendToQ(data);
}

int sendSensMsgToQ(int dist) {

    data_struct data = {.type=sensor_data, .value.sensor_val=dist,
        .value.time_val=0};
    return sendToQ(data);
}

data_struct readMsgFromQ(){

   // UART_PRINT("Entered readMsgFromQ\r\n");
//    data_struct data = { .type = no_data, .value.message_num_sent = 0,
//                             .value.message_num_receive = 0, .value.message = "" };
    data_struct data;
    xQueueReceive(publish_queue_handle, &data, portMAX_DELAY);

    return data;
}

uint8_t readStatisticsFromSubscribeQueue()
{
    uint8_t ack = 0;
    xQueueReceive(subscribe_queue_handle, &ack, 0);
    return ack;
}

void initMsgQueue()
{
    publish_queue_handle = xQueueCreate(QUEUE_LENGTH, sizeof(data_struct));
    //subscribe_queue_handle = xQueueCreate(QUEUE_LENGTH, sizeof(uint8_t));
}
