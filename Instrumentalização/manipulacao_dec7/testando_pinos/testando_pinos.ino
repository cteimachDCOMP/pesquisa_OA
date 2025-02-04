// Testando pinagem


void setup() {

  for (int i = 2; i <= 9; i++){
    pinMode(i, OUTPUT);
  }

}

void loop() {

  for (int i = 2; i <= 9; i++){
    digitalWrite(i, 1);
    delay(500);
    digitalWrite(i, 0);
    delay(500);
  }

}
