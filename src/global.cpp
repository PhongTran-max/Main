#include "global.h"

SemaphoreHandle_t xTempSemaphore;
SemaphoreHandle_t xHumidSemaphore;
SemaphoreHandle_t xLCDSemaphore;
SemaphoreHandle_t xDataMutex;
SemaphoreHandle_t xI2CMutex;

float glob_temperature = 0;
float glob_humidity = 0;
char lcdBuffer[3][16] = {"Temp: 0.00C", "Humid: 0.00%", "State: NORMAL"};

