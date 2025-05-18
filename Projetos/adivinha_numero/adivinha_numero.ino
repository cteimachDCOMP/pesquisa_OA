#include <TimerOne.h>

#define DISP_UNIDADE 10
#define DISP_DEZENA 11
#define DISP_CENTENA 12
#define DISP_MILHAR A0
#define DISP_DEZMILHAR A1

int num = 0;
int valor_unidade = 0, valor_dezena = 0, valor_centena = 0, valor_milhar = 0, valor_dezenaMilhar = 0;
int alterna = 1;

int lista1[8] = {1,3,5,7,9,11,13,15};
int lista2[8] = {2,3,6,7,10,11,14,15};
int lista3[8] = {4,5,6,7,12,13,14,15};
int lista4[8] = {8,9,10,11,12,13,14,15};

char confirmacao = '\0';

int disposicao_pinos[6] = {2, 3, 4, 5, 6, 7};

int digitos[2][6] = {
  { 1, 1, 1, 1, 1, 1 },  // 0
  { 0, 1, 1, 0, 0, 0 }   // 1
};

void imprimeNumero(int n) {
  for (int i = 0; i < 6; i++) {
    digitalWrite(disposicao_pinos[i], digitos[n][i]);
  }
}

void imprimeLista(int lista[]){
  Serial.print("---> ");
  for (int i = 0; i < 8; i++){
    Serial.print(lista[i]);
    Serial.print(" ");
  }
  Serial.println("");
}

char aguardaRespostaBinaria(){
  char resposta = '\0';

  while (true){
    if(Serial.available()){
      resposta = Serial.read();

      if (resposta == '\n' || resposta == '\r' || resposta == ' ') {
        continue;
      }

      if (resposta == '1' || resposta == '0'){
        while (Serial.available()) Serial.read();
        return resposta;
      }
      else{
        Serial.println("Entrada inválida. Digite apenas 1 ou 0:");
        while (Serial.available()) Serial.read();
      }
    }
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

  for (int i = 0; i < 6; i++) {
    pinMode(disposicao_pinos[i], OUTPUT);
  }

  Timer1.initialize(4000);
  Timer1.attachInterrupt(trocarDisplay);

  Serial.begin(9600);
}

void loop() {
  Serial.println("Bem vindo(a) ao adivinhador binário!");
  delay(500);
  Serial.println("Pense em um número de 0 a 15, mas não me diga rs");
  delay(1500);
  Serial.println("Digite 1 quando estiver pronto(a)");
  while (aguardaRespostaBinaria() != '1') aguardaRespostaBinaria();

  Serial.println("A partir de agora eu farei algumas perguntas, digite 1 para confirmar ou 0 para negar");
  
  Serial.print("Seu número está aqui? ");
  imprimeLista(lista1);
  confirmacao = aguardaRespostaBinaria();
  if (confirmacao == '1'){
    valor_unidade = 1;
    num = 1;
  }

  Serial.print("Seu número está aqui? ");
  imprimeLista(lista2);
  confirmacao = aguardaRespostaBinaria();
  if (confirmacao == '1'){
    valor_dezena = 1;
    num = num + 2;
  }

  Serial.print("Seu número está aqui? ");
  imprimeLista(lista3);
  confirmacao = aguardaRespostaBinaria();
  if (confirmacao == '1'){
    valor_centena = 1;
    num = num + 4;
  }

  Serial.print("Seu número está aqui? ");
  imprimeLista(lista4);
  confirmacao = aguardaRespostaBinaria();
  if (confirmacao == '1'){
    valor_milhar = 1;
    num = num + 8;
  }

  Serial.print("O número que você escolheu é... ");
  delay(1000);
  Serial.print(num);
  Serial.println(" !!!");

  Serial.println("Se quiser tentar outra vez, basta digitar 1 novamente :D");
  confirmacao = aguardaRespostaBinaria();
  if (confirmacao == '1'){
    valor_unidade = 0;
    valor_dezena = 0;
    valor_centena = 0;
    valor_milhar = 0;
    num = 0;
  }
}
