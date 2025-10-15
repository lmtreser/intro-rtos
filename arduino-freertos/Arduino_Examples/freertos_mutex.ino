/*  
    Este sketch demuestra el uso de un mutex para proteger un recurso compartido,
    en este caso una pantalla LCD y el puerto Serial, evitando que dos tareas escriban
    al mismo tiempo y produzcan resultados mezclados. El funcionamiento es el siguiente:
    
    1. Se crean dos tareas (task1 y task2) que incrementan una variable global 'count'.
    2. Cada tarea toma un mutex (xSemaphoreTake) antes de acceder al LCD y Serial.
    3. Cada tarea imprime su propio mensaje y el valor de 'count' en su respectiva línea
       del LCD, luego libera el mutex (xSemaphoreGive).
    4. Se usan delays fuera del mutex para permitir alternancia eficiente entre tareas.
    5. Se muestra el stack libre de cada tarea usando uxTaskGetStackHighWaterMark(NULL).
    
    Created 13 Oct 2025
    by Lucas Martin Treser
*/
#include <Arduino_FreeRTOS.h>
#include <LiquidCrystal_I2C.h>
#include <semphr.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
SemaphoreHandle_t mutexLCD;
int count = 0;  // Global variable (warning!)

void task1(void *pvParameters) {
  for (;;) {
    count++;
    if (xSemaphoreTake(mutexLCD, portMAX_DELAY)) {
      Serial.print("task1 run, free stack (words):");
      Serial.println(uxTaskGetStackHighWaterMark(NULL));

      lcd.setCursor(0, 0);
      lcd.print("task1 run: ");
      lcd.print(count);
      xSemaphoreGive(mutexLCD);
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void task2(void *pvParameters) {
  for (;;) {
    count++;
    if (xSemaphoreTake(mutexLCD, portMAX_DELAY)) {
      Serial.print("task2 run, free stack (words):");
      Serial.println(uxTaskGetStackHighWaterMark(NULL));

      lcd.setCursor(0, 1);
      lcd.print("task2 run: ");
      lcd.print(count);
      xSemaphoreGive(mutexLCD);
    }
    vTaskDelay(pdMS_TO_TICKS(300));
  }
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  mutexLCD = xSemaphoreCreateMutex();
  xTaskCreate(task1, "Tarea A", 256, NULL, 1, NULL);
  xTaskCreate(task2, "Tarea B", 256, NULL, 1, NULL);
}

void loop() {
}