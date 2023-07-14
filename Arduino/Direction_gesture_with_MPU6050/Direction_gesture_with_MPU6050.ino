#include "Wire.h"
#include <MPU6050_light.h>

// For circuit diagram, more details about MPU6050 visit page https://lastminuteengineers.com/mpu6050-accel-gyro-arduino-tutorial/
MPU6050 mpu(Wire);


unsigned long timer = 0;
double x,y,z;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0) {}  // stop everything if could not connect to MPU6050
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets();  // gyro and accelero
  Serial.println("Done!\n");
}
void loop() {
  mpu.update();
  if ((millis() - timer) > 0) {  // print data every 10ms
    x=mpu.getAngleX();
    y=mpu.getAngleY();
    z=mpu.getAngleZ();
    checkDirectionX(x, y, z);
    timer = millis();
  }
}


void checkDirectionX(double xval, double yval, double zval) {
  
  int x= toDeg(xval);
  // Serial.println(x);
  if (x > 345 || x < 15) {
    Serial.println("Stop");
  } else if (x > 180) {
    Serial.print("Forword");
    checkDirectionY(xval, yval, zval);
  } else {
    Serial.print("Backword");
    checkDirectionY(xval, yval, zval);
  }
}

void checkDirectionY(double xval, double yval, double zval) {
  // Serial.println(y);
   int y = toDeg(yval);
  if (y > 350 || y < 10) {
    Serial.println("");
  } else if (y > 180) {
    Serial.println(" Right");
  } else {
    Serial.println(" Left");
  }
}




int toDeg(double val){
  int value=int(val);
  if(value<0 && value!=0){
    return 360+value;
  }
  return value;
}