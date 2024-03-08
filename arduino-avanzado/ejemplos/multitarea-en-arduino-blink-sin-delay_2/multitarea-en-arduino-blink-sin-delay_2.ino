/*  Códigos de ejemplo de los tutoriales de www.luisllamas.es
    Enlace entrada : https :  //www.luisllamas.es/multitarea-en-arduino-blink-sin-delay/
    Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa
*/

bool state = false;
// Muestra valores para el debug

void debug(char* text) {
  Serial.print(millis());
  Serial.print('\t');
  Serial.println(text);
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  toggleLed();
  delay(1000);
}

// Cambia el estado del Led
void toggleLed() {
  state = !state;
  if (state) debug("ON");
  if (!state) debug("OFF");
}