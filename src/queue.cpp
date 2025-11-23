#include "queue.h"

QueueHandle_t xSensorQueue = NULL;

// ===================== TASK 1: Value Task =====================
void ValueTask(void *pvParameters) {
    SensorData_t data;
    int id = 0;

    while (1)
    {
        // Tạo dữ liệu mô phỏng sensor
        data.temperature = 20.0 + (rand() % 1500) / 100.0;  // 20 - 35°C
        data.humidity = 40.0 + (rand() % 500) / 10.0;       // 40 - 90%
        data.sample_id = id++;

        // Gửi qua queue
        xQueueSend(xSensorQueue, &data, portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// ===================== TASK 2: Process Task =====================
void ProcessTask(void *pvParameters) {
    SensorData_t recv;

    while (1)
    {
        if (xQueueReceive(xSensorQueue, &recv, portMAX_DELAY))
        {
            if (recv.temperature > 30.0)
            {
                Serial.print("[CẢNH BÁO] Nhiệt độ cao: ");
                Serial.print(recv.temperature);
                Serial.print("°C (ID=");
                Serial.print(recv.sample_id);
                Serial.println(")");
            }
            else
            {
                Serial.print("Temp=");
                Serial.print(recv.temperature);
                Serial.print("°C Humidity=");
                Serial.print(recv.humidity);
                Serial.print("% (ID=");
                Serial.print(recv.sample_id);
                Serial.println(")");
            }
        }
    }
}