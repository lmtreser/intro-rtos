#include <Arduino_FreeRTOS.h>
#include <queue.h>

static QueueHandle_t xQueue1 = NULL, xQueue2 = NULL;
static QueueSetHandle_t xQueueSet = NULL;

TaskHandle_t TaskHandle_1;  // handler for Task1
TaskHandle_t TaskHandle_2;  // handler for Task2

void setup() {
  Serial.begin(9600);  // Enable serial communication library.
  
  xQueue1 = xQueueCreate(1, sizeof(char*));
  xQueue2 = xQueueCreate(1, sizeof(char*));
  xQueueSet = xQueueCreateSet(1 * 2);

  xQueueAddToSet(xQueue1, xQueueSet);
  xQueueAddToSet(xQueue2, xQueueSet);
  xTaskCreate(Task1, "Sender1", 100, NULL, 1, &TaskHandle_1);
  xTaskCreate(Task2, "Sender2", 100, NULL, 1, &TaskHandle_2);
  xTaskCreate(vReceiverTask, "Receiver", 100, NULL, 2, NULL);
  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:
}

//definition of Task1
void Task1(void* pvParameters) {
  const char* const pcMessage = "Message from vSenderTask1";
  while (1) {
    vTaskDelay(100 / portTICK_PERIOD_MS);
    xQueueSend(xQueue1, &pcMessage, 0);
  }
}
//definition of Task2
void Task2(void* pvParameters) {
  const char* const pcMessage = "Message from vSenderTask2";
  while (1) {
    vTaskDelay(200 / portTICK_PERIOD_MS);
    xQueueSend(xQueue2, &pcMessage, 0);
  }
}
//definition of  Receiver Task
void vReceiverTask(void* pvParameters) {
  QueueHandle_t xQueueThatContainsData;
  char* pcReceivedString;
  for (;;) {
    xQueueThatContainsData = (QueueHandle_t)
      xQueueSelectFromSet(xQueueSet, portMAX_DELAY);
    xQueueReceive(xQueueThatContainsData, &pcReceivedString, 0);
    Serial.println(pcReceivedString);
  }
}
