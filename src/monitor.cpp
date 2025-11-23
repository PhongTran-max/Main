#include "monitor.h"

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

void LCD_task(void *pvParameters){
    lcd.begin();
    lcd.backlight();

    const int numLines = 3;
    int curLine = 0;
    int critRep = 0;

    while(1){
        if(xSemaphoreTake(xLCDSemaphore, pdMS_TO_TICKS(50)) == pdTRUE){
            xSemaphoreTake(xDataMutex, portMAX_DELAY);
            float temp = glob_temperature;
            float humid = glob_humidity;
            xSemaphoreGive(xDataMutex);

            LCD_UpdateBuffer(temp, humid);
            lcd.clear();

            int lineA = curLine;
            int lineB = (curLine+1) % numLines;

            if(strcmp(lcdBuffer[lineB], "!!!CRITICAL!!!") == 0){
                if(critRep < 2){
                    lcd.setCursor(0, 0);
                    lcd.print(lcdBuffer[lineB]);
                    lcd.setCursor(0, 1);
                    lcd.print(lcdBuffer[lineB]);
                    vTaskDelay(pdMS_TO_TICKS(1000));
                    critRep++;
                    continue;
                }
                critRep = 0;
            }

            lcd.setCursor(0, 0);
            lcd.print(lcdBuffer[lineA]);
            lcd.setCursor(0, 1);
            lcd.print(lcdBuffer[lineB]);
            vTaskDelay(pdMS_TO_TICKS(1000));

            curLine = (curLine+1) % numLines;
        }
    }
}