// include the library code:
#include <LiquidCrystal.h>
#include "DHT.h"
#define sensorpin 10
int touch=LOW;
int ledpin1=8;
String lable ="lable 1 *";
#define DHTPIN 6     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11


// initialize the library by associating any needed LCD interface pin`
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


DHT dht(DHTPIN, DHTTYPE);
void setup() {
  pinMode(sensorpin,INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  dht.begin();
  temp_disp();

  lcd.setCursor(0, 0);
  lcd.print("OFF-> "+lable);
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  
  
}

void loop() {
  if(millis() % 10000==0){
    temp_disp();  
  }
  fancontrol();

  
   
}

void fancontrol(){
  int senseValue=digitalRead(sensorpin);
  if(senseValue==HIGH && touch==LOW)
  { 
    touch=HIGH;
    Serial.println("ON");
    lcd.setCursor(0, 0);
    lcd.print("ON -> "+lable);
    digitalWrite(ledpin1,HIGH);
    delay(200);
  }
  else if(senseValue==HIGH && touch==HIGH)
  {
    touch=LOW;
    Serial.println("OFF ");
    lcd.setCursor(0, 0);
    lcd.print("OFF-> "+lable);
    digitalWrite(ledpin1,LOW);
    delay(200);
  }
}

void temp_disp(){
  
    float t = dht.readTemperature();
    Serial.print(t);
    Serial.print(F("C \n"));
    lcd.setCursor(5, 1);
    lcd.print(t);
    lcd.print(F("C "));
    if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
    }else{
       if(t>50){
         lable="lable3(:(}";
        }
       else if(t>30){
         lable="lable2- :)";
        }
        else{
          lable="label 1*";
        }
        }
    
}
