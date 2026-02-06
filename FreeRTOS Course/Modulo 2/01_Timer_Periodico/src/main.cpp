#include <Arduino.h>
#include <DHT.h>

const uint8_t DHT_PIN  = 4;
const uint8_t DHT_TYPE = DHT22;

DHT dht{DHT_PIN, DHT_TYPE};

TimerHandle_t xSensorTimer;

// Callback del timer
void vSensorTimerCallback(TimerHandle_t xTimer) {
  float temperature = dht.readTemperature();
  float humidity    = dht.readHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {
    Serial.printf("Temp: %.2f °C | Hum: %.2f %%\n", temperature, humidity);
  } else {
    Serial.println("Error leyendo DHT22");
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Crear timer periódico de 2000 ms (auto-reload activado)
  xSensorTimer = xTimerCreate("SensorTimer",        // Nombre
                              pdMS_TO_TICKS(2000),  // Período
                              pdTRUE,               // Auto-reload
                              nullptr,              // ID opcional
                              vSensorTimerCallback  // Función a ejecutar
  );

  if (xSensorTimer != nullptr) {
    xTimerStart(xSensorTimer, 0);  // Inicia el timer
    Serial.println("Timer iniciado correctamente");
  } else {
    Serial.println("Error creando timer");
  }
}

void loop() {
}