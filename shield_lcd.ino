
#include <LiquidCrystal.h> // Inclui biblioteca "LiquidCristal.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // Define Pinos do Display

//Caracteres especiais criados para as naves
const byte const_millenium_back[8] = {B00000, B00011, B01111, B11111, B11111, B01111, B00011, B00000};
const byte const_millenium_front[8] = {B00000, B11100, B11110, B11000, B11000, B11110, B11100, B00000};
const byte enemy[8] = {B00000, B00000, B11111, B00110, B00110, B11111, B00000, B00000};
const byte const_shoot[8] = {B00000, B00000, B11100, B00000, B00000, B11100, B00000, B00000};
byte millenium_back[8] = {};
byte millenium_front[8] = {};
byte shoot1[8] = {};
byte shoot2[8] = {};


int millenium[3] = {const_millenium_back, const_millenium_front, const_shoot};


int x_nave = 0;
int y_tiro = 0;
int p_tiro = x_nave + 1;
int p_enemy1[5] = {8, 13, 0, 0, 0};
int num_inimigos1 = 1;
int p_enemy2[5] = {7, 11, 0, 0, 0};
int num_inimigos2 = 2;
int inc_p_enemy = 2;
int y_nave = 0;
bool atirando = false;
int vel_inimigo = 20;

void setup() {
  //Adiciona os caracteres especiais na memória do display
  lcd.createChar(0, millenium[0]);
  lcd.createChar(1, millenium[1]);
  lcd.createChar(6, enemy);
  Serial.begin(9600);
  lcd.begin(16, 2); // Estabelece caracteres do display
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.write("Star Wars Game");
  lcd.setCursor(7, 1);
  lcd.write(byte(0)); //Mostra o caracter especial alocado na posição zero
  lcd.setCursor(8, 1);
  lcd.write(byte(1));
  delay(000);
  mover_nave(); //Chama a função que lida com a posição da millenium falcon
  HandleDisplay(0); //Chama a função que atualiza o display
}

void loop() {
  int x = analogRead (0); //Lê os botões
  /*Os botões funcionam como um potenciômetro, cada um tem uma faixa de leitura na entrada analógica*/
  if (x < 80) { // Botão Left
    if (x_nave < p_enemy1[0])
      x_nave++;
  }
  else if (x < 200) { //Botão Up
    if (y_nave > 0)
      y_nave--; //Decrementa a posição da nave
    mover_nave(); //Chama a função que lida com a posição da nave
  }

  else if (x < 400) { //Botão Down
    if (y_nave < 8)
      y_nave++; //Incrementa a posição
    mover_nave();
  }
  else if (x < 600) { //Botão Right
    if (x_nave > 0)
      x_nave--;
  }
  else if (x < 800) { //Botão Select
    if (!atirando) { //Verifica se já não há outro disparo acontecendo
      mover_nave();
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
    else {
      if (y_tiro < 4) {
        if (p_tiro == p_enemy1[0]) { //Verifica se o tiro da nave acertou o inimigo
          explosao(0); //Chama a função que substitui a nave por uma explosão
          p_tiro = 16;
        }
      }
      else if (y_tiro > 5) {
        if (p_tiro == p_enemy2[0]) { //Verifica se o tiro da nave acertou o inimigo
          explosao(1); //Chama a função que substitui a nave por uma explosão
          p_tiro = 16;
        }
      }
    }
  }

  if ((p_enemy1[0] == x_nave + 1) && (y_nave < 5)) { //Verifica se a nave bateu no inimigo para finalizar o jogo
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.write("Se fudeu!");
    x_nave = 0;
    delay(1000);
  }

  HandleDisplay(0);
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
  if (p_enemy1[0] > 0)
    ship_enemy(0);
  delay(100);
}
void mover_objeto(byte *r, int p_y, int mem) {
  byte char_sup[8] = {};
  byte char_inf[8] = {};

  for (int z = 0; z < 8; z++) {
    char_sup[z] = *r;
    char_inf[z] = *r;
    r++;
  }
  //Movimenta os bytes para mover a nave e os tiros entre os pontos
  for (int x = 0; x < p_y; x++) {
    for (int x = 7; x > 0; x--) {
      char_sup[x] = char_sup[x - 1];
    }
  }
  for (int x = 0; x < 8 - p_y; x++) {
    for (int x = 0; x < 7; x++) {
      char_inf[x] = char_inf[x + 1];
    }
  }
  lcd.createChar(mem, char_sup);
  lcd.createChar(mem + 1, char_inf);
}
void tiros() {
  lcd.setCursor(p_tiro, 0);
  lcd.write(byte(4));
  lcd.setCursor(p_tiro, 1);
  lcd.write(byte(5));
}
void criar_inimigo(int y) {
  if (y == 0) {
    p_enemy1[num_inimigos1 - 1] = random(p_enemy1[0], 15); //Reseta o inimigo numa posição aleatória longe da nave
    num_inimigos1++;
  }
  else {
    p_enemy2[num_inimigos2 - 1] = random(p_enemy2[0], 15); //Reseta o inimigo numa posição aleatória longe da nave
    num_inimigos2++;
  }
}
void ship_enemy(int qnt) {
  if (num_inimigos1 + num_inimigos2 > 0){
  if (num_inimigos1 > 0) {
      lcd.setCursor(p_enemy1[0], 0);
      if (inc_p_enemy % 20 == 0) {
        p_enemy1[0]--;
      }
      lcd.write(byte(6));
    }
    if (num_inimigos2 > 0) {
      for (int x = 0; x < num_inimigos2; x++) {
        lcd.setCursor(p_enemy2[x], 1);
        if (inc_p_enemy % vel_inimigo == 0) {
          p_enemy2[x]--;
          inc_p_enemy = 1;
        }
        lcd.write(byte(6));
      }
    }
    if (inc_p_enemy == vel_inimigo)
      inc_p_enemy = 1;
    inc_p_enemy++;
  }
}
void explosao(int y) {
  if (y == 0)
    lcd.setCursor(p_enemy1[0], y);
  else
    lcd.setCursor(p_enemy2[0], y);
  lcd.write("o");
  criar_inimigo(y);
  if (y == 0) {
     for (int x = 0; x < 5; x++) {
       p_enemy1[x] = p_enemy1[x + 1];
      }
    num_inimigos1--;
  }
  else {
          for (int x = 0; x < 5; x++) {
        p_enemy2[x] = p_enemy2[x + 1];
      }
    num_inimigos2--;
  }
  Serial.println(p_enemy1[0]);
  delay(300);
}
void mover_nave() {
  mover_objeto(const_millenium_back, y_nave, 0);
  mover_objeto(const_millenium_front, y_nave, 2);
  if (!atirando) {
    mover_objeto(const_shoot, y_nave, 4);
    HandleDisplay(0);
  }
}
