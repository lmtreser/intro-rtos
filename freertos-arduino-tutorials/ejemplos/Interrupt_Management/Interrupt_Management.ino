#include <Arduino_FreeRTOS.h>
#include "queue.h"

QueueHandle_t xStringQueue;
int timer1_counter;

void setup() {

  Serial.begin(9600);
  xTaskCreate(vStringPrinter, " String Printer", 100, NULL, 1, NULL);
  xStringQueue = xQueueCreate(5, sizeof(char *));
  InterruptInit();
}

void vStringPrinter(void *pvParameters) {
  char *pcString;
  while (1) {
    xQueueReceive(xStringQueue, &pcString, portMAX_DELAY);
    Serial.println(pcString);
  }
}

ISR(TIMER1_OVF_vect) {
  TCNT1 = timer1_counter;
  uint32_t receivedNumber;
  static const char *pcStrings[] = {
    "Hello\r\n",
    "Hi\r\n",
    "I\r\n",
    "am\r\n",
    "here\r\n",
  };
  xQueueSendToBackFromISR(xStringQueue, &pcStrings[0], pdFALSE);
}

void loop() {}

void InterruptInit() {
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  timer1_counter = 34286;
  TCNT1 = timer1_counter;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();
}
