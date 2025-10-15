/*  FreeRTOS es un sistema operativo en tiempo real (RTOS) ligero y de código abierto.
    Proporciona un marco para ejecutar múltiples tareas simultáneamente, cada una con 
    su propia prioridad y programación de ejecución. En lugar de ejecutar código línea 
    por línea, FreeRTOS permite crear tareas independientes entre las que el procesador
    puede alternar rápidamente según la prioridad de la tarea.

    Created 13 Oct 2025
    by Lucas Martin Treser
*/
#include <Arduino_FreeRTOS.h>

/*  Declarar el identificador de tarea (TaskHandle). Una TaskHandle_t es una variable 
    que apunta a una tarea de FreeRTOS, lo que permite controlarla, como reanudarla, 
    detenerla o eliminarla. En este ejemplo, no necesitaremos el identificador de tarea, 
    pero lo crearemos para mostrarle cómo se hace.
*/
TaskHandle_t handlePot = NULL, handleLed = NULL, handleSerial = NULL;

const int POTENCIOMETER = A0;
const int LED = 3;
int potValue = 0;  // Global variable (warning!)

void taskPot(void *pvParameters) {
  for (;;) {  // Infinite loop
    potValue = analogRead(POTENCIOMETER);

    /* El stack es un área de memoria dedicada a cada tarea de FreeRTOS, que se utiliza
    para almacenar datos temporales como variables locales, información de llamadas a 
    funciones y el estado de la tarea durante la ejecución. Cada tarea tiene su propia
    pila, que se asigna al crearla. 
   
    Existe una función que se puede llamar dentro de una tarea para determinar el uso
    del stack: uxTaskGetStackHighWaterMark(). Esta función determina el tamaño de pila
    asignado que no se utiliza.
    */
    Serial.print("Task POT run, free stack (words):");
    Serial.println(uxTaskGetStackHighWaterMark(handlePot));

    /* El heap es un conjunto de memoria compartida en la SRAM del procesador, que se 
    utiliza para la asignación dinámica de memoria, incluyendo pilas de tareas, búferes
    y otros datos de ejecución asignados por FreeRTOS o el núcleo Arduino. Podemos 
    llamar a la función xPortGetFreeHeapSize() en nuestro código para determinar el 
    heap libre. Esta función no está implementada en la biblioteca Arduino FreeRTOS.
    */
    vTaskDelay(pdMS_TO_TICKS(50));  // read every 50 ms
  }
}

void taskLed(void *pvParameters) {
  for (;;) {
    int pwm = map(potValue, 0, 1023, 0, 255);
    analogWrite(LED, pwm);
    Serial.print("Task LED run, free stack:");
    Serial.println(uxTaskGetStackHighWaterMark(handleLed));
    vTaskDelay(pdMS_TO_TICKS(20));
  }
}

void taskSerial(void *pvParameters) {
  for (;;) {
    Serial.print("Task SERIAL run, free stack:");
    Serial.println(uxTaskGetStackHighWaterMark(handleSerial));
    Serial.println(potValue);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

  // Task function, Task name, Stack size (words), Parameters, Priority, Task handle, Core
  xTaskCreate(taskPot, "Tarea1", 128, NULL, 1, &handlePot);
  xTaskCreate(taskLed, "Tarea2", 128, NULL, 1, &handleLed);
  xTaskCreate(taskSerial, "Tarea3", 128, NULL, 1, &handleSerial);
}

void loop() {
  // El scheduler se encarga del resto
}
