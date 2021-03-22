int sensorPin=A0;
int sensorValue=0; 
int piezoPin=9; 
void setup() { 
pinMode(sensorPin,INPUT); 
pinMode(7,OUTPUT); 
pinMode(6,OUTPUT); 
pinMode(piezoPin,OUTPUT); 
digitalWrite(7,HIGH); 
digitalWrite(6,LOW); 
} 
void loop() { 
sensorValue=analogRead(sensorPin); 
if(sensorValue<=1000) 
{
digitalWrite(piezoPin,HIGH); 
{tone(9,3047,400); noTone(8); } 
digitalWrite(7,HIGH); 
}
 else { 
digitalWrite(piezoPin,LOW); 
digitalWrite(7,LOW); 
} 
sensorValue=1000
}
