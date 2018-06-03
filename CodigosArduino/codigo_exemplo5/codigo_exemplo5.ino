/*Este exemplo utiliza uma biblioteca mais completa do star wars, mas isso limita a programação e possui alguns bugs propositais que não podem ser corrigidos nesse código
 * 
 * Rodolfo C M Schiavi 05/18
 */

#include <StarWarsFull.h>
#include <LiquidCrystal.h>

StarWarsFull  sw;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  sw.inicializa_jogo();
  sw.set_nivel(6);
}

void loop() {

  int leitura = analogRead(A0);
  delay(100);
  
  if(!sw.over){
    if (leitura < 80) {
    /*Botão RIGHT*/
    sw.move_frente();
  }
  else if (leitura < 200) {
    /*Botão UP*/
    sw.move_cima();
  }
  else if (leitura < 400) {
    /*Botão Down*/
    sw.move_baixo();
  }
  else if (leitura < 650) {
    /*Botão Left*/
    sw.move_tras();
  }
  else if (leitura < 800) { 
    /*Botão Select*/
    sw.tiro();
    //sw.criar_enemy();
  }
  sw.atualiza_tela();
  }
  else{
    /*Fazer menu*/
    lcd.clear();
    //lcd.print("ok");
    delay(500);
    sw.over=false;
  }
}
