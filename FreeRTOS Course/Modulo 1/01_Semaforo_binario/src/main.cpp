/*  MÓDULO 1 — SINCRONIZACIÓN ENTRE TAREAS: Semáforos binarios

    Un semáforo binario se comporta como una bandera de evento, una
    tarea o una ISR la “levanta” (xSemaphoreGive()), y otra la “toma”
    (xSemaphoreTake()).

    Es ideal para decirle a una tarea que algo ocurrió, sin usar
    delay() ni polling.

    xSemaphoreCreateBinary() crea un semáforo binario inicialmente en 0
    (no disponible). TaskButtonHandler llama a xSemaphoreTake() y queda
    bloqueada esperando el semáforo.
    Cuando se presiona el botón (ISR), llama xSemaphoreGiveFromISR(),
    esto pone el semáforo a "disponible". portYIELD_FROM_ISR() forza
    (si corresponde) un cambio de contexto inmediato para ejecutar la
    tarea despierta. E
    En la tarea, xSemaphoreTake() devuelve pdTRUE: la tarea consume el
    semáforo (lo deja en 0) y continúa ejecutando. Luego la tarea vuelve
    al xSemaphoreTake y se bloquea otra vez hasta la próxima señal de la
    ISR.
*/
#include <Arduino.h>

const uint8_t LED_PIN = 2;
const uint8_t BTN_PIN = 0;

SemaphoreHandle_t xButtonSemaphore;

// Debounce: ignorar pulsos que ocurran antes de este umbral (ms)
static const TickType_t DEBOUNCE_TICKS = pdMS_TO_TICKS(50);
volatile TickType_t     last_isr_tick  = 0;

// La interrupción notifica a la tarea que el botón fue presionado
void IRAM_ATTR isrButton() {
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  TickType_t now                      = xTaskGetTickCountFromISR();

  // Debounce
  if ((now - last_isr_tick) > DEBOUNCE_TICKS) {
    last_isr_tick = now;
    xSemaphoreGiveFromISR(xButtonSemaphore, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
  }
}

void TaskButtonHandler(void* pvParams) {
  (void)pvParams;
  for (;;) {
    if (xSemaphoreTake(xButtonSemaphore, portMAX_DELAY) == pdTRUE) {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      Serial.println("Botón presionado -> LED cambiado");
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);

  xButtonSemaphore = xSemaphoreCreateBinary();
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), isrButton, FALLING);
  xTaskCreate(TaskButtonHandler, "ButtonTask", 2048, nullptr, 1, nullptr);
}

void loop() {
}