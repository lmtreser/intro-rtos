/*  Códigos de ejemplo de los tutoriales de www.luisllamas.es
    Enlace entrada: https://www.luisllamas.es/implementar-una-red-de-petri-en-arduino/
    Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa
*/

#include "PetriNetLib.h"

enum Input {
  ForwardA = 0,
  ForwardB = 1,
  Unknown = 2
};

Input input;

PetriNet petriNet(8, 7);

void setup() {
  Serial.begin(9600);

  // Definicion de la red de petri del ejemplo
  // Entradas y salidas de los estados
  static uint8_t inputs0[] = { 0, 4 };
  static uint8_t outputs0[] = { 1, 5 };

  static uint8_t inputs1[] = { 1 };
  static uint8_t outputs1[] = { 2 };

  static uint8_t inputs2[] = { 2, 6 };
  static uint8_t outputs2[] = { 3, 7 };

  static uint8_t inputs3[] = { 3 };
  static uint8_t outputs3[] = { 0 };

  static uint8_t inputs4[] = { 5 };
  static uint8_t outputs4[] = { 6 };

  static uint8_t inputs5[] = { 7 };
  static uint8_t outputs5[] = { 4 };

  // Transiciones
  petriNet.SetTransition(
    0, inputs0, 2, outputs0, 2,
    []() -> bool {
      return input == Input::ForwardA || input == Input::ForwardB;
    },
    []() {
      Serial.println("Fired T0");
      printMarkup();
    });

  petriNet.SetTransition(
    1, inputs1, 1, outputs1, 1,
    []() -> bool {
      return input == Input::ForwardA;
    },
    []() {
      Serial.println("Fired T1");
      printMarkup();
    });

  petriNet.SetTransition(
    2, inputs2, 2, outputs2, 2,
    []() -> bool {
      return input == Input::ForwardA || input == Input::ForwardB;
    },
    []() {
      Serial.println("Fired T2");
      printMarkup();
    });

  petriNet.SetTransition(
    3, inputs3, 1, outputs3, 1,
    []() -> bool {
      return input == Input::ForwardA;
    },
    []() {
      Serial.println("Fired T3");
      printMarkup();
    });

  petriNet.SetTransition(
    4, inputs4, 1, outputs4, 1,
    []() -> bool {
      return input == Input::ForwardB;
    },
    []() {
      Serial.println("Fired T4");
      printMarkup();
      activateTimer();
    });

  petriNet.SetTransition(
    5, inputs5, 1, outputs5, 1,
    []() -> bool {
      return input == Input::ForwardB;
    },
    []() {
      Serial.println("Fired T5");
      printMarkup();
    });

  petriNet.SetTransition(6, outputs4, 1, inputs4, 1,
                         timerExpired,
                         []() {
                           Serial.println("Reseting T6");
                           printMarkup();
                         });

  // Marcado inicial
  petriNet.SetMarkup(0, 1);
  petriNet.SetMarkup(4, 1);

  printMarkup();  // Mostrar el estado inicial
}

void loop() {
  input = static_cast<Input>(readInput());

  petriNet.Update();
}

// Realiza la lectura de un caracter para el ejemplo
int readInput() {
  Input currentInput = Input::Unknown;
  if (Serial.available()) {
    char incomingChar = Serial.read();

    switch (incomingChar) {
      case 'A': currentInput = Input::ForwardA; break;
      case 'B': currentInput = Input::ForwardB; break;
      default: break;
    }
  }

  return currentInput;
}

// Para debug del ejemplo
void printMarkup() {
  Serial.print(petriNet.GetMarkup(0));
  Serial.print(petriNet.GetMarkup(1));
  Serial.print(petriNet.GetMarkup(2));
  Serial.println(petriNet.GetMarkup(3));

  Serial.print(petriNet.GetMarkup(4));
  Serial.print(petriNet.GetMarkup(5));
  Serial.print(petriNet.GetMarkup(6));
  Serial.println(petriNet.GetMarkup(7));
}

// Timer para la transicion 6
unsigned long previousMillis;
bool isTimerON = false;

void activateTimer() {
  isTimerON = true;
  previousMillis = millis();
}

bool timerExpired() {
  if (isTimerON == false) return false;

  if ((unsigned long)(millis() - previousMillis) >= 5000)
    return true;
  return false;
}