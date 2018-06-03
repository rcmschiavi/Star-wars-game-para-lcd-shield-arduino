#include "StarWarsFull.h"

LiquidCrystal display(8, 9, 4, 5, 6, 7);

void StarWarsFull::inicializa_jogo(){
  display.begin(16,2);
  display.clear();
  display.setCursor(1,0);
  display.write("Star Wars Game");
  display.createChar(6, enemy);
  mover_nave();
  delay(1000);
}
void StarWarsFull::atualiza_tela(){
  if(atirando){
    p_tiro++; //Incrementa a posição do tiro
    HandleDisplay();
    if (p_tiro > 15) { //Verifica se o tiro chegou ao final da tela
      p_tiro = -1; //Oculta ele da tela
      atirando = false;
    }
    else {
      if (y_tiro <4) {
        if (p_tiro == p_enemy1[0]) { //Verifica se o tiro da nave acertou o inimigo
          explosao(0); //Chama a função que substitui a nave por uma explosão
          p_tiro = 16;
          atirando = false;
        }
      }
      else if (y_tiro>5) {
        if (p_tiro == p_enemy2[0]) { //Verifica se o tiro da nave acertou o inimigo
          explosao(1); //Chama a função que substitui a nave por uma explosão
          p_tiro = 16;
          atirando = false;
        }
      }
    }
  }
  if(num_enemies<nivel){
    criar_enemy();
  }
  if(num_enemies>0){
    HandleDisplay();
  }
  game_over();
}
void StarWarsFull::move_cima(){
  if(y_nave>0){
    y_nave--;
    mover_nave();
  }
}
void StarWarsFull::move_baixo(){
  if(y_nave<10){
    y_nave++;
    mover_nave();
  }
}
void StarWarsFull::move_frente(){
  if(x_nave<16){
    x_nave++;
    HandleDisplay();
  }
}
void StarWarsFull::move_tras(){
  if(x_nave>0){
    x_nave--;
    HandleDisplay();
  }
}
void StarWarsFull::criar_enemy(){
  if(num_enemies==0){
    p_enemy1[num_enemies1] = 15;
    num_enemies1++;
  }
  else if(num_enemies1<=num_enemies2){
    p_enemy1[num_enemies1] = 16; //cria o inimigo numa posição aleatória longe da nave
    num_enemies1++;
  }
  else{
    p_enemy2[num_enemies2] = 15; //cria o inimigo numa posição aleatória longe da nave
    num_enemies2++;
  }
  num_enemies=num_enemies1+num_enemies2;
  HandleDisplay();
}

void StarWarsFull::mover_nave(){
  mover_objeto(const_millenium_back, y_nave, 0);
  mover_objeto(const_millenium_front, y_nave, 2);
  if (!atirando) {
    mover_objeto(const_shoot, y_nave, 4);
    y_tiro=y_nave;
  }
//  HandleDisplay();
}
void StarWarsFull::mover_objeto(byte *r, int p_y, int mem) {
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
  display.createChar(mem, char_sup);
  display.createChar(mem + 1, char_inf);
}
void StarWarsFull::HandleDisplay() {
  display.clear();
  display.setCursor(x_nave, 0);
  display.write(byte(0));
  display.setCursor(x_nave + 1, 0);
  display.write(byte(2));
  display.setCursor(x_nave, 1);
  display.write(byte(1));
  display.setCursor(x_nave + 1, 1);
  display.write(byte(3));
  if (atirando){
    display.setCursor(p_tiro, 0);
    display.write(byte(4));
    display.setCursor(p_tiro, 1);
    display.write(byte(5));
  }
  ship_enemy();
  delay(100);
}
void StarWarsFull::tiro(){
  if(!atirando){
    p_tiro=x_nave + 2;
    mover_nave();
    atirando=true;
    HandleDisplay();
  }
}
void StarWarsFull::ship_enemy() {

    if(num_enemies>0){
      if(num_enemies1>0){
        for(int x=0;x<num_enemies1;x++){
          display.setCursor(p_enemy1[x],0);
          display.write(byte(6));
          if(inc_p_enemy==vel_inimigo)
            p_enemy1[x]--;
        }
        if(num_enemies2>0){
          for(int x=0;x<num_enemies2;x++){
            display.setCursor(p_enemy2[x],1);
            display.write(byte(6));
            if(inc_p_enemy==vel_inimigo)
              p_enemy2[x]--;
          }
        }
      }
      inc_p_enemy++;
    }
  if(inc_p_enemy==vel_inimigo+1){
    inc_p_enemy=0;
  }
}
void StarWarsFull::explosao(int y) {
  if (y == 0)
    display.setCursor(p_enemy1[0], y);
  else
    display.setCursor(p_enemy2[0], y);
  display.write("+1");
  if (y == 0) {
     for (int x = 0; x < num_enemies1; x++) {
       p_enemy1[x] = p_enemy1[x + 1];
      }
    num_enemies1--;
  }
  else {
          for (int x = 0; x <num_enemies2; x++) {
        p_enemy2[x] = p_enemy2[x + 1];
      }
    num_enemies2--;
  }
  num_enemies=num_enemies1+num_enemies2;
  score++;
  delay(300);
  print_score();
}
void StarWarsFull::print_score(){
  display.clear();
  display.setCursor(10,0);
  display.print(score);
  display.write(" ptns");
  delay(500);
}

void StarWarsFull::set_nivel(int x){
  if(x>nivel_max)
   nivel=nivel_max;
  nivel=x;
}
void StarWarsFull::game_over(){
  if(y_nave<4){
    for(int x=0;x<num_enemies1;x++){
      if(x_nave+1==p_enemy1[x]){
        reset_game();
        over=true;
      }
    }
  }
  else{
    for(int x=0;x<num_enemies2;x++){
      if(x_nave+1==p_enemy2[x]){
        reset_game();
        over=true;
      }
    }
  }
  if((p_enemy1[0]<=0)||(p_enemy2[0]<=0)){
    reset_game();
    over=true;
  }
}
void StarWarsFull::reset_game(){
  display.clear();
  display.print("Game Over");
  display.setCursor(0,1);
  display.print("Score: ");
  display.print(score);
  num_enemies = 0;
  p_enemy1[0] = 16;
  num_enemies1 = 0;
  p_enemy2[0] =16;
  num_enemies2 = 0;
  inc_p_enemy = 2;
  y_nave = 0;
  x_nave = 0;
  y_tiro = 0;
  score=0;
  delay(500);
}
