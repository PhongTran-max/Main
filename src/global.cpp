#include "global.h"

SemaphoreHandle_t xTempSemaphore;
SemaphoreHandle_t xHumidSemaphore;
SemaphoreHandle_t xLCDSemaphore;
SemaphoreHandle_t xDataMutex;

float glob_temperature = 0;
float glob_humidity = 0;
char lcdBuffer[3][16] = {"Temp: 0.0C", "Humi: 0.0%", "State: NORMAL"};

