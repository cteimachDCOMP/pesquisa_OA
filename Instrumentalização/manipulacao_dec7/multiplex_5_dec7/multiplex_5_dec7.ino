#include <TimerOne.h>

#define DISP_UNIDADE 10
#define DISP_DEZENA 11
#define DISP_CENTENA 12
#define DISP_MILHAR A0
#define DISP_DEZMILHAR A1

int num = 0;
int valor_unidade = 0, valor_dezena = 0, valor_centena = 0, valor_milhar = 0, valor_dezenaMilhar = 0;
int alterna = 1;
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
  digitalWrite(DISP_UNIDADE, HIGH);
  digitalWrite(DISP_DEZENA, HIGH);
  digitalWrite(DISP_CENTENA, HIGH);
  digitalWrite(DISP_MILHAR, HIGH);
  digitalWrite(DISP_DEZMILHAR, HIGH);

  switch (alterna) {
    case 1:
      digitalWrite(DISP_UNIDADE, LOW);
      imprimeNumero(valor_unidade);
      break;

    case 2:
      digitalWrite(DISP_DEZENA, LOW);
      imprimeNumero(valor_dezena);
      break;

    case 3:
      digitalWrite(DISP_CENTENA, LOW);
      imprimeNumero(valor_centena);
      
      break;

    case 4:
      digitalWrite(DISP_MILHAR, LOW);
      imprimeNumero(valor_milhar);
      
      break;

    case 5:
      digitalWrite(DISP_DEZMILHAR, LOW);
      imprimeNumero(valor_dezenaMilhar);
      
      break;
  }

  alterna++;
  if (alterna > 5) {
    alterna = 1;
  }
}

void setup() {
  pinMode(DISP_UNIDADE, OUTPUT);
  pinMode(DISP_DEZENA, OUTPUT);
  pinMode(DISP_CENTENA, OUTPUT);
  pinMode(DISP_MILHAR, OUTPUT);
  pinMode(DISP_DEZMILHAR, OUTPUT);

  for (int i = 0; i < 8; i++) {
    pinMode(disposicao_pinos[i], OUTPUT);
  }

  Timer1.initialize(4000);
  Timer1.attachInterrupt(trocarDisplay);

  Serial.begin(9600);
}

void loop() {
  valor_unidade = num % 16;
  valor_dezena = (num / 16) % 16;
  valor_centena = (num / 256) % 16;
  valor_milhar = (num / 4096) % 16;
  valor_dezenaMilhar = (num / 65536) % 16;

  Serial.print(valor_dezenaMilhar);
  Serial.print(" || ");
  Serial.print(valor_milhar);
  Serial.print(" || ");
  Serial.print(valor_centena);
  Serial.print(" || ");
  Serial.print(valor_dezena);
  Serial.print(" || ");
  Serial.print(valor_unidade);
  Serial.println("");

  num++;

  if (num > 1048575) {
    num = 0;
  }

  delay(100);
}
