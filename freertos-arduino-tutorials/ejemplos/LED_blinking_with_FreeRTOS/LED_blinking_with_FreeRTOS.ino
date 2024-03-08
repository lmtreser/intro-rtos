#include <Arduino_FreeRTOS.h>

void setup() {
  //Initialize the Serial Monitor with 9600 baud rate
  Serial.begin(9600);
  Serial.println(F("In Setup function"));
  //Set the digital pins 8 to 11 as digital output pins
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  //Create three tasks with labels Task1, Task2 and Task3 and assign the priority as 1, 2 and 3 respectively.
  //We also create the fourth task labeled as IdelTask when there is no task in
  //operation and it has the highest priority.

  xTaskCreate(MyTask1, "Task1", 100, NULL, 1, NULL);
  xTaskCreate(MyTask2, "Task2", 100, NULL, 2, NULL);
  xTaskCreate(MyTask3, "Task3", 100, NULL, 3, NULL);
  xTaskCreate(MyIdleTask, "IdleTask", 100, NULL, 0, NULL);
}

//We can change the priority of task according to our desire by changing the numeric’s //between NULL texts.
void loop() {
  //There is no instruction in the loop section of the code.
  // Because each task executes on interrupt after specified time
}

//The following function is Task1. We display the task label on Serial monitor.
static void MyTask1(void* pvParameters) {

  while (1) {
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    Serial.println(F("Task1"));
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

//Similarly this is task 2
static void MyTask2(void* pvParameters) {
  while (1) {
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    Serial.println(F("Task2"));
    vTaskDelay(110 / portTICK_PERIOD_MS);
  }
}

//Similarly this is task 3
static void MyTask3(void* pvParameters) {
  while (1) {
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    Serial.println(F("Task3"));
    vTaskDelay(120 / portTICK_PERIOD_MS);
  }
}

//This is the idle task which has the lowest priority and calls when no task is running.
static void MyIdleTask(void* pvParameters) {
  while (1) {
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    Serial.println(F("Idle state"));
    delay(50);
  }
}
