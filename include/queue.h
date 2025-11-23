#ifndef __QUEUE__
#define __QUEUE__

#include "global.h"

//Cấu trúc dữ liệu của queue
typedef struct {
    float temperature;
    float humidity;
    int sample_id;
} SensorData_t;

extern QueueHandle_t xSensorQueue;

void ValueTask(void *pvParameters);
void ProcessTask(void *pvParameters);

#endif