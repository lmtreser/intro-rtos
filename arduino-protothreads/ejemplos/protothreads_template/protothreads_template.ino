/*
    Ejemplo usando la librería ProtoThreads - Agosto de 2022

    No se pueden usar variables locales dentro de cada hilo ya que el
    contenido se perdería, tenemos dos alternativas: variables globales
    o usar variables estáticas.

*/

#include "protothreads.h"

//Constantes y variables
const int BOTON = 2;
const int TIEMPO = 1000;
int datos = 0;

static struct pt pt1, pt2, pt3, pt4; //Declarar 4 protothreads

//Hilo Nro. 1
static int tarea1(struct pt *pt) {

  static unsigned long lastTime = 0;

  PT_BEGIN(pt);
  while (1) {
    Serial.println("EJECUTANDO HILO 1");
    PT_WAIT_UNTIL(pt, millis() - lastTime > TIEMPO); //Bloqueo
    Serial.print("Incrementando la variable \"Datos\": ");
    Serial.println(datos);
    Serial.println("-------");
    lastTime = millis();
    datos++;
    PT_YIELD(pt);
  }
  PT_END(pt);
}

//Hilo Nro. 2
static int tarea2(struct pt *pt) {
  PT_BEGIN(pt);
  while (1) {
    Serial.println("EJECUTANDO HILO 2");
    PT_WAIT_UNTIL(pt, datos > 10);
    Serial.println("---------------------------");
    Serial.println("Adquiere bloqueo el Hilo 2");
    Serial.println("La variable datos llego a 10");
    Serial.println("---------------------------");
    datos = 0;
    PT_YIELD(pt);
  }
  PT_END(pt);
}

//Hilo Nro. 3
static int tarea3(struct pt *pt) {
  PT_BEGIN(pt);
  while (1) {
    Serial.println("EJECUTANDO HILO 3");
    PT_WAIT_UNTIL(pt, datos == 5);
    Serial.println("Adquiere bloqueo el Hilo 3");
    Serial.println("---------------------------");
    PT_YIELD(pt);
  }
  PT_END(pt);
}

//Hilo Nro. 4
static int tarea4(struct pt *pt) {
  PT_BEGIN(pt);
  while (1) {
    bool buttonState = digitalRead(BOTON);
    if (buttonState == LOW) {
      PT_SLEEP(pt, 20);
      buttonState = digitalRead(BOTON);
      if (buttonState == HIGH) {
        Serial.println("EJECUTANDO HILO 4");
        Serial.println("Botón presionado!!!");
        datos = 6;
      }
    }
    PT_YIELD(pt);
  }
  PT_END(pt);
}

void setup() {

  Serial.begin(9600);
  pinMode(BOTON, INPUT);

  //Inicializar todos los protothreads
  PT_INIT(&pt1);
  PT_INIT(&pt2);
  PT_INIT(&pt3);
  PT_INIT(&pt4);
}

void loop() {

  //Llamar todos los protothreads
  tarea1(&pt1);
  tarea2(&pt2);
  tarea3(&pt3);
  tarea4(&pt4);
}
