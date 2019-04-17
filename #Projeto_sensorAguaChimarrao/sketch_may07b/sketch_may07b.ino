#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

// Porta do pino de sinal do DS18B20
#define ONE_WIRE_BUS 13

//Porta pino relé
int rele = 12; 

// Define uma instancia do oneWire para comunicacao com o sensor
OneWire oneWire(ONE_WIRE_BUS);

// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

//CARACTER ESPECIAL
byte caracter[8] = {0x18,0x18,0x3,0x4,0x4,0x4,0x3,0x0};

// Armazena temperaturas minima e maxima
float tempMin = 999;
float tempMax = 0; 
float tempIdeal = 80; //temp que desliga a relé
float tempAtual; //temperatura atual
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;

void setup(void){

  pinMode(7,INPUT); //botão de decrementar a tempAtual
  pinMode(2,INPUT);//botão de incrementar a tempAtual
  
  lcd.begin(16,2);
  lcd.createChar(0,caracter);
  Serial.begin(9600);
  sensors.begin();
   //inicializa display
  
  
  // Localiza e mostra enderecos dos sensores
  Serial.println("Localizando sensores DS18B20...");
  Serial.print("Foram encontrados ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" sensores.");

  //teste de detecção do sensor
  if (!sensors.getAddress(sensor1, 0)) 
     Serial.println("Sensores nao encontrados !"); 
  // Mostra o endereco do sensor encontrado no barramento
  Serial.print("Endereco sensor: ");
  mostra_endereco_sensor(sensor1);
  Serial.println();
  
  //saída pino relé
  pinMode(rele, OUTPUT);   
}

void mostra_endereco_sensor(DeviceAddress deviceAddress){
  for (uint8_t i = 0; i < 8; i++)
  {
    // Adiciona zeros se necessário
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void loop(){

  //teste dos botões para aumentar ou diminuir a tempIdeal
  if(digitalRead(7) == 1){
    tempIdeal--;
  }
  if(digitalRead(2) == 1){
    tempIdeal++;
  }
  
  lcd.setBacklight(HIGH);
  // Le a informacao do sensor
  sensors.requestTemperatures();
  //atribui para uma variável a temperatura
  tempAtual = sensors.getTempC(sensor1);
  
  //compara temp para ligar ou desligar relé
  if(tempAtual < tempIdeal){
    digitalWrite(rele, HIGH);
  }
  
  if(tempAtual >=tempIdeal){
    digitalWrite(rele, LOW);
      while(tempAtual>=tempIdeal){
        sensors.requestTemperatures();
        tempAtual = sensors.getTempC(sensor1);
        
        //mensagem indicando a temperatura ideal da água
        lcd.clear();
        lcd.setCursor(2,0);
        lcd.print("TEMP IDEAL!"); 
        
        //print da temperatura Atual
        lcd.setCursor(0,1);
        lcd.print("TEMP: "); 
        lcd.setCursor(5,1);
        lcd.print(tempAtual,1);
  
        //print da temperatura ideal
        lcd.setCursor(10,1);
        lcd.print("G:");
        lcd.print(tempIdeal,1);
        
        //teste dos botões para aumentar ou diminuir a tempIdeal
        if(digitalRead(7) == 1){
          tempIdeal--;
        }
        if(digitalRead(2) == 1){
          tempIdeal++;
        }
        delay(500);
      }
   }
     
  // Atualiza temperaturas minima e maxima
  if (tempAtual < tempMin){
    tempMin = tempAtual;
  }
  if (tempAtual > tempMax){
    tempMax = tempAtual;
  }

  //printa no lcd 16x2
  lcd.clear();

  //print temperatura atual
  lcd.setCursor(0,0);
  lcd.print("T: ");
  lcd.setCursor(2,0);
  lcd.print(tempAtual,1);
  
  //print do caracter '°C'
  lcd.setCursor(6,0);
  lcd.print((char)0);

  //print da temperatura ideal
  lcd.setCursor(10,0);
  lcd.print("G:");
  lcd.print(tempIdeal,1);
  
  //print temperatura mínima
  lcd.setCursor(0,1);
  lcd.print("L:");
  lcd.print(tempMin,1);

  //print temperatura máxima
  lcd.setCursor(10,1);
  lcd.print("H:");
  lcd.print(tempMax,1);
  
  delay(500);

  // Mostra dados no serial monitor
  Serial.print("Temp C: ");
  Serial.print(tempAtual);
  Serial.print(" // Min : ");
  Serial.print(tempMin);
  Serial.print(" // Max : ");
  Serial.println(tempMax);
  delay(0);
}
