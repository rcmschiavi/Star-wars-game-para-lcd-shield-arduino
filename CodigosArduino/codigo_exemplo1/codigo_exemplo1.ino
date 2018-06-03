/*Código de exemplo inicial para utilização da shield lcd
 * 
 * Rodolfo C M Schiavi 05/2018
 */

#include <LiquidCrystal.h>

/*Fazer um arquivo de cabeçalho com os pinos do lcd para mostrar como criar uma biblioteca, lembrar de criar os keywords*/

LiquidCrystal   lcd(8, 9, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(4, 1);
  lcd.write("Hello World!");
}

void loop() {
  int leitura = analogRead(A0);
  delay(100);
  if (leitura < 80) {
    /*Botão RIGHT*/
    lcd.scrollDisplayRight();
  }
  else if (leitura < 200) {
    /*Botão UP*/
    lcd.clear();
    lcd.setCursor(0, 0); //Desnecessário pois o clear já posiciona
    lcd.write("Hello World!");
  }
  else if (leitura < 400) {
    /*Botão Down*/
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.write("Hello World!");
  }
  else if (leitura < 650) {
    /*Botão Left*/
    lcd.scrollDisplayLeft();
  }
  else if (leitura < 800) { //Verifica se o select está ativo
    lcd.noDisplay();
    delay(1000);
    lcd.display();
  }
}
