#include <Arduino_FreeRTOS.h>
#include <queue.h>

typedef struct xExampleStructure {
  TickType_t xTimeStamp;
  uint32_t ulValue;
} Example_t;

/* A mailbox is a queue, so its handle is stored in a variable of type
QueueHandle_t. */
QueueHandle_t xMailbox;
TaskHandle_t TaskHandle_1;  // handler for Task1
TaskHandle_t TaskHandle_2;  // handler for Task2

void setup() {
  // put your setup code here, to run once:
  xMailbox = xQueueCreate(1, sizeof(Example_t));
  Serial.begin(9600);  // Enable serial communication library.
  xTaskCreate(vUpdateMailbox, "Sender", 100, NULL, 1, &TaskHandle_1);
  xTaskCreate(vReadMailbox, "Receiver", 100, NULL, 1, &TaskHandle_2);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void vUpdateMailbox(uint32_t ulNewValue) {
  /* Example_t was defined in Listing 67. */
  Example_t xData;
  /* Write the new data into the Example_t structure.*/
  xData.ulValue = ulNewValue;
  /* Use the RTOS tick count as the time stamp stored in the Example_t structure. */
  xData.xTimeStamp = xTaskGetTickCount();
  /* Send the structure to the mailbox - overwriting any data that is already in the
mailbox. */
  xQueueOverwrite(xMailbox, &xData);
}

BaseType_t vReadMailbox(Example_t *pxData) {
  TickType_t xPreviousTimeStamp;
  BaseType_t xDataUpdated;
  /* This function updates an Example_t structure with the latest value received
from the mailbox. Record the time stamp already contained in *pxData before it
gets overwritten by the new data. */
  xPreviousTimeStamp = pxData->xTimeStamp;
  /* Update the Example_t structure pointed to by pxData with the data contained in
the mailbox. If xQueueReceive() was used here then the mailbox would be left
empty, and the data could not then be read by any other tasks. Using
xQueuePeek() instead of xQueueReceive() ensures the data remains in the mailbox.
A block time is specified, so the calling task will be placed in the Blocked
state to wait for the mailbox to contain data should the mailbox be empty. An
infinite block time is used, so it is not necessary to check the value returned
from xQueuePeek(), as xQueuePeek() will only return when data is available. */
  xQueuePeek(xMailbox, pxData, portMAX_DELAY);
  /* Return pdTRUE if the value read from the mailbox has been updated since this
function was last called. Otherwise return pdFALSE. */
  if (pxData->xTimeStamp > xPreviousTimeStamp) {
    xDataUpdated = pdTRUE;
  } else {
    xDataUpdated = pdFALSE;
  }
  return xDataUpdated;
}
