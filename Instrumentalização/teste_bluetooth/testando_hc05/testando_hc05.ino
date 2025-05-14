#include <SoftwareSerial.h>

SoftwareSerial bluetooth(8, 9);  // RX, TX

void confirmacao() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
  }
}

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);       
  bluetooth.begin(9600);    
  Serial.println("Bluetooth pronto!");
}

void loop() {
  // Monitor Serial (USB)
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 's') {
      confirmacao();
    }
  }

  // Bluetooth (HC-05)
  if (bluetooth.available()) {
    char c = bluetooth.read();
    if (c == 's') {
      confirmacao();
    }
  }
}

