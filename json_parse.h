#include "cJSON.h"
#include "uart_term.h"


typedef struct dev_data {

    char* id;   // Name of topic ('ultra', 'pixy', 'rover', 'arm', 'statistics', or 'topics')
    int pub;    // Number of published messages
    int rec;    // Number of recieved messages

    int time;
    int dist;  // distance
    int x;     // x-coordinate
    int y;     // y-coordinate
    int height;
    int width;
    int signature;
    char* status;  // true or false
    char* atDestination;

    // topics
    char* topic1;
    char* topic2;
    char* topic3;
    char* topic4;

} dev_data;

/* Prints out struct values to UART */
void printDevData(dev_data d);

/* Wrapper for cJSON_GetObjectItemCaseSensitive function*/
int getIntValue(cJSON *obj, char *field);

char *getStrValue(cJSON *obj, char *field);

/* Returns a struct with values from str string (JSON format) */
struct dev_data getJSONData(char *str);

char * createJSONMsg(int pub, int rec, int dist, int time);
