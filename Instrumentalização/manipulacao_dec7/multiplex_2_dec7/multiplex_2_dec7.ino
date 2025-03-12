// Multiplexação de 2 Decodificadores de 7 segmentos
#include <TimerOne.h>

#define DISP_UNIDADE 10
#define DISP_DEZENA 11

int num = 0, valor_unidade = 0, valor_dezena = 0;
int disposicao_pinos[8] = { 2, 3, 4, 5, 6, 7, 8, 9 };

int digitos[16][8] = {
  { 1, 1, 1, 1, 1, 1, 0, 0 },  // 0
  { 0, 1, 1, 0, 0, 0, 0, 0 },  // 1
  { 1, 1, 0, 1, 1, 0, 1, 0 },  // 2
  { 1, 1, 1, 1, 0, 0, 1, 0 },  // 3
  { 0, 1, 1, 0, 0, 1, 1, 0 },  // 4
  { 1, 0, 1, 1, 0, 1, 1, 0 },  // 5
  { 1, 0, 1, 1, 1, 1, 1, 0 },  // 6
  { 1, 1, 1, 0, 0, 0, 0, 0 },  // 7
  { 1, 1, 1, 1, 1, 1, 1, 0 },  // 8
  { 1, 1, 1, 0, 0, 1, 1, 0 },  // 9
  { 1, 1, 1, 0, 1, 1, 1, 0 },  // A
  { 0, 0, 1, 1, 1, 1, 1, 0 },  // B
  { 1, 0, 0, 1, 1, 1, 0, 0 },  // C
  { 0, 1, 1, 1, 1, 0, 1, 0 },  // D
  { 1, 0, 0, 1, 1, 1, 1, 0 },  // E
  { 1, 0, 0, 0, 1, 1, 1, 0 }   // F
};

void imprimeNumero(int n) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(disposicao_pinos[i], digitos[n][i]);
  }
}

void trocarDisplay() {
  static bool alternar = false;

  digitalWrite(DISP_DEZENA, LOW);
  digitalWrite(DISP_UNIDADE, LOW);

  if (alternar) {
    digitalWrite(DISP_UNIDADE, HIGH);
    imprimeNumero(valor_dezena);
  } else {
    digitalWrite(DISP_DEZENA, HIGH);
    imprimeNumero(valor_unidade);
  }

  alternar = !alternar;
}

void setup() {
  pinMode(DISP_UNIDADE, OUTPUT);
  pinMode(DISP_DEZENA, OUTPUT);

  for (int i = 0; i < 8; i++) {
    pinMode(disposicao_pinos[i], OUTPUT);
  }

  Timer1.initialize(5000);
  Timer1.attachInterrupt(trocarDisplay);
}

void loop() {
  valor_unidade = num % 16;
  valor_dezena = num / 16;

  num++;
  if (num > 255) {
    num = 0;
  }

  delay(100);
}
