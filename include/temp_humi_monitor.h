#ifndef __TEMP_HUMI_MONITOR__
#define __TEMP_HUMI_MONITOR__
#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include "DHT20.h"
#include "global.h"

void LCD_UpdateBuffer(float temp, float humid);
void temp_humi_monitor(void *pvParameters);
void LCD_task(void *pvParameters);

#endif