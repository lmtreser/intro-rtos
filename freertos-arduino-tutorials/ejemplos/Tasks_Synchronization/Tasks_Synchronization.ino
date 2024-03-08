// Include header files of FreeRTOS and event groups
#include <Arduino_FreeRTOS.h>
#include "event_groups.h"

// define three event flag bit variable
#define TASK1_BIT (1UL << 0UL)  // zero shift for bit0
#define TASK2_BIT (1UL << 1UL)  // 1 shift for flag  bit 1
#define TASK3_BIT (1UL << 2UL)  // 2 shift for flag bit 2

//  declare a event grounp handler variable
EventGroupHandle_t xEventGroup;

// A constant to define 500ms delay
//because we use to periodically execute each task
//after every 500ms
const TickType_t xDelay500ms = pdMS_TO_TICKS(500);

void setup() {
  // intialize uart module with baud rate of 9600
  Serial.begin(9600);
  //create event group and assign it a earlier created referene handler
  xEventGroup = xEventGroupCreate();
  // Create three tasks which are used to release event with
  // the help of above defined event flags
  xTaskCreate(InputTask1, "Input Task 1", 100, NULL, 1, NULL);
  xTaskCreate(InputTask2, "Input Task 2", 100, NULL, 1, NULL);
  xTaskCreate(InputTask3, "Input Task 3", 100, NULL, 1, NULL);
  //Create output task that will execute only when all three events occured
  xTaskCreate(OutputTask, "Output Task", 100, NULL, 1, NULL);
}

// defintion of input task1
void InputTask1(void *pvParameters) {
  while (1) {
    // set flag bit TASK1_BIT
    xEventGroupSetBits(xEventGroup, TASK1_BIT);
    //delay this task for 500ms
    vTaskDelay(xDelay500ms);
  }
}

// defintion of input task2
void InputTask2(void *pvParameters) {
  while (1) {
    // set flag bit TASK2_BIT
    xEventGroupSetBits(xEventGroup, TASK2_BIT);
    //delay this task for 500ms
    vTaskDelay(xDelay500ms);
  }
}

// defintion of input task3
void InputTask3(void *pvParameters) {
  while (1) {
    // set flag bit TASK2_BIT
    xEventGroupSetBits(xEventGroup, TASK3_BIT);
    //delay this task for 500ms
    vTaskDelay(xDelay500ms);
  }
}

//  Definition of output task
void OutputTask(void *pvParameters) {
  // define a variable which holds the state of events
  const EventBits_t xBitsToWaitFor = (TASK1_BIT | TASK2_BIT | TASK3_BIT);
  EventBits_t xEventGroupValue;
  while (1) {
    xEventGroupValue = xEventGroupWaitBits(xEventGroup,
                                           xBitsToWaitFor,
                                           pdTRUE,
                                           pdTRUE,
                                           portMAX_DELAY);
    if ((xEventGroupValue & TASK1_BIT) != 0) {
      Serial.println("Task1 event occured");
    }
    if ((xEventGroupValue & TASK2_BIT != 0)) {
      Serial.println("Task2 event occured");
    }
    if ((xEventGroupValue & TASK3_BIT != 0)) {
      Serial.println("Task3 event occured");
    }
  }
}

void loop() {}
