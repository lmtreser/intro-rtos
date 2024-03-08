/*  Códigos de ejemplo de los tutoriales de www.luisllamas.es
    Enlace entrada : https :  //www.luisllamas.es/multitarea-en-arduino-blink-sin-delay/
    Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa
*/

//Blink without delay
unsigned long interval = 1000;
unsigned long previousMillis;

bool state = false;

void debug(String text) {
  Serial.print(millis());
  Serial.print('\t');
  Serial.println(text);
}

void setup() {
  Serial.begin(115200);
  // Capturar el primer millis
  previousMillis = millis();
}

void loop() {
  // Esta es la parte importante del ejemplo
  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
    switchLed();
    previousMillis = millis();
  }
}

void switchLed() {
  state = !state;
  if (state) debug("ON");
  if (!state) debug("OFF");
}