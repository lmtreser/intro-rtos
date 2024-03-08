#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t interruptSemaphore;

void setup() {
  Serial.begin(9600);  // Enable serial communication library.
  pinMode(LED_BUILTIN, OUTPUT);

  // Create task for Arduino led
  xTaskCreate(TaskLedon,  // Task function
              "Ledon",    // Task name
              128,        // Stack size
              NULL,
              0,  // Priority
              NULL);
  xTaskCreate(TaskLedoff,  // Task function
              "Ledoff",    // Task name
              128,         // Stack size
              NULL,
              0,  // Priority
              NULL);
  interruptSemaphore = xSemaphoreCreateBinary();
  if (interruptSemaphore != NULL) {
    attachInterrupt(digitalPinToInterrupt(2), interruptHandler, HIGH);
  }
}

void loop() {}

void interruptHandler() {
  Serial.println("Semaphore is given");
  BaseType_t xHigherPriorityTaskWoken pdFALSE;
  xSemaphoreGiveFromISR(interruptSemaphore, &xHigherPriorityTaskWoken);
}

void TaskLedon(void *pvParameters) {
  (void)pvParameters;

  for (;;) {
    if (xSemaphoreTake(interruptSemaphore, portMAX_DELAY) == pdPASS) {
      Serial.println("TaskLedon Received Semaphore");
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
}

void TaskLedoff(void *pvParameters) {
  (void)pvParameters;
  for (;;) {
    if (xSemaphoreTake(interruptSemaphore, portMAX_DELAY) == pdPASS) {
      Serial.println("TaskLedoff Received Semaphore");
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}
