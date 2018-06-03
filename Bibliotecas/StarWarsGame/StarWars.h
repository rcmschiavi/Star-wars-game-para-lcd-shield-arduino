#include "Arduino.h"
#include "LiquidCrystal.h"


class StarWars{
  public:
    void mover_nave(int y);
    bool atirando=false;
  private:
    byte const_millenium_back[8] = {B00000, B00011, B01111, B11111, B11111, B01111, B00011, B00000};
    byte const_millenium_front[8] = {B00000, B11100, B11110, B11000, B11000, B11110, B11100, B00000};
    void mover_objeto(byte *r, int p_y, int mem);
};
