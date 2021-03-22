#include<ESP8266WiFi.h>
#include<Blynk.h>
#include<BlynkSympleESP8266.h>
char auth[]="fdlWcmQ2jchnpYqEakrwqYIOoxHim6";
char ssid[]="tirtha's realme3";
char pass[]="9876543210";
BlynkTimer timer;
void MS()
{
  float m=analogRead(A0);
  Blynk.virtualWrite(V0,m);
  
}
void setup() {
 Serial.begin(9600);
 Blynk.begin(auth,ssid,pass);
 timer.setInterval(1000L,MS);
}

void loop() {
 Blynk.run()
 timer.run()
}
