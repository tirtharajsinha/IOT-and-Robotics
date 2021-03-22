#include <NewPing.h>

#include <AFMotor.h>
#include <Servo.h>
String voice;
#define TRIG_PIN A0 
#define ECHO_PIN A1
#define MAX_DISTANCE 100
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1 (1, MOTOR12_1KHZ); 
AF_DCMotor motor2 (2, MOTOR12_1KHZ); 
Servo myServo; 

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup()
{
Serial.begin(9600); 
myServo.attach(10); 
myServo.write(90);

  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);  

}

void loop() 
{
  while (Serial.available()){ 
     delay(10); 
    char c = Serial.read(); 
    if (c == '#') {break;} 
    voice += c; 
  }
  if (voice.length() > 0){
    if(voice == "*front"){
forward_car();
      }
    else if(voice == "*go back"){
back_car();
      }
    else if(voice == "*right") {
right_car();
    }
    else if(voice == "*left") {
left_car();
    }
    else if(voice == "*stop") {
stop_car();
    }else if(voice=="*auto") {
    int distanceR = 0;
int distanceL = 0;
 delay(40);

 if(distance<=25)
 {
stop_car();
  delay(100);
back_car();
  delay(200);
stop_car();
  delay(200);
distanceR = lookRight();
  delay(200);
distanceL = lookLeft();
  delay(200);

  if(distanceR>=distanceL)
  {
right_car();
stop_car();
  } 
  else

  {
left_car();
stop_car();
  }
 } 

 else
 {
forward_car();
 }
 distance = readPing();
}
  }voice="";}
  

int lookRight()
{
myServo.write(50); 
    delay(500);
int distance = readPing();
    delay(100);
myServo.write(115); 
    return distance;
}

int lookLeft()
{
myServo.write(170); 
    delay(500);
int distance = readPing();
    delay(100);
myServo.write(115); 
    return distance;
    delay(100);
}

int  readPing() { 
  delay(100);
int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;}

void forward_car()
{
  motor1.run(FORWARD);
  motor1.setSpeed(700);
  motor2.run(FORWARD);
  motor2.setSpeed(700);
  delay(2000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void back_car()
{
  motor1.run(BACKWARD);
  motor1.setSpeed(700);
  motor2.run(BACKWARD);
  motor2.setSpeed(700);
  delay(2000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void right_car()
{
myServo.write(0);
  delay(1000);
myServo.write(90);
  delay(1000);
  motor1.run(FORWARD);
  motor1.setSpeed(190);
  motor2.run(BACKWARD);
  motor2.setSpeed(190);
  delay(1000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void left_car()
{
myServo.write(180);
  delay(1000);
myServo.write(90);
  delay(1000);
  motor1.run(BACKWARD);
  motor1.setSpeed(190);
  motor2.run(FORWARD);
  motor2.setSpeed(190);
  delay(1000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void stop_car ()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}





