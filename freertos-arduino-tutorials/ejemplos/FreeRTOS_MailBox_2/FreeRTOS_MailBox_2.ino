#include <Arduino_FreeRTOS.h>
#include <queue.h>

QueueHandle_t xMailbox;
TaskHandle_t TaskHandle_1;  // handler for Task1
TaskHandle_t TaskHandle_2;  // handler for Task2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  xMailbox = xQueueCreate(1, sizeof(int32_t));
  Serial.begin(9600);  // Enable serial communication library.
  xTaskCreate(vUpdateMailbox, "Sender", 100, NULL, 1, &TaskHandle_1);
  xTaskCreate(vReadMailbox, "Receiver", 100, NULL, 1, &TaskHandle_2);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void vUpdateMailbox(void) {
  int32_t ulNewValue = 1;
  while (1) {
    xQueueOverwrite(xMailbox, &ulNewValue);
    Serial.println("Data written to mailbox");
    ulNewValue++;
    vTaskDelay(500);
  }
}

BaseType_t vReadMailbox(void) {
  int32_t value_received;
  while (1) {
    xQueuePeek(xMailbox, &value_received, portMAX_DELAY);
    Serial.print("Data Read from mailbox = ");
    Serial.println(value_received);
    vTaskDelay(100);
  }
}
