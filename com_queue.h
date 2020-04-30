#ifndef COM_QUEUE_H_
#define COM_QUEUE_H_

#include <FreeRTOS.h>
#include <queue.h>


#define QUEUE_LENGTH 128
#define QUEUE_ITEM_SIZE 8

typedef enum data_type
{
    no_data, sensor_data, time_data, message_data
} data_type; /*If there is an error the data type will be error*/

//typedef struct mqtt_data_value
//{
//    unsigned int message_num_sent;
//    unsigned int message_num_receive;
//    char * source;
//    char * message;
////    unsigned int time_val;
////    int sensor_val;
//} mqtt_data_value;
typedef struct data_value
{
    unsigned int time_val;
    int sensor_val;
    char *message;
} data_value;

typedef struct data_struct
{
    data_type type;
    data_value value;
    //mqtt_data_value value;
    //char * message;
} data_struct;

/* Global Handle for the sensor queue */
QueueHandle_t publish_queue_handle;
QueueHandle_t subscribe_queue_handle;

char * createNewMsg(int pub, int rec, int dist, int time);

int sendToQ(data_struct data);

/* Function to send a time value to a queue. */
int sendTimeMsgToQ(unsigned int timeVal);

/* Function to send a sensor value to a queue. */
int sendSensMsgToQ(int dist);

int sendStatisticsToSubscribeQueue();

/* Function to read a message from a queue */
data_struct readMsgFromQ();

uint8_t readStatisticsFromSubscribeQueue();

void initMsgQueue();


#endif /* COM_QUEUE_H_ */
