/*
    Comunicación entre tareas usando COLAS en FreeRTOS con Arduino UNO.

    Dos tareas cooperan mediante una cola:
    - taskSensor: lee un valor analógico (potenciómetro o sensor) y lo envía por la cola.
    - taskSerial: recibe el valor desde la cola y lo imprime por Serial.

    La cola actúa como un búfer FIFO (First In, First Out), asegurando comunicación
    segura entre tareas sin necesidad de variables globales compartidas.

    Created 13 Oct 2025
    by Lucas Martin Treser
*/

#include <Arduino_FreeRTOS.h>
#include <queue.h>

QueueHandle_t data;  // Declaración del identificador de cola
const int POTENTIOMETER = A0;

void taskSensor(void *pvParameters) {
  int reading;
  for (;;) {
    reading = analogRead(POTENTIOMETER);
    /* xQueueSend(queue, item, ticksToWait)
       Envia un elemento a la cola. 
       Parámetros:
       - queue: identificador de la cola (data)
       - item: puntero al dato a enviar (&reading)
       - ticksToWait: tiempo máximo a esperar si la cola está llena

       En este caso usamos portMAX_DELAY, la tarea se bloquea indefinidamente 
       hasta que haya espacio libre en la cola, evitando pérdida de datos o
       ciclos de espera activa (polling).
    */
    xQueueSend(data, &reading, portMAX_DELAY);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void taskSerial(void *pvParameters) {
  int temperature;
  for (;;) {
    /* xQueueReceive(queue, buffer, ticksToWait)
       Recibe un elemento desde la cola.
       - queue: identificador de la cola (data)
       - buffer: puntero donde se guardará el dato recibido (&temperature)
       - ticksToWait: tiempo máximo a esperar si la cola está vacía

       portMAX_DELAY, la tarea se bloquea (queda dormida) hasta que otro 
       proceso envíe un nuevo dato. Esto ahorra CPU y garantiza sincronización
       perfecta entre productor y consumidor.
    */
    if (xQueueReceive(data, &temperature, portMAX_DELAY))
      Serial.print("Temperatura: ");
    Serial.println(temperature);
  }
}

void setup() {
  Serial.begin(9600);

   /* xQueueCreate(length, itemSize)
     Crea una cola capaz de almacenar 'length' elementos, 
     cada uno de tamaño 'itemSize' bytes.

     Aquí se crean 5 espacios para almacenar enteros (int).
     Si todas las posiciones están ocupadas, xQueueSend() bloqueará 
     la tarea hasta que se libere un espacio.
  */
  data = xQueueCreate(5, sizeof(int));
  xTaskCreate(taskSensor, "Sensor", 256, NULL, 1, NULL);
  xTaskCreate(taskSerial, "Display", 256, NULL, 1, NULL);
}

void loop() {
}
