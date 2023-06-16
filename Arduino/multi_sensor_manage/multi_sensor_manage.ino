// ##################################
// Author : Tirtharaj Sinha
// Written for : arduino AVR Boards
// Date : 27-09-2022
// IDE : Arduino IDE 2.X
// Description : A multisensor reader to read sensor data from third party program over serial port
// ##################################





#include "DHT.h"
#include <Servo.h>


#define DHTPIN 6  // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11

// variable and const declearation
const int trigPin = 10;
const int echoPin = 11;
const int servopin = 12;

int curLoc = 0;    // current angle of servo
int increase = 1;  // direction of servo{increasing:1,decreasing:0}

long duration;
int distinCM;



String curTemp;  // current temp and humidity
String curDis;   // current distance upon angle

// sensor declearation
Servo radarServo;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

  // starting the servo and DHT11
  radarServo.attach(servopin);
  dht.begin();



  curTemp = temp_disp();
  curDis = calculate_distance(curLoc);

  Serial.println(curTemp + "," + curDis);
}

void loop() {
  // servo arm rotation in every 2s
  // full cycle covers in 8s
  // 0deg => 90deg => 180deg => 90deg => 0deg

  if (millis() % 2000 == 0) {
    if (curLoc == 180) {
      increase = 0;
    } else if (curLoc == 0) {
      increase = 1;
    }


    if (increase == 1) {
      curLoc += 90;
    } else {
      curLoc -= 90;
    }

    radarServo.write(curLoc);
  }

  // sensor reading in every 1s
  if (millis() % 1000 == 0) {
    curTemp = temp_disp();
    curDis = calculate_distance(curLoc);

    Serial.println(curTemp + "," + curDis);
  }
}


String temp_disp() {

  float t_inC = dht.readTemperature();
  float i_inF = t_inC * 1.8 + 32;
  float h = dht.readHumidity();

  String method = "si";  // or Imperial
  if (isnan(t_inC)) {
    return "0.0,0.0";
  } else {
    return String(t_inC) + "|" + String(h);
  }
}

String calculate_distance(int i) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distinCM = duration * 0.034 / 2;

  Serial.print(i);
  Serial.print("*");
  Serial.print(distinCM);
  Serial.print("#");
  return String(i) + "#" + String(distinCM);
}