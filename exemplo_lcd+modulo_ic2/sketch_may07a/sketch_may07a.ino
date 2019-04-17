// Programa : Display LCD 16x2 e modulo I2C
// Autor : Arduino e Cia

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);
 
void setup()
{
 lcd.begin (16,2);
}
 
void loop()
{
  //lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("TESTE");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ARDUINO");
  delay(1000);
 
}
