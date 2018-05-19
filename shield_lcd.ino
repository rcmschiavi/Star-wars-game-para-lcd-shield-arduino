
#include <LiquidCrystal.h> // Inclui biblioteca "LiquidCristal.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // Define Pinos do Display

//Caracteres especiais criados para as naves
byte back[8] = {
  B00000,
  B00011,
  B01111,
  B11111,
  B11111,
  B01111,
  B00011,
  B00000,
};
byte front[8] = {
  B00000,
  B11100,
  B11110,
  B11000,
  B11000,
  B11110,
  B11100,
  B00000,
};

byte enemy[8] {
  B00000,
  B00000,
  B11111,
  B00110,
  B00110,
  B11111,
  B00000,
  B00000,
};

int teste[2] {back, front};
int x_nave = 0;
int y_tiro = 0;
int p_tiro = x_nave + 1;
int p_enemy = 15;
int inc_p_enemy = 1;
int y_nave = 0;
bool atirando = false;

void setup() {
  //Adiciona os caracteres especiais na memória do display
  lcd.createChar(0, teste[0]);
  lcd.createChar(1, teste[1]);
  lcd.createChar(6, enemy);

  lcd.begin(16, 2); // Estabelece caracteres do display
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.write("Star Wars Game");
  lcd.setCursor(7, 1);
  lcd.write(byte(0)); //Mostra o caracter especial alocado na posição zero
  lcd.setCursor(8, 1);
  lcd.write(byte(1));
  delay(5000);
  nave(); //Chama a função que lida com a posição da millenium falcon
  HandleDisplay(0); //Chama a função que atualiza o display
}

void loop() {
  int x = analogRead (0); //Lê os botões
  /*Os botões funcionam como um potenciômetro, cada um tem uma faixa de leitura na entrada analógica*/
  if (x < 80) { // Botão Left
    if (x_nave < 14)
      x_nave++;
  }
  else if (x < 200) { //Botão Up
    if (y_nave > 0)
      y_nave--; //Decrementa a posição da nave
    nave(); //Chama a função que lida com a posição da nave
  }

  else if (x < 400) { //Botão Down
    if (y_nave < 8)
      y_nave++; //Incrementa a posição
    nave();
  }
  else if (x < 600) { //Botão Right
    if (x_nave > 0)
      x_nave--;
  }
  else if (x < 800) { //Botão Select
    if (!atirando) { //Verifica se já não há outro disparo acontecendo
      nave();
      p_tiro = x_nave + 2;
      atirando = true;
      y_tiro = y_nave; //Salva a posição do tiro para comparações como acertar o inimigo
    }
  }
  if (atirando) {
    p_tiro++; //Incrementa a posição do tiro
    if (p_tiro > 15) { //Verifica se o tiro chegou ao final da tela
      p_tiro = -1;
      atirando = false;
    }
  }
  HandleDisplay(0);
  if ((p_enemy == x_nave + 1) && (y_nave < 5)) { //Verifica se a nave bateu no inimigo para finalizar o jogo
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.write("Se fudeu!");
    x_nave = 0;
    delay(1000);
  }
  if ((p_tiro == p_enemy) && (y_tiro < 4)) { //Verifica se o tiro da nave acertou o inimigo
    explosao(); //Chama a função que substitui a nave por uma explosão
    p_enemy = random(x_nave+5,15); //Reseta o inimigo numa posição aleatória longe da nave
    p_tiro = 16;
  }

}
//Atualiza a tela
void HandleDisplay(int x) {
  lcd.clear();
  lcd.setCursor(x_nave, 0);
  lcd.write(byte(0));
  lcd.setCursor(x_nave + 1, 0);
  lcd.write(byte(2));
  lcd.setCursor(x_nave, 1);
  lcd.write(byte(1));
  lcd.setCursor(x_nave + 1, 1);
  lcd.write(byte(3));
  if (atirando)
    tiros();
  if (p_enemy > 0)
    ship_enemy();
  delay(100);
}
void nave() {
  byte part_nave[8] = {B00000, B00011, B01111, B11111, B11111, B01111, B00011, B00000};
  byte part2_nave[8] = {B00000, B00011, B01111, B11111, B11111, B01111, B00011, B00000};
  byte part3_nave[8] =  {B00000, B11100, B11110, B11000, B11000, B11110, B11100, B00000};
  byte part4_nave[8] =  {B00000, B11100, B11110, B11000, B11000, B11110, B11100, B00000};
  byte shoot1[8] =       {B00000, B00000, B11100, B00000, B00000, B11100, B00000, B00000};
  byte shoot2[8] =       {B00000, B00000, B11100, B00000, B00000, B11100, B00000, B00000};

//Movimenta os bytes para mover a nave e os tiros entre os pontos
  for (int x = 0; x < y_nave; x++) {
    for (int x = 7; x > 0; x--) {
      part_nave[x] = part_nave[x - 1];
      part3_nave[x] = part3_nave[x - 1];
      shoot1[x] = shoot1[x - 1];
    }
  }
  for (int x = 0; x < 8 - y_nave; x++) {
    for (int x = 0; x < 7; x++) {
      part2_nave[x] = part2_nave[x + 1];
      part4_nave[x] = part4_nave[x + 1];
      shoot2[x] = shoot2[x + 1];

    }
  }


  lcd.createChar(0, part_nave);
  lcd.createChar(1, part2_nave);
  lcd.createChar(2, part3_nave);
  lcd.createChar(3, part4_nave);
  if (!atirando) {
    lcd.createChar(4, shoot1);
    lcd.createChar(5, shoot2);
    HandleDisplay(0);
  }
}
void tiros() {
  lcd.setCursor(p_tiro, 0);
  lcd.write(byte(4));
  lcd.setCursor(p_tiro, 1);
  lcd.write(byte(5));
}
void ship_enemy() {
  lcd.setCursor(p_enemy, 0);
  if (inc_p_enemy % 20 == 0) {
    p_enemy--;
    inc_p_enemy = 1;
  }
  inc_p_enemy++;
  lcd.write(byte(6));
}
void explosao() {
  lcd.setCursor(p_enemy, 0);
  lcd.write("o");
  delay(300);
}

