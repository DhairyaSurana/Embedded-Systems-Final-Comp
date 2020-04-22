#include "com_queue.h"
#include "cJSON.h"

char * createNewMsg(int pub, int rec, int dist, int time) {

    cJSON *msg = cJSON_CreateObject();
    cJSON_AddItemToObject(msg, "id", cJSON_CreateString("ultra"));
    cJSON_AddItemToObject(msg, "pub", cJSON_CreateNumber(pub));
    cJSON_AddItemToObject(msg, "rec", cJSON_CreateNumber(rec));
    cJSON_AddItemToObject(msg, "distance", cJSON_CreateNumber(dist));
    cJSON_AddItemToObject(msg, "time", cJSON_CreateNumber(time));

    return cJSON_Print(msg);
}

int sendStatisticsToPublishQueue(mqtt_data_struct statistics)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t result = xQueueSendFromISR(publish_queue_handle, &statistics,
                                         &xHigherPriorityTaskWoken);
    return (pdPASS == result);
}

int sendStatisticsToSubscribeQueue()
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint8_t ack = 1;
    BaseType_t result = xQueueSendToBack(subscribe_queue_handle, &ack,
                                                &xHigherPriorityTaskWoken);
    return (pdPASS == result);
}

mqtt_data_struct readStatisticsFromPublishQueue()
{

//    cJSON *msg = cJSON_CreateObject();
//        cJSON_AddItemToObject(msg, "id", cJSON_CreateString("ultra"));
//        cJSON_AddItemToObject(msg, "pub", cJSON_CreateNumber(0));
//        cJSON_AddItemToObject(msg, "rec", cJSON_CreateNumber(0));
//        cJSON_AddItemToObject(msg, "distance", cJSON_CreateNumber(0));
//        cJSON_AddItemToObject(msg, "time", cJSON_CreateNumber(0));

//    mqtt_data_struct data = { .type = no_data, .value.message_num_sent = 0,
//                           .value.message_num_receive = 0, .value.message = "" };

    mqtt_data_struct data = { .type = no_data, .message = "" };

    xQueueReceive(publish_queue_handle, &data, portMAX_DELAY);
    return data;
}

uint8_t readStatisticsFromSubscribeQueue()
{
    uint8_t ack = 0;
    xQueueReceive(subscribe_queue_handle, &ack, 0);
    return ack;
}

void initStatisticsQueues()
{
    publish_queue_handle = xQueueCreate(QUEUE_LENGTH, sizeof(cJSON));
    subscribe_queue_handle = xQueueCreate(QUEUE_LENGTH, sizeof(uint8_t));
}
