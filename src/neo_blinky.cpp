#include "neo_blinky.h"

Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);

uint32_t scaleColor(uint32_t color, float brightness){
    if(brightness < 0) brightness = 0;
    if(brightness > 1) brightness = 1;

    uint8_t r = ((color>>16) & 0xFF) * brightness;
    uint8_t g = ((color>>8) & 0xFF) * brightness;
    uint8_t b = ((color) & 0xFF) * brightness;
    return strip.Color(r,g,b);
}

void neo_blinky(void *pvParameters){

    strip.begin();
    // Set all pixels to off to start
    strip.clear();
    strip.show();

    uint32_t baseColor = strip.Color(0,0,0);

    while(1) {
        if(xSemaphoreTake(xHumidSemaphore, portMAX_DELAY) == pdTRUE){
            if(glob_humidity < 70) baseColor = strip.Color(0, 255, 0); // Set strip to green
            else if(glob_humidity < 80) baseColor = strip.Color(255, 255, 0); // Set strip to yellow
            else baseColor = strip.Color(255, 0, 0); // Set strip to red
            strip.show();
        }
        for(float b=0; b<=1; b+=0.05){
            strip.setPixelColor(0, scaleColor(baseColor, b));
            strip.show();
            vTaskDelay(BREATHING_DELAY);
        }
        for(float b=1; b>=0; b-=0.05){
            strip.setPixelColor(0, scaleColor(baseColor, b));
            strip.show();
            vTaskDelay(BREATHING_DELAY);
        }
    }
}