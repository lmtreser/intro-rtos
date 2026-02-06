#include <Arduino.h>
#include <DHT.h>

const uint8_t LED_PIN  = 2;
const uint8_t DHT_PIN  = 4;
const uint8_t DHT_TYPE = DHT22;

DHT dht{DHT_PIN, DHT_TYPE};

TimerHandle_t xSensorTimer;
TimerHandle_t xOneShotTimer;

// Callback del timer
void vSensorTimerCallback(TimerHandle_t xTimer) {
  float temperature = dht.readTemperature();
  float humidity    = dht.readHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {
    Serial.printf("Temp: %.2f °C | Hum: %.2f %%\n", temperature, humidity);
  }

  else {
    Serial.printf("Error leyendo DHT22\n");
  }
}

void vOneShotCallback(TimerHandle_t xTimer) {
  Serial.printf("Evento one-shot ejecutado\n");
  digitalWrite(LED_PIN, HIGH);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  dht.begin();

  xSensorTimer = xTimerCreate("SensorTimer",        // Nombre
                              pdMS_TO_TICKS(2000),  // Período
                              pdTRUE,               // Auto-reload
                              nullptr,              // ID
                              vSensorTimerCallback  // Callback
  );

  xOneShotTimer = xTimerCreate("OneShot",            // Nombre
                               pdMS_TO_TICKS(3000),  // Período
                               pdFALSE,              // No se repite
                               nullptr,              // ID
                               vOneShotCallback);    // Callback

  if (xSensorTimer != nullptr && xOneShotTimer != nullptr) {
    xTimerStart(xSensorTimer, 0);
    xTimerStart(xOneShotTimer, 0);
    Serial.printf("Timers iniciados correctamente\n");
  } else {
    Serial.printf("Error creando timers\n");
  }
}

void loop() {
}