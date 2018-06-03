/*Aprimoramento do exemplo 3, com utilização de uma função para deixar o código mais limpo
 * 
 * Rodolfo C M Schiavi 05/18
 */
 
#include <LiquidCrystal.h>
#include <StarWars.h>

#define nave_front0 byte(0)
#define nave_back0 byte(2)
#define nave_front1 byte(1)
#define nave_back1 byte(3)

StarWars  sw;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int px = 0;
int py = 0;


void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  sw.mover_nave(py);
  lcd.setCursor(px, 0);
  lcd.write(nave_front0);
  lcd.setCursor(px + 1, 0);
  lcd.write(nave_back0);
  lcd.setCursor(px, 1);
  lcd.write(nave_front1);
  lcd.setCursor(px + 1, 1);
  lcd.write(nave_back1);
}

void loop() {
  int leitura = analogRead(A0);
  delay(100);
  if (leitura < 80) {
    /*Botão RIGHT*/
    if (px < 14) {
      lcd.scrollDisplayRight();
      px++;
    }
  }
  else if (leitura < 200) {
    /*Botão UP*/
    if(py>0){
      py--;
      handle_lcd();
    }
  }
  else if (leitura < 400) {
    /*Botão Down*/
    if(py<10){
      py++;
      handle_lcd();
    }
  }
  else if (leitura < 650) {
    /*Botão Left*/
    if (px > 0) {
      lcd.scrollDisplayLeft();
      px--;
    }
  }
  else if (leitura < 800) { //Verifica se o select está ativo
    lcd.noDisplay();
    delay(1000);
    lcd.display();
  }
}

void handle_lcd(){
  /* Função que lida com a movimentação da nave no display*/
  lcd.clear();
  sw.mover_nave(py);
  lcd.setCursor(px, 0);
  lcd.write(nave_front0);
  lcd.setCursor(px + 1, 0);
  lcd.write(nave_back0);
  lcd.setCursor(px, 1);
  lcd.write(nave_front1);
  lcd.setCursor(px + 1, 1);
  lcd.write(nave_back1);
}

