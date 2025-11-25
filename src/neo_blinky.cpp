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

uint32_t rainbow(float h, float s, float v){
    float r, g, b;
    int i = int(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    switch(i % 6){
        case 0: r=v; g=t; b=p; break;
        case 1: r=q; g=v; b=p; break;
        case 2: r=p; g=v; b=t; break;
        case 3: r=p; g=q; b=v; break;
        case 4: r=t; g=p; b=v; break;
        case 5: r=v; g=p; b=q; break;
    }

    return strip.Color(int(r*255), int(g*255), int(b*255));
}

void neo_blinky(void *pvParameters){

    strip.begin();
    // Set all pixels to off to start
    strip.clear();
    strip.show();

    uint32_t baseColor = strip.Color(0,0,0);

    float hue = 0;

    while(1) {
        xSemaphoreTake(xDataMutex, portMAX_DELAY);
        float humid = glob_humidity;
        xSemaphoreGive(xDataMutex);
        switch(neo_status){
            case 0:
                if(humid < 70) baseColor = strip.Color(0, 255, 0); // Set strip to green
                else if(humid < 80) baseColor = strip.Color(255, 255, 0); // Set strip to yellow
                else baseColor = strip.Color(255, 0, 0); // Set strip to red
                strip.show();
        
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
                break;
            case 1:
                strip.setPixelColor(0, rainbow(hue, 1.0, 1.0));
                strip.show();
                hue += 0.01;
                if(hue > 1) hue = 0;
                vTaskDelay(pdMS_TO_TICKS(100));
                break;
            case 2:
                strip.setPixelColor(0, rainbow(hue, 1.0, 1.0));
                strip.show();
                hue += 0.01;
                if(hue > 1) hue = 0;
                vTaskDelay(pdMS_TO_TICKS(20));
                break;
            default:
                break;
        }
    }
}