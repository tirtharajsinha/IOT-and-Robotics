#include "DHT.h"
//#define sensorpin 10

#define DHTPIN 6  // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  dht.begin();
  temp_disp();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() % 3000 == 0) {
    temp_disp();
  }
}


void temp_disp() {

  float t_inC = dht.readTemperature();
  float i_inF = t_inC * 1.8 + 32;
  float h = dht.readHumidity();

  String method = "si"; // or Imperial 
  Serial.print("Temperature = ");

  if(method=="si"){
    Serial.print(t_inC);
    Serial.print(F(" °C"));
  }
  else{
    Serial.print(t_inC);
    Serial.print(F(" °F"));
  }
    
  Serial.print("\t\t Humidity = ");
  Serial.print(h);
  Serial.println(F("%"));
  if (isnan(t_inC)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
}