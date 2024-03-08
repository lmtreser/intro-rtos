/*  Códigos de ejemplo de los tutoriales de www.luisllamas.es
    Enlace entrada: https://www.luisllamas.es/maquina-de-estados-finitos-arduino/
    Todo el contenido distribuido bajo licencia CCC, salvo indicación expresa
*/

enum State {
  PosicionA,
  PosicionB,
  PosicionC,
  PosicionD
};

enum Input {
  Unknown,
  Reset,
  Forward,
  Backward
};

// Variables globales
State currentState;
Input currentInput;

// Acciones de los estados y condiciones de transiciones
void stateA() {
  if (currentInput == Input::Forward)
    changeState(State::PosicionB);
}

void stateB() {
  if (currentInput == Input::Backward)
    changeState(State::PosicionA);
  if (currentInput == Input::Forward)
    changeState(State::PosicionC);
  if (currentInput == Input::Reset)
    changeState(State::PosicionA);
}

void stateC() {
  if (currentInput == Input::Backward)
    changeState(State::PosicionB);
  if (currentInput == Input::Forward)
    changeState(State::PosicionD);
  if (currentInput == Input::Reset)
    changeState(State::PosicionA);
}

void stateD() {
  if (currentInput == Input::Backward)
    changeState(State::PosicionC);
  if (currentInput == Input::Reset)
    changeState(State::PosicionA);
}

// Salidas asociadas a las transiciones
void outputA() {
  Serial.println("A   B   C   D");
  Serial.println("X            ");
  Serial.println();
}

void outputB() {
  Serial.println("A   B   C   D");
  Serial.println("    X        ");
  Serial.println();
}

void outputC() {
  Serial.println("A   B   C   D");
  Serial.println("        X    ");
  Serial.println();
}

void outputD() {
  Serial.println("A   B   C   D");
  Serial.println("            X");
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  currentState = PosicionA;
  outputA();
}

void loop() {
  readInput();
  updateStateMachine();
}

// Actualiza el estado de la maquina
void updateStateMachine() {
  switch (currentState) {
    case PosicionA: stateA(); break;
    case PosicionB: stateB(); break;
    case PosicionC: stateC(); break;
    case PosicionD: stateD(); break;
  }
}

// Lee la entrada por puerto serie
void readInput() {
  currentInput = Input::Unknown;
  if (Serial.available()) {
    char incomingChar = Serial.read();

    switch (incomingChar) {
      case 'R': currentInput = Input::Reset; break;
      case 'A': currentInput = Input::Backward; break;
      case 'D': currentInput = Input::Forward; break;
      default: break;
    }
  }
}

// Funcion que cambia el estado y dispara las transiciones
void changeState(int newState) {
  currentState = newState;

  switch (currentState) {
    case State::PosicionA: outputA(); break;
    case State::PosicionB: outputB(); break;
    case State::PosicionC: outputC(); break;
    case State::PosicionD: outputD(); break;
    default: break;
  }
}