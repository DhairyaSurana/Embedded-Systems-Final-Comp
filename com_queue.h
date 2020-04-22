#ifndef COM_QUEUE_H_
#define COM_QUEUE_H_

#include <FreeRTOS.h>
#include <queue.h>


#define QUEUE_LENGTH 128
#define QUEUE_ITEM_SIZE 8

typedef enum mqtt_data_type
{
    no_data, message_data, error_type
} mqtt_data_type; /*If there is an error the data type will be error*/

typedef struct mqtt_data_value
{
    unsigned int message_num_sent;
    unsigned int message_num_receive;
    char * source;
    char * message;
//    unsigned int time_val;
//    int sensor_val;
} mqtt_data_value;

typedef struct mqtt_data_struct
{
    mqtt_data_type type;
    mqtt_data_value value;
} mqtt_data_struct;

/* Global Handle for the sensor queue */
QueueHandle_t publish_queue_handle;
QueueHandle_t subscribe_queue_handle;

char * createNewMsg();

/* Function to send a time value to a queue. */
int sendStatisticsToPublishQueue(mqtt_data_struct statistics);

int sendStatisticsToSubscribeQueue();

/* Function to read a message from a queue */
mqtt_data_struct readStatisticsFromPublishQueue();

uint8_t readStatisticsFromSubscribeQueue();

void initStatisticsQueues();


#endif /* COM_QUEUE_H_ */
