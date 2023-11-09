// Use level shifter if operating voltage is diffrent in microcontroller board.


#include <Wire.h>
#include <ArduinoJson.h>
#include <AFMotor.h>

AF_DCMotor motor_left(1);
AF_DCMotor motor_right(2);

double left = 0;
double right = 0;

void setup() {
  Wire.begin(8);                /* join i2c bus with address 8 */
  Wire.onReceive(receiveEvent); /* register receive event */
  Serial.begin(9600);           /* start serial for debug */
}

void loop() {
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
  // Serial.println(howMany);
  String data = "";
  while (0 < Wire.available()) {
    char c = Wire.read();
    data += (String)c; /* receive byte as a character */
    // Serial.print(c);
  }

  DynamicJsonDocument doc(1024);
  deserializeJson(doc, data);
  double x = doc["data"][0];
  double y = doc["data"][1];
  int angle = doc["data"][2];
  // Serial.println(x);
  // Serial.println(y);
  // Serial.println(speed);


  y = -y;
  left = (y / 100) * 150;
  right = left;

  if (x > 40) {
    if (left < 0) {
      left = min(-100, left);
    } else {
      left = max(100, left);
    }
    double xx = min(100, x);
    right = right * ((100 - xx) / 100);
  } else if(x<-40 ) {
    if (right < 0) {
      right = min(-100, right);
    } else {
      right = max(100, right);
    }
    double xx = min(100, abs(x));
    left = left * ((100 - xx) / 100);
  }

  left=round(left);
  right=round(right);

  Serial.println("LEFT : " + String(left) + " RIGHT : " + String(right));

  motorController(left,right);
}





void motorController(int left,int right){
  if(left==0 && right==0){
    motor_left.run(RELEASE);
    motor_right.run(RELEASE);
    return;
  }

  if(right>0){
    motor_right.run(FORWARD);
    motor_right.setSpeed(right);
  }
  else{
    motor_right.run(BACKWARD);
    motor_right.setSpeed(abs(right));
  }

  if(left>0){
    motor_left.run(FORWARD);
    motor_left.setSpeed(left);
  }
  else{
    motor_left.run(BACKWARD);
    motor_left.setSpeed(abs(left));
  }

  
}
