#include "global.h"

#include "led_blinky.h"
#include "neo_blinky.h"
#include "DHT_sensor.h"
#include "monitor.h"
#include "queue.h"
#include "button.h"

void setup()
{
  Serial.begin(115200);
  Wire.begin(11,12);
  //Create semaphors
  xButtonSemaphore = xSemaphoreCreateBinary();
  xDataMutex = xSemaphoreCreateMutex();
  xI2CMutex = xSemaphoreCreateMutex();
  xSensorQueue = xQueueCreate(10, sizeof(SensorData_t));

  xTaskCreate(led_blinky, "Task LED Blink", 2048, NULL, 2, NULL);
  xTaskCreate(neo_blinky, "Task NEO Blink", 2048, NULL, 2, NULL);
  xTaskCreate(dht_sensor, "DHT Sensor", 2048, NULL, 2, NULL);
  xTaskCreate(LCD_task, "LCD Task", 2048, NULL, 2, NULL);
  xTaskCreate(getKeyButton, "Button Task", 2048, NULL, 2, NULL);
  xTaskCreate(PrintSerialTask, "Serial Task", 2048, NULL, 2, NULL);
}

void loop()
{
}