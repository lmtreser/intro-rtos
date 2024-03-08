// Include Arduino FreeRTOS library
#include <Arduino_FreeRTOS.h>
// include LCD library function
#include <LiquidCrystal.h>
// Include queue support
#include <queue.h>

//Define LCD pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  //RS, E, D4, D5, D6, D7

// Define a struct
struct pinRead {
  int pin;    // analog channel indentifier
  int value;  // sensor output value
};

QueueHandle_t structQueue;

void setup() {

  Serial.begin(9600);  // Enable serial communication library.
  lcd.begin(16, 2);    // Enable LCD library
  // create Structure Queue
  structQueue = xQueueCreate(10,                     // Queue length
                             sizeof(struct pinRead)  // Queue item size
  );

  if (structQueue != NULL) {

    // Create task that consumes the queue if it was created.
    xTaskCreate(TaskLcd,        // Task function
                "Displaydata",  // A name just for humans
                128,            // This stack size can be checked & adjusted by reading the Stack Highwater
                NULL,
                2,  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
                NULL);


    // Create task that publish data in the queue if it was created.
    xTaskCreate(TaskTempReadPin0,  // Task function
                "AnalogReadPin0",  // Task name
                128,               // Stack size
                NULL,
                1,  // Priority
                NULL);

    // Create other task that publish data in the queue if it was created.
    xTaskCreate(TaskLightReadPin1,  // Task function
                "AnalogReadPin1",   // Task name
                128,                // Stack size
                NULL,
                1,  // Priority
                NULL);
  }

  vTaskStartScheduler();
}

void loop() {
}

// Temperature value and adc number writing
void TaskTempReadPin0(void *pvParameters) {
  (void)pvParameters;

  for (;;) {

    struct pinRead currentPinRead;                            // define a structure of type pinRead
    currentPinRead.pin = 0;                                   // assign value '0' to pin element of struct
    currentPinRead.value = analogRead(A0);                    // Read adc value from A0 channel and store it in value element of struct
    xQueueSend(structQueue, &currentPinRead, portMAX_DELAY);  //write struct message to queue
    Serial.println("Channel_0");                              //print Channel_0 on serial monitor
    taskYIELD();                                              //terminate the task and inform schulder about it
  }
}

// Light Sensor value and adc number writing
void TaskLightReadPin1(void *pvParameters) {
  (void)pvParameters;

  for (;;) {

    struct pinRead currentPinRead;  // define a structure of type pinRead
    currentPinRead.pin = 1;         // assign value '1' to pin element of struct
    currentPinRead.value = analogRead(A1);
    // Read adc value from A1 channel and store it in value element of struct
    xQueueSend(structQueue, &currentPinRead, portMAX_DELAY);  //write struct message to queue
    Serial.println("Channel_1");                              //print Channel_1 on serial monitor
    taskYIELD();                                              //terminate the task and inform schulder about it
  }
}

void TaskLcd(void *pvParameters) {
  (void)pvParameters;

  for (;;) {
    int TEMP = 0;                   // temporary variable to hold Temperature adc0 value
    int LDR = 0;                    // temporary variable to hold LDR adc1 value
    struct pinRead currentPinRead;  // structure to hold receiv data
    // Read structure elements from queue and check if data received successfully
    if (xQueueReceive(structQueue, &currentPinRead, portMAX_DELAY) == pdPASS) {
      // print received data elements on serial montor
      Serial.print("Pin: ");
      Serial.print(currentPinRead.pin);
      Serial.print(" Value: ");
      Serial.println(currentPinRead.value);

      // If condition checks,  if data receive from channel zero
      // If yes, store sensor value member of structure in temporary temp variable
      if (currentPinRead.pin == 0) {
        TEMP = (currentPinRead.value * 500) / 1024;  // convert adc value into temperature

        // dispay temperature sensor output in first line of 16x2 LCD
        lcd.setCursor(0, 0);
        lcd.print("Temp = ");
        lcd.setCursor(7, 0);
        lcd.print(TEMP);
        lcd.print("'C");
      }

      // If condition checks,  if data receive from channel one (A1)
      // If yes, store sensor value member of structure in temporary LDR variable
      if (currentPinRead.pin == 1) {

        LDR = map(currentPinRead.value, 0, 1023, 0, 255);  //map ADC1 value to light value
        // dispay light dependent resistor output in first line of 16x2 LCD
        lcd.setCursor(0, 1);
        lcd.print("LIGHT = ");
        lcd.setCursor(7, 1);
        lcd.print(LDR);
        lcd.print("LUX");
      }
    }
    taskYIELD();  // terminate the task and inform schulder about it
  }
}
