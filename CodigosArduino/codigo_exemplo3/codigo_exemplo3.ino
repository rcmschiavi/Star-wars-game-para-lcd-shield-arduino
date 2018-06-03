/*Exemplo de utilização da biblioteca simples "StarWars", deve ser instalada na pasta libraries do arduino
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



void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  sw.mover_nave(0);
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
    lcd.clear();
    lcd.setCursor(px, 0);
    lcd.write(nave_front0);
    lcd.setCursor(px + 1, 0);
    lcd.write(nave_back0);
  }
  else if (leitura < 400) {
    /*Botão Down*/
    lcd.clear();
    lcd.setCursor(px, 1);
    lcd.write(nave_front0);
    lcd.setCursor(px + 1, 1);
    lcd.write(nave_back0);
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
