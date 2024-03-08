#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <LiquidCrystal.h>            // include LCD library function

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  //RS, E, D4, D5, D6, D7
QueueHandle_t xQueue;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  xQueue = xQueueCreate(5, sizeof(int));
  if (xQueue != NULL) {
    xTaskCreate(AdcTask, "Sender", 240, NULL, 1, NULL);
    xTaskCreate(LcdTask, "Receiver", 240, NULL, 2, NULL);
    vTaskStartScheduler();
  } else {
    /* The queue could not be created. */
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}

void AdcTask(void *pvParameters) {


  for (;;) {
    int adc_value;
    adc_value = analogRead(A4);
    xQueueSend(xQueue, &adc_value, portMAX_DELAY == pdPASS);
    Serial.print("AdcTask = ");
    Serial.println(adc_value);
    //vTaskDelay(100);
  }
}


void LcdTask(void *pvParameters) {
  int ReceivedValue = 0;
  for (;;) {

    if (xQueueReceive(xQueue, &ReceivedValue, portMAX_DELAY) == pdPASS) {
      Serial.print("Received = ");
      Serial.println(ReceivedValue);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ADC : ");
      lcd.setCursor(6, 0);
      lcd.print(ReceivedValue);
    }
    taskYIELD();
  }
}
