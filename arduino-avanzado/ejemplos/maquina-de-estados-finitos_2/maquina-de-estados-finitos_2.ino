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

const void outputA() {
  Serial.println("A   B   C   D");
  Serial.println("X            ");
  Serial.println();
}

const void outputB() {
  Serial.println("A   B   C   D");
  Serial.println("    X        ");
  Serial.println();
}

const void outputC() {
  Serial.println("A   B   C   D");
  Serial.println("        X    ");
  Serial.println();
}

const void outputD() {
  Serial.println("A   B   C   D");
  Serial.println("            X");
  Serial.println();
}

typedef void (*const StateFunc)();
State currentState;
Input currentInput;

const StateFunc transitionOutput[] PROGMEM = { outputA, outputB, outputC, outputD };

const byte stateChange[4][4] PROGMEM = {
  { PosicionA, PosicionA, PosicionB, PosicionA },
  { PosicionB, PosicionA, PosicionC, PosicionA },
  { PosicionC, PosicionA, PosicionD, PosicionB },
  { PosicionD, PosicionA, PosicionD, PosicionC },
};

void setup() {
  Serial.begin(9600);
  currentState = PosicionA;
  outputA();
}

void loop() {
  readInput();
  updateStateMachine();
}

void updateStateMachine() {
  State newState = (State)pgm_read_byte(&stateChange[currentState][currentInput]);
  if (currentState == newState) return;

  currentState = newState;

  StateFunc pStateFunc = (StateFunc)pgm_read_ptr(&transitionOutput[currentState]);
  pStateFunc();
}

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