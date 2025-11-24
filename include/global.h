#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#define LED_GPIO        48

#define NORMAL_TEMP     0
#define MED_TEMP        1
#define HIGH_TEMP       2

#define NEO_PIN         45
#define LED_COUNT       1
#define BREATHING_DELAY 20

extern SemaphoreHandle_t xTempSemaphore;
extern SemaphoreHandle_t xHumidSemaphore;
extern SemaphoreHandle_t xLCDSemaphore;
extern SemaphoreHandle_t xDataMutex;
extern SemaphoreHandle_t xI2CMutex;

extern float glob_temperature;
extern float glob_humidity;
extern char lcdBuffer[3][16];
#endif
