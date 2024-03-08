// Include Arduino FreeRTOS library
#include <Arduino_FreeRTOS.h>
#include "task.h"

TaskHandle_t TaskHandle_2;  // handler for Task2

void setup() {
  Serial.begin(9600);  // Enable serial communication library.
  pinMode(4, OUTPUT);  // define LED1 pin as a digital output
  pinMode(5, OUTPUT);  // define LED2 pin as a digital output

  //Create the first task at priority 1
  // Name of task is "LED1"
  // Stack size is set to 100
  // we do not pass any value to Task1. Hence, third agument is NULL
  // Set the priority of task to one
  // Task1 handler is not used. Therefore set to Null
  xTaskCreate(Task1, "LED1", 100, NULL, 1, NULL);
  // Start FreeRTOS scheduler in Preemptive timing silicing mode
  vTaskStartScheduler();
}

void loop() {
  // Do nothing as schduler will allocated CPU to Task1 and Task2 automatically
}

/* Task1 with priority 1 */
void Task1(void* pvParameters) {

  while (1) {
    Serial.println("Task1 Running");                          // print "Task1 Running" on Arduino Serial Monitor
    digitalWrite(4, HIGH);                                    // sets the digital pin 4 on
    digitalWrite(5, LOW);                                     // sets the digital pin 5 off
    xTaskCreate(Task2, "LED2", 100, NULL, 2, &TaskHandle_2);  // create task2 with priority 2
    vTaskDelay(100 / portTICK_PERIOD_MS);                     // wait for one second
  }
}

/* Task2 with priority 2 */
void Task2(void* pvParameters) {
  //digitalWrite(5, HIGH); // sets the digital pin 5 high
  //digitalWrite(4, LOW); // sets the digital pin 4 low
  Serial.println("Task2 is runnig and about to delete itself");
  vTaskDelete(TaskHandle_2);  //Delete own task by passing NULL(TaskHandle_2 can also be used)
}
