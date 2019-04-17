// Programa : Display LCD 16x2 e modulo I2C
// Autor : Arduino e Cia

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

int led  = 3;
int pinoSensor = 4;
int iniciaSensor = 0;
//Variável para calibração do sensor
int calibracao = 45;


 
void setup()
{
 lcd.begin (16,2);
 pinMode(3,OUTPUT);
 ///
    Serial.begin(9600);
    pinMode(pinoSensor,INPUT); //E o sensor uma entrada.
    Serial.print("Calibrando o sensor...");
    for(int i = 0; i < calibracao; i++){
    Serial.print(".");
    }
    Serial.println("Sensor Ativado");
    delay(500);
///
}
 
void loop()
{
    iniciaSensor = digitalRead(pinoSensor);
    Serial.print("Valor do Sensor PIR: "); 
    Serial.println(iniciaSensor);
    
    if (iniciaSensor == 1) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MOVIMENTO");
      digitalWrite(led,HIGH);
      delay(500);
    } else {
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("SEM MOVIMENTO");
      digitalWrite(led,LOW);
      
    } 
  delay(900);

}




