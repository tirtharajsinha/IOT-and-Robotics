#include <Servo.h>


const int trigPin = 10;
const int echoPin = 11;
const int servopin = 12;

long duration;
int distinCM;


Servo radarServo;


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  radarServo.attach(servopin);
}
void loop() {
  for (int i = 0; i <= 180; i++) {
    calculate_distance();
  }

  for (int i = 180; i >= 0; i--) {
    calculate_distance();
  }
}

void calculate_distance() {
  radarServo.write(i);
  delay(50);
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
}