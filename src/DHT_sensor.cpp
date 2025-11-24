#include "DHT_sensor.h"

DHT20 dht20;

void dht_sensor(void *pvParameters){

    while (1){
        float temperature = -1;
        float humidity = -1;

        if(xSemaphoreTake(xI2CMutex, portMAX_DELAY)){
            if(dht20.read()==0){
                temperature = dht20.getTemperature();
                humidity = dht20.getHumidity();
            }
            xSemaphoreGive(xI2CMutex);
        }

        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        glob_temperature = temperature;
        glob_humidity = humidity;
        xSemaphoreGive(xDataMutex);

        xSemaphoreGive(xTempSemaphore);
        xSemaphoreGive(xHumidSemaphore);
        xSemaphoreGive(xLCDSemaphore);

        Serial.print("Humidity: ");
        Serial.print(glob_humidity);
        Serial.print("%  Temperature: ");
        Serial.print(glob_temperature);
        Serial.println("°C");

        vTaskDelay(5000);
    }
}