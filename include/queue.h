#ifndef __QUEUE__
#define __QUEUE__

#include "global.h"

//Cấu trúc dữ liệu của queue
typedef struct {
    float temperature;
    float humidity;
} SensorData_t;

extern QueueHandle_t xSensorQueue;

void PrintSerialTask(void *pvParameters);

#endif