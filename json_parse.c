#include "json_parse.h"
#include <string.h>


/* Prints out struct values to UART */
void printDevData(dev_data d) {

    UART_PRINT("DEVICE STRUCT {\r\n\r\n");

    UART_PRINT("    id: %s\r\n", d.id);
    UART_PRINT("    pub: %d\r\n", d.pub);
    UART_PRINT("    rec: %d\r\n", d.rec);

    if(strcmp(d.id, "ultra") == 0) {
        UART_PRINT("    distance: %d\r\n", d.dist);
        UART_PRINT("    time: %d\r\n", d.time);
    }

    if(strcmp(d.id, "arm") == 0) {
        UART_PRINT("    status: %s\r\n", d.status);
        UART_PRINT("    time: %d\r\n", d.time);
    }

    if(strcmp(d.id, "rover") == 0) {
        UART_PRINT("    atDestination: %s\r\n", d.atDestination);
        UART_PRINT("    status: %s\r\n", d.status);
        UART_PRINT("    time: %d\r\n", d.time);
    }

    if(strcmp(d.id, "pixy") == 0) {

        UART_PRINT("    time: %d\r\n", d.time);
        UART_PRINT("    x: %d\r\n", d.x);
        UART_PRINT("    y: %d\r\n", d.y);
        UART_PRINT("    width: %d\r\n", d.width);
        UART_PRINT("    height: %d\r\n", d.height);
        UART_PRINT("    signature:  %d\r\n", d.signature);
    }

    if(strcmp(d.id, "topics") == 0) {

        UART_PRINT("    topic1:  %s\r\n", d.topic1);
        UART_PRINT("    topic2:  %s\r\n", d.topic2);
        UART_PRINT("    topic3:  %s\r\n", d.topic3);
        UART_PRINT("    topic4:  %s\r\n", d.topic4);

    }

    UART_PRINT("\r\n}\r\n");

}


/* Wrapper for cJSON_GetObjectItemCaseSensitive function*/
int getIntValue(cJSON *obj, char *field) {

    cJSON *val_obj = cJSON_GetObjectItemCaseSensitive(obj, field);
    return (val_obj != NULL) ? val_obj->valueint : -1;       // -1 indicates value not found
}

char *getStrValue(cJSON *obj, char *field) {

    cJSON *val_obj = cJSON_GetObjectItemCaseSensitive(obj, field);
    return (val_obj != NULL) ? val_obj->valuestring : "None";
}


/* Returns a struct with values from str string (JSON format) */
struct dev_data getJSONData(char *str) {

    // initialize struct
    dev_data d_data = {"None", -1, -1, -1, -1, -1, -1, -1, -1, -1, "None", "false", "None", "None", "None", "None"};

    cJSON *json_obj = cJSON_Parse(str);

    int size = cJSON_GetArraySize(json_obj);
    if(size == 0) {
        UART_PRINT("ERROR: Empty string or improper format.\r\n");
        return d_data;
    }

    d_data.id = getStrValue(json_obj, "id");
    d_data.pub = getIntValue(json_obj, "pub");
    d_data.rec = getIntValue(json_obj, "rec");

//    UART_PRINT("ID: %s\r\n", d_data.id);
//    UART_PRINT("SIZE: %d\r\n", size);

        if(strcmp(d_data.id, "ultra") == 0) { // ultra

                d_data.time = getIntValue(json_obj, "time");
                d_data.dist = getIntValue(json_obj, "distance");
                d_data.status = getStrValue(json_obj, "status");

        }

        else if(strcmp(d_data.id, "arm") == 0) { // arm

                d_data.time = getIntValue(json_obj, "time");
                d_data.status = getStrValue(json_obj, "status");


        }

        else if(strcmp(d_data.id, "rover") == 0) { // rover

                d_data.time = getIntValue(json_obj, "time");
                d_data.status = getStrValue(json_obj, "status");
                d_data.atDestination = getStrValue(json_obj, "atDestination");


        }

        else if(strcmp(d_data.id, "pixy") == 0) { // pixy

                d_data.time = getIntValue(json_obj, "time");
                d_data.x = getIntValue(json_obj, "x_coordinate");
                d_data.y = getIntValue(json_obj, "y_coordinate");
                d_data.height = getIntValue(json_obj, "height");
                d_data.width = getIntValue(json_obj, "width");
                d_data.signature = getIntValue(json_obj, "signature");

        }

        else if(strcmp(d_data.id, "topics") == 0) {

                d_data.topic1 = getStrValue(json_obj, "topic1");
                d_data.topic2 = getStrValue(json_obj, "topic2");
                d_data.topic3 = getStrValue(json_obj, "topic3");
                d_data.topic4 = getStrValue(json_obj, "topic4");

        }

        else if(strcmp(d_data.id, "statistics") != 0){  // Invalid ID error

           UART_PRINT("ERROR: id not recognized.\r\n");
           d_data.id = "None";
           d_data.pub = -1;
           d_data.rec = -1;
        }


        cJSON_Delete(json_obj);
        return d_data;

}

char * createJSONMsg(int pub, int rec, int dist, int time) {

    cJSON *msg = cJSON_CreateObject();

    cJSON_AddItemToObject(msg, "id", cJSON_CreateString("ultra"));
    cJSON_AddItemToObject(msg, "pub", cJSON_CreateNumber(pub));
    cJSON_AddItemToObject(msg, "rec", cJSON_CreateNumber(rec));
    cJSON_AddItemToObject(msg, "distance", cJSON_CreateNumber(dist));
    cJSON_AddItemToObject(msg, "time", cJSON_CreateNumber(time));

    char *msg_str = cJSON_Print(msg);
    cJSON_Delete(msg);

    return msg_str;
}
