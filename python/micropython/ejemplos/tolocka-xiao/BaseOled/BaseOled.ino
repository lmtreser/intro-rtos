

void Beep (int bips) {
 
 for (int x=0; x<bips; x++) {
    digitalWrite (D3, HIGH);
    delay (1);
    digitalWrite (D3, LOW);
    delay (1);

 }

}

void setup() {
  Serial.begin(115200);

  pinMode (D3, OUTPUT);

}

void loop() {

  Beep (100);
  delay (1000);

}
