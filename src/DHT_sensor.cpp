#include "DHT_sensor.h"

DHT20 dht20;

void dht_sensor(void *pvParameters){

    while (1){
        float temperature = 0;
        float humidity = 0;

        if(xSemaphoreTake(xI2CMutex, portMAX_DELAY)){
            if(dht20.read()==0){
                temperature = 33;
                humidity = 33;
            }
            xSemaphoreGive(xI2CMutex);
        }

        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        glob_temperature = temperature;
        glob_humidity = humidity;
        xSemaphoreGive(xDataMutex);

        Serial.print("Humidity: ");
        Serial.print(glob_humidity);
        Serial.print("%  Temperature: ");
        Serial.print(glob_temperature);
        Serial.println("°C");

        vTaskDelay(5000);
    }
}