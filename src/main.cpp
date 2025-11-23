#include "global.h"

#include "led_blinky.h"
#include "neo_blinky.h"
#include "temp_humi_monitor.h"
#include "queue.h"

void setup()
{
  Serial.begin(115200);

  //Create semaphors
  // xTempSemaphore = xSemaphoreCreateBinary();
  // xHumidSemaphore = xSemaphoreCreateBinary();
  // xLCDSemaphore = xSemaphoreCreateBinary();

  xSensorQueue = xQueueCreate(10, sizeof(SensorData_t));

  // xTaskCreate(led_blinky, "Task LED Blink", 2048, NULL, 2, NULL);
  // xTaskCreate(neo_blinky, "Task NEO Blink", 2048, NULL, 2, NULL);
  // xTaskCreate(temp_humi_monitor, "Task TEMP HUMI Monitor", 2048, NULL, 2, NULL);
  // xTaskCreate(LCD_task, "LCD Task", 2048, NULL, 2, NULL);
  xTaskCreate(ValueTask, "Value Task", 2048, NULL, 2, NULL);
  xTaskCreate(ProcessTask, "Process Task", 2048, NULL, 2, NULL);
}

void loop()
{
}