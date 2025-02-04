//Contagem 0----9

int num = 0;

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
  { 1, 0, 0, 0, 1, 1, 1, 0 },  // F

};

void imprimeNumero(int n) {
  for (int i = 0; i <= 7; i++) {
    digitalWrite(disposicao_pinos[i], digitos[n][i]);
  }
}

void setup() {

  for (int i = 0; i <= 7; i++) {
    pinMode(disposicao_pinos[i], OUTPUT);
  }
}

void loop() {

  imprimeNumero(num);
  delay(1000);
  num++;

  if (num > 15) {
    num = 0;
  }
}