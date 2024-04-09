/*
   Ejemplo usando la librería ProtoThreads
   Agosto de 2022 -

  No se pueden usar variables locales dentro de cada hilo ya que el
  contenido se perdería, tenemos dos alternativas: variables globales
  o usar variables estáticas.

*/

#include <LiquidCrystal_I2C.h>
#include <pt.h>
#include "RTClib.h"
#include "DHT.h"

//Objetos
LiquidCrystal_I2C pantalla(0x27, 16, 2);
DHT sensor(2, DHT11);
RTC_DS1307 reloj;

//Constantes y variables
const int LED_PIN = 3;
const int TIEMPO_LED = 300;
const int TIEMPO_RTC = 1000;
const int TIEMPO_DHT = 2000;

String lectura;
String tiempo;

byte grados[] = {
  B00111,
  B00101,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

//Declarar 3 protothreads
static struct pt pt1, pt2, pt3;

//Hilo #1: LED blink cada 300ms
static int toogleLed(struct pt *pt) {
  static unsigned long lastTimeBlink = 0;
  PT_BEGIN(pt); //Comienza el hilo
  while (1) {
    lastTimeBlink = millis();
    Serial.println("Ejecutando Hilo #1(a)");
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > TIEMPO_LED); //Bloqueo
    Serial.println("Adquiere bloqueo el Hilo #1(a)");
    digitalWrite(LED_PIN, HIGH);
    lastTimeBlink = millis();
    Serial.println("Ejecutando Hilo #1(b)");
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > TIEMPO_LED);
    Serial.println("Adquiere bloqueo el Hilo #1(b)");
    digitalWrite(LED_PIN, LOW);
  }
  PT_END(pt); //Finaliza el hilo
}

//Hilo #2: lee datos del sensor
static int getSensor(struct pt *pt) {
  static unsigned long lastTimeDht = 0;
  PT_BEGIN(pt);
  while (1) {
    lastTimeDht = millis();
    Serial.println("Ejecutando Hilo #2");
    PT_WAIT_UNTIL(pt, millis() - lastTimeDht > TIEMPO_DHT);
    Serial.println("Adquiere bloqueo el Hilo #2");
    float humedad = sensor.readHumidity();
    float temperatura = sensor.readTemperature();
    lectura = String(humedad) + "%RH " + String(temperatura) + " C";
  }
  PT_END(pt);
}

//Hilo #3: lee datos del reloj
static int getTime(struct pt *pt) {
  static unsigned long lastTimeCheck = 0;
  PT_BEGIN(pt);
  while (1) {
    lastTimeCheck = millis();
    Serial.println("Ejecutando Hilo #3");
    PT_WAIT_UNTIL(pt, millis() - lastTimeCheck > TIEMPO_RTC);
    Serial.println("Adquiere bloqueo el Hilo #3");
    DateTime now = reloj.now();
    tiempo = String(now.year()) + "/" + String(now.month()) + "/" +
             String(now.day()) + " " + String(now.hour()) + ":" +
             String(now.minute());
  }
  PT_END(pt);
}

// **************************************************** //
void setup() {

  pinMode(LED_PIN, OUTPUT);

  //Solo para depuración
  Serial.begin(9600);
  
  //Inicializar la pantalla
  pantalla.init();
  pantalla.backlight();
  pantalla.createChar(0, grados);

  //Inicializar el sensor
  sensor.begin();

  //Inicializar el reloj
  if (! reloj.begin()) {
    pantalla.clear();
    pantalla.setCursor(0, 0);
    pantalla.print("Falla RTC");
    while (1) delay(10);
  }

  if (! reloj.isrunning()) {
    //Ajusta el RTC con la fecha y hora de compilación del sketch.
    reloj.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // Ajusta el RTC con el siguiente formato: Enero 21, 2022 3am
    // rtc.adjust(DateTime(2022, 1, 21, 3, 0, 0));
  }

  //Inicializar todos los protothreads
  PT_INIT(&pt1);
  PT_INIT(&pt2);
  PT_INIT(&pt3);
}

void loop() {

  //Llamar todos los protothreads
  toogleLed(&pt1);
  getSensor(&pt2);
  getTime(&pt3);

  //pantalla.clear();
  pantalla.setCursor(0, 0);
  pantalla.print(tiempo);
  pantalla.setCursor(0, 1);
  pantalla.print(lectura);
  pantalla.setCursor(14, 1);
  pantalla.write(0); //Simbolo grados

}
