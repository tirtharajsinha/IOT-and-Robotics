#define sensorpin 2
int ledpin1=13;
int ledpin2=12;
int ledpin3=11;




void setup() {
  Serial.begin(9600);
  pinMode(ledpin1,OUTPUT);
   pinMode(ledpin2,OUTPUT);
    pinMode(ledpin3,OUTPUT);
  pinMode(sensorpin,INPUT);
  

}

void loop() {
  int senseValue=digitalRead(sensorpin);
  if(senseValue==HIGH)
  { digitalWrite(ledpin1,HIGH);
  delay(100);
  digitalWrite(ledpin1,LOW);
  delay(100);
   digitalWrite(ledpin2,HIGH);
  delay(100);
  digitalWrite(ledpin2,LOW);
  delay(100);
   digitalWrite(ledpin3,HIGH);
  delay(100);
  digitalWrite(ledpin3,LOW);
  delay(100);
  
  Serial.println("TOUCHED");
  }
  else
  {digitalWrite(ledpin1,LOW);
  digitalWrite(ledpin2,LOW);
  digitalWrite(ledpin3,LOW);
  
  Serial.println("not touched");
  }
  delay(500);
  

}
