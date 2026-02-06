#include <Arduino.h>

SemaphoreHandle_t xSerialMutex;

void Task1(void* pvParams) {
  (void)pvParams;
  for (;;) {
    if (xSemaphoreTake(xSerialMutex, portMAX_DELAY) == pdTRUE) {
      Serial.println("Mensaje desde Tarea 1");
      xSemaphoreGive(xSerialMutex);
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void Task2(void* pvParams) {
  (void)pvParams;
  for (;;) {
    if (xSemaphoreTake(xSerialMutex, portMAX_DELAY) == pdTRUE) {
      Serial.println("Mensaje desde Tarea 2");
      xSemaphoreGive(xSerialMutex);
    }
    vTaskDelay(pdMS_TO_TICKS(700));
  }
}

void setup() {
  Serial.begin(115200);
  xSerialMutex = xSemaphoreCreateMutex();

  xTaskCreate(Task1, "Tarea1", 2048, nullptr, 1, nullptr);
  xTaskCreate(Task2, "Tarea2", 2048, nullptr, 1, nullptr);
}

void loop() {
}