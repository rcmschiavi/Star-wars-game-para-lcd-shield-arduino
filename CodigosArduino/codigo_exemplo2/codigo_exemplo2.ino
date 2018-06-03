/*Código que cria um caracter e salva na memória do display para manipula-lo na tela
 * 
 * Rodolfo C M schiavi 05/18
 */
#include <LiquidCrystal.h>

/*Fazer um arquivo de cabeçalho com os pinos do lcd para mostrar como criar uma biblioteca, lembrar de criar os keywords*/

LiquidCrystal   lcd(8, 9, 4, 5, 6, 7);

byte bender[8] = {B00100, B01110, B11111, B10101, B11111, B10001, B10001, B11111};
int px = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, bender);
  lcd.clear();
  lcd.setCursor(px, 0);
  lcd.write(byte(0));
}

void loop() {
  int leitura = analogRead(A0);
  delay(100);
  if (leitura < 80) {
    /*Botão RIGHT*/
    lcd.scrollDisplayRight();
    if (px < 16)
      px++;
  }
  else if (leitura < 200) {
    /*Botão UP*/
    lcd.clear();
    lcd.setCursor(px, 0); //Desnecessário pois o clear já posiciona
    lcd.write(byte(0));
  }
  else if (leitura < 400) {
    /*Botão Down*/
    lcd.clear();
    lcd.setCursor(px, 1);
    lcd.write(byte(0));
  }
  else if (leitura < 650) {
    /*Botão Left*/
    lcd.scrollDisplayLeft();
    if (px > 0)
      px--;
  }
  else if (leitura < 800) { //Verifica se o select está ativo
    lcd.noDisplay();
    delay(1000);
    lcd.display();
  }
}
