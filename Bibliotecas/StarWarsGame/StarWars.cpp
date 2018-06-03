#include "StarWars.h"

LiquidCrystal lcd2(8, 9, 4, 5, 6, 7);

void StarWars::mover_nave(int y){
  mover_objeto(const_millenium_back, y, 0);
  mover_objeto(const_millenium_front, y, 2);
}

void StarWars::mover_objeto(byte *r, int p_y, int mem) {
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
  lcd2.createChar(mem, char_sup);
  lcd2.createChar(mem + 1, char_inf);
}
