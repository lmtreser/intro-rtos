/*  Códigos de ejemplo de los tutoriales de www.luisllamas.es
    Enlace entrada : https :  //www.luisllamas.es/multitarea-en-arduino-blink-sin-delay/
    Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa
*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}