#ifndef SENSOR_QUEUE_H_
#define SENSOR_QUEUE_H_

#include <FreeRTOS.h>
#include <queue.h>

#define QUEUE_LENGTH 120
#define QUEUE_ITEM_SIZE 8

typedef enum data_type{no_data, time_data, sensor_data} data_type; /*If there is an error the data type will be error*/
typedef struct data_value{unsigned int time_val; int sensor_val;} data_value;
typedef struct data_struct{data_type type; data_value value;} data_struct;

/* Global Handle for the sensor queue */
QueueHandle_t sensor_queue_handle;

/* Writes message to queue using the data struct */
int sendToQueue(data_struct data);

/* Function to send a time value to a queue. */
int sendTimeMsgToQ1(unsigned int timeVal);

/* Function to send a sensor value to a queue. */
int sendSensorMsgToQ1(int mmDist);

/* Function to read a message from a queue */
data_struct readMsgFromQ1();

void initMessageQueue();


#endif /* SENSOR_QUEUE_H_ */
