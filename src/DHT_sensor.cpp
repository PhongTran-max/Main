#include "DHT_sensor.h"

DHT20 dht20;

void dht_sensor(void *pvParameters){

    Wire.begin(11, 12);
    Serial.begin(115200);
    dht20.begin();

    while (1){
        if(dht20.read()){
            // Reading temperature in Celsius
            float temperature = dht20.getTemperature();
            // Reading humidity
            float humidity = dht20.getHumidity();

            // Check if any reads failed and exit early
            if (isnan(temperature) || isnan(humidity)) {
                Serial.println("Failed to read from DHT sensor!");
                temperature = humidity =  -1;
                //return;
            }

            //Update global variables for temperature and humidity
            glob_temperature = temperature;
            glob_humidity = humidity;

            xSemaphoreGive(xTempSemaphore);
            xSemaphoreGive(xHumidSemaphore);
            xSemaphoreGive(xLCDSemaphore);
        }

        Serial.print("Humidity: ");
        Serial.print(glob_humidity);
        Serial.print("%  Temperature: ");
        Serial.print(glob_temperature);
        Serial.println("°C");

        vTaskDelay(5000);
    }
}