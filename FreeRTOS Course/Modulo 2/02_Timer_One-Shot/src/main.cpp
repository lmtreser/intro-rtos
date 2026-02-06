#include <Arduino.h>

TimerHandle_t xOneShotTimer;

void vOneShotCallback(TimerHandle_t xTimer) {
  Serial.println("Evento one-shot ejecutado");
}

void setup() {
  Serial.begin(115200);

  xOneShotTimer = xTimerCreate("OneShot",            // Nombre del timer
                               pdMS_TO_TICKS(5000),  // Tiempo
                               pdFALSE,              // No se repite
                               nullptr,              // Id
                               vOneShotCallback);    // Callback

  xTimerStart(xOneShotTimer, 0);
}

void loop() {
}