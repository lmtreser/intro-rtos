#include <Arduino_FreeRTOS.h>
#include "semphr.h"

#define LED 13

SemaphoreHandle_t xBinarySemaphore;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  xBinarySemaphore = xSemaphoreCreateBinary();
  xTaskCreate(LedOnTask, "LedON", 100, NULL, 1, NULL);
  xTaskCreate(LedoffTask, "LedOFF", 100, NULL, 1, NULL);
  xSemaphoreGive(xBinarySemaphore);
}

void loop() {}

void LedOnTask(void *pvParameters) {
  while (1) {
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("Inside LedOnTask");
    digitalWrite(LED, LOW);
    xSemaphoreGive(xBinarySemaphore);
    vTaskDelay(1);
  }
}

void LedoffTask(void *pvParameters) {
  while (1) {
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("Inside LedffTask");
    digitalWrite(LED, HIGH);
    xSemaphoreGive(xBinarySemaphore);
    vTaskDelay(1);
  }
}
