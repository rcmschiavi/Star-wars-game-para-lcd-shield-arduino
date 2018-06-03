#include "Arduino.h"
#include "LiquidCrystal.h"


class StarWarsFull{
  public:
    void inicializa_jogo();
    void atualiza_tela();
    void move_cima();
    void move_baixo();
    void move_frente();
    void move_tras();
    void criar_enemy();
    void tiro();
    void set_nivel(int x);
    int get_score(){return score;};
    bool over = true;
    int vel_inimigo = 10;
  private:
    void mover_nave();
    void mover_objeto(byte *r, int p_y, int mem);
    void HandleDisplay();
    void ship_enemy();
    void explosao(int y);
    void print_score();
    void reset_game();
    void game_over();
    byte const_millenium_back[8] = {B00000, B00011, B01111, B11111, B11111, B01111, B00011, B00000};
    byte const_millenium_front[8] = {B00000, B11100, B11110, B11000, B11000, B11110, B11100, B00000};
    const byte enemy[8] = {B00000, B00000, B11111, B00110, B00110, B11111, B00000, B00000};
    const byte const_shoot[8] = {B00000, B00000, B11100, B00000, B00000, B11100, B00000, B00000};
    int num_enemies = 0;
    int p_enemy1[3] = {16, 0, 0};
    int num_enemies1 = 0;
    int p_enemy2[3] = {16, 0, 0};
    int num_enemies2 = 0;
    int inc_p_enemy = 2;
    int y_nave = 0;
    int x_nave = 0;
    int y_tiro = 0;
    int p_tiro = 1;
    int nivel = 2;
    int nivel_max=6;
    bool atirando=false;
    int score=0;
};
