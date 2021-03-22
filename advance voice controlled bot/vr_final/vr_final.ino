
/*
  * @author  Aditya Tripathi
  * @brief   This file provides a demostration on 
              how to control led by using VoiceRecognitionModule
  ******************************************************************************
  * @note:
        voice control led
   ******************************************************************************
  * @section  HISTORY
    
    2017/11/13    Initial version.
  */
  
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

/**        
  Connection
  Arduino    VoiceRecognitionModule
   2   ------->     TX
   3   ------->     RX
*/
VR myVR(2,3);    // 2:RX 3:TX, you can choose your favourite pins.

uint8_t records[7]; // save record
uint8_t buf[64];

int led = 13;
const int left0=4;
const int left1=5;
const int right0=6;
const int right1=7;// initializing motors

const int trig = 9;
const int echo = 10;//initializing sensors

#define forwardRecord   (0)
#define backwardRecord   (1) 
#define turnRecord (2) 
#define autoPilot (3)
/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf     --> command length
           len     --> number of parameters
*/
void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}

/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf  -->  VR module return value when voice is recognized.
             buf[0]  -->  Group mode(FF: None Group, 0x8n: User, 0x0n:System
             buf[1]  -->  number of record which is recognized. 
             buf[2]  -->  Recognizer index(position) value of the recognized record.
             buf[3]  -->  Signature length
             buf[4]~buf[n] --> Signature
*/
void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}

void setup()
{
  
  /** initialize */
  myVR.begin(9600);
  
  Serial.begin(115200);
  Serial.println("Elechouse Voice Recognition V3 Module\r\nControl LED sample");
  
  pinMode(led, OUTPUT);
  pinMode(left0,OUTPUT);
  pinMode(left1,OUTPUT);
  pinMode(right0,OUTPUT);
  pinMode(right1,OUTPUT);
    
  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }
  
  if(myVR.load((uint8_t)forwardRecord) >= 0){
    Serial.println("loaded");
  }
  
  if(myVR.load((uint8_t)backwardRecord) >= 0){
    Serial.println("loaded");
  }
    if(myVR.load((uint8_t)turnRecord) >= 0){ //loading what's trained
    Serial.println("loaded");
  }
      if(myVR.load((uint8_t)autoPilot) >= 0){ //loading what's trained
    Serial.println("loaded");
  }
}

void loop()
{
  long duration, inches, cm;
  
  int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0){
    switch(buf[1]){
      case forwardRecord:
        digitalWrite(led, HIGH);
        digitalWrite(left0, LOW);
        digitalWrite(left1, HIGH);
        digitalWrite(right0, LOW);
        digitalWrite(right1, HIGH);
        delay(5000);
        digitalWrite(left0, LOW);
        digitalWrite(left1, LOW);
        digitalWrite(right0, LOW);
        digitalWrite(right1,LOW);
        break;
      case backwardRecord:
        /** turn on LED */
        digitalWrite(led, LOW);
        digitalWrite(left0, HIGH);
        digitalWrite(left1, LOW);
        digitalWrite(right0, HIGH);
        digitalWrite(right1, LOW);
        delay(5000);
        digitalWrite(left0, LOW);
        digitalWrite(left1, LOW);
        digitalWrite(right0, LOW);
        digitalWrite(right1,LOW);
        break;
        case turnRecord:
        {
        digitalWrite(left1, LOW);
        digitalWrite(left0, HIGH);
        digitalWrite(right0, LOW);
        digitalWrite(right1, HIGH);
        delay(5000);
        digitalWrite(left0, LOW);
        digitalWrite(left1, LOW);
        digitalWrite(right0, LOW);
        digitalWrite(right1,LOW);
        }break;
        case autoPilot:
        { for(int i=1;i>0 ;i++){
                       pinMode(trig, OUTPUT);
                       digitalWrite(trig, LOW);
                       delayMicroseconds(2);
                       digitalWrite(trig, HIGH);
                       delayMicroseconds(5);
                       digitalWrite(trig, LOW);

  
                         pinMode(echo, INPUT);
                         duration = pulseIn(echo, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);

              if(cm<20){
                   digitalWrite(left0, LOW);
                   digitalWrite(left1, HIGH);
                   digitalWrite(right1, LOW);
                   digitalWrite(right0, HIGH);
                      delay(5000);
                   digitalWrite(left0, LOW);
                   digitalWrite(left1, LOW);
                   digitalWrite(right0, LOW);
                   digitalWrite(right1,LOW);}
                   else{
                   digitalWrite(left0, LOW);
                   digitalWrite(left1, HIGH);
                   digitalWrite(right0, LOW);
                   digitalWrite(right1,HIGH);}
        }
        
        break;
}
      default:
        Serial.println("Record function undefined");
        break;
    }
    /** voice recognized */
    printVR(buf);
  }
}


long microsecondsToInches(long microseconds)
{  return microseconds / 74 / 2;}
long microsecondsToCentimeters(long microseconds)
{return microseconds / 29 / 2;}
