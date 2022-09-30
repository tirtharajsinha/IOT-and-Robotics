// ##################################
// Author : Tirtharaj Sinha
// Written for : arduino AVR Boards
// Date : 29-09-2022
// IDE : Arduino IDE 2.X
// Description : A controller to control component from third party script over serial port
// ##################################


#include <Servo.h>


// variable and const declearation
const int trigPin = 4;
const int echoPin = 5;
const int servopin = 6;


// led pin
const int ledpin1 = 12;
const int ledpin2 = 11;
const int ledpin3 = 10;

bool isLed1 = false;
bool isLed2 = false;
bool isLed3 = false;

int Buzzerpin = 9;

bool isBuzzer = false;

int curLoc = 0;    // current angle of servo
int increase = 1;  // direction of servo{increasing:1,decreasing:0}

long duration;
int distinCM;

// auto control
bool isServoAutoControl = false;
bool isIncreasing = true;

String curDis;  // current distance upon angle
long distance_limit = 50;

// sensor declearation
Servo radarServo;


void setup() {

  // setting the led pins
  pinMode(ledpin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);
  pinMode(ledpin3, OUTPUT);
  pinMode(Buzzerpin, OUTPUT);

  // setting ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

  // starting the servo
  radarServo.attach(servopin);
  radarServo.write(0);
}

void loop() {
  // check any serial input is given
  if (Serial.available()) {
    String command = Serial.readString();
    manage_command(command);
  }
  if (millis() % 200 == 0) {
    if (isServoAutoControl) {
      autoRotateServo();
    }
  }
  // reading sensor in every 1s
  if (millis() % 1000 == 0) {

    curDis = calculate_distance(curLoc);
    Serial.println(curDis);
  }
}

void manage_command(String command) {
  if (command.indexOf("led") >= 0) {
    int pinNo = command.substring(3).toInt();
    toggleLED(pinNo);
  } else if (command.indexOf("servo") >= 0) {
    int angleReq = command.substring(5).toInt();
    rotateServo(angleReq);
  } else if (command.indexOf("buzzer") >= 0) {
    toggleBuzzer();
  } else if (command.indexOf("auto") >= 0) {
    if (isServoAutoControl) {
      isServoAutoControl = false;
    } else {
      isServoAutoControl = true;
    }
  }
}

void rotateServo(int angel) {
  if (!isServoAutoControl) {
    if (angel > curLoc) {
      for (int i = curLoc; i <= angel; i++) {
        radarServo.write(i);
        delay(50);
      }
    } else {
      for (int i = curLoc; i >= angel; i--) {
        radarServo.write(i);
        delay(50);
      }
    }
    curLoc = angel;
  }
  // Serial.println(angel);
}

void autoRotateServo() {
  if (isIncreasing) {
    curLoc++;
  } else {
    curLoc--;
  }

  if (curLoc == 180) {
    isIncreasing = false;
  } else if (curLoc == 0) {
    isIncreasing = true;
  }

  radarServo.write(curLoc);
}

void toggleLED(int led) {
  if (led == 1) {
    if (isLed1) {
      digitalWrite(ledpin1, LOW);
      isLed1 = false;
    } else {
      digitalWrite(ledpin1, HIGH);
      isLed1 = true;
    }
  } else if (led == 2) {
    if (isLed2) {
      digitalWrite(ledpin2, LOW);
      isLed2 = false;
    } else {
      digitalWrite(ledpin2, HIGH);
      isLed2 = true;
    }
  } else if (led == 3) {
    if (isLed3) {
      digitalWrite(ledpin3, LOW);
      isLed3 = false;
    } else {
      digitalWrite(ledpin3, HIGH);
      isLed3 = true;
    }
  }
}

String calculate_distance(int i) {

  // digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distinCM = duration * 0.034 / 2;


  return String(i) + "#" + String(distinCM);
}


void toggleBuzzer() {
  if (isBuzzer) {
    digitalWrite(Buzzerpin, LOW);
    isBuzzer = false;
  } else {
    digitalWrite(Buzzerpin, HIGH);
    isBuzzer = true;
  }
}