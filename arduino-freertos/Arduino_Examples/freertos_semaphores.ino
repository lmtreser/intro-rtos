/*
    Uso de semáforo binario en FreeRTOS con Arduino UNO. 
    Dos tareas acceden a un recurso compartido (Serial) utilizando un semáforo 
    para evitar conflictos. El funcionamiento es el siguiente:

    1. Se crea un semaforo binario, inicialmente libre (xSemaphoreGive()).
    2. task1 y task2 intentan tomarlo (xSemaphoreTake()).
    3. Solo una tarea a la vez accede al recurso compartido (Serial).
    4. Cuando termina, lo libera (xSemaphoreGive()).
    5. La otra tarea puede continuar.

    Created 13 Oct 2025
    by Lucas Martin Treser
*/
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

SemaphoreHandle_t semaforo;

void task1(void *pvParameters) {
  for (;;) {
    // xSemaphoreTake(xSemaphore, xBlockTime); return pdFALSE/pdTRUE
    if (xSemaphoreTake(semaforo, portMAX_DELAY) == pdTRUE) { // Inicia sección crítica
      Serial.println("Tarea #1 accediendo al recurso");
      xSemaphoreGive(semaforo); // Finaliza sección critica
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void task2(void *pvParameters) {
  for (;;) {
    if (xSemaphoreTake(semaforo, portMAX_DELAY) == pdTRUE) {
      Serial.println("Tarea #2 accediendo al recurso");
      xSemaphoreGive(semaforo);
    }
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void setup() {
  Serial.begin(9600);

  semaforo = xSemaphoreCreateBinary();
  if (semaforo != NULL) {
    xSemaphoreGive(semaforo);  // Inicializar semáforo liberado
    xTaskCreate(task1, "Tarea A", 128, NULL, 1, NULL);
    xTaskCreate(task2, "Tarea B", 128, NULL, 1, NULL);
  }
}

void loop() {
}