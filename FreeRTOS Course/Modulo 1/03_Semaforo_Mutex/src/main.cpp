#include <Arduino.h>

const uint8_t LED_PIN = 2;
const uint8_t BTN_PIN = 0;

static const TickType_t DEBOUNCE_TICKS = pdMS_TO_TICKS(50);
volatile TickType_t     last_isr_tick  = 0;
static uint8_t          sharedCounter  = 0;  // Recurso compartido (variable global)

SemaphoreHandle_t xButtonSemaphore;
SemaphoreHandle_t xSerialMutex;

// La interrupción notifica a la tarea que el botón fue presionado
void IRAM_ATTR isrButton() {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  TickType_t now                      = xTaskGetTickCountFromISR();

  if ((now - last_isr_tick) > DEBOUNCE_TICKS) {  // Debounce
    last_isr_tick = now;
    if (xButtonSemaphore != NULL) {  // check por seguridad
      xSemaphoreGiveFromISR(xButtonSemaphore, &xHigherPriorityTaskWoken);
      portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
  }
}

// Tarea que cambia el estado del LED al presionar el botón
void TaskButtonHandler(void* pvParams) {
  (void)pvParams;
  for (;;) {
    if (xSemaphoreTake(xButtonSemaphore, portMAX_DELAY) == pdTRUE) {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      // Protección de acceso concurrente a Serial y variable global
      if (xSerialMutex != NULL && xSemaphoreTake(xSerialMutex, portMAX_DELAY) == pdTRUE) {
        sharedCounter++;  // actualizar recurso compartido
        Serial.printf("Botón presionado -> LED cambiado\n");
        xSemaphoreGive(xSerialMutex);
      }
      vTaskDelay(pdMS_TO_TICKS(10));
    }
  }
}

// Tarea que periódicamente imprime el valor del contador de pulsaciones
void TaskLogger(void* pvParams) {
  (void)pvParams;
  for (;;) {
    if (xSerialMutex != NULL && xSemaphoreTake(xSerialMutex, pdMS_TO_TICKS(200)) == pdTRUE) {
      uint8_t counter = sharedCounter;
      Serial.printf("Pulsaciones: %d\n", counter);
      xSemaphoreGive(xSerialMutex);
    }
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);

  xButtonSemaphore = xSemaphoreCreateBinary();
  xSerialMutex     = xSemaphoreCreateMutex();

  if (xButtonSemaphore == NULL || xSerialMutex == NULL) {
    Serial.printf("Error: no se pudieron crear semáforos/mutex\n");
  }

  attachInterrupt(digitalPinToInterrupt(BTN_PIN), isrButton, FALLING);
  xTaskCreate(TaskButtonHandler, "ButtonTask", 2048, nullptr, 1, nullptr);
  xTaskCreate(TaskLogger, "LoggerTask", 2048, nullptr, 1, nullptr);
}

void loop() {
}