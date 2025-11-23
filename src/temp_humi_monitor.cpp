#include "temp_humi_monitor.h"

DHT20 dht20;
LiquidCrystal_I2C lcd(33,16,2);

void LCD_UpdateBuffer(float temp, float humid){
    snprintf(lcdBuffer[0], sizeof(lcdBuffer), "Temp: %.2fC", temp);
    snprintf(lcdBuffer[1], sizeof(lcdBuffer), "Humid: %.2f%", humid);

    if(temp < 25){
        snprintf(lcdBuffer[2], sizeof(lcdBuffer), "State: Normal");
    } else if(temp < 30){
        snprintf(lcdBuffer[2], sizeof(lcdBuffer), "State: Warning");
    } else{
        snprintf(lcdBuffer[2], sizeof(lcdBuffer), "!!!CRITICAL!!!");
    }
}

void temp_humi_monitor(void *pvParameters){

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
            LCD_UpdateBuffer(glob_temperature, glob_humidity);

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

void LCD_task(void *pvParameters){
    Wire.begin(11, 12);
    Serial.begin(115200);
    lcd.begin();
    lcd.backlight();

    const int numLines = 3;
    int curLine = 0;
    int critRep = 0;

    while(1){
        if(xSemaphoreTake(xLCDSemaphore, portMAX_DELAY) == pdTRUE){
            lcd.clear();

            int lineA = curLine;
            int lineB = (curLine+1) % numLines;

            if(strcmp(lcdBuffer[lineB], "!!!CRITICAL!!!") == 0){
                if(critRep < 2){
                    lcd.setCursor(0, 0);
                    lcd.print(lcdBuffer[lineA]);
                    lcd.setCursor(0, 1);
                    lcd.print(lcdBuffer[lineB]);
                    vTaskDelay(pdMS_TO_TICKS(500));
                    critRep++;
                    continue;
                }
                critRep = 0;
            }

            lcd.setCursor(0, 0);
            lcd.print(lcdBuffer[lineA]);
            lcd.setCursor(0, 1);
            lcd.print(lcdBuffer[lineB]);
            vTaskDelay(pdMS_TO_TICKS(500));

            curLine = (curLine+1) % numLines;
        }
    }
}