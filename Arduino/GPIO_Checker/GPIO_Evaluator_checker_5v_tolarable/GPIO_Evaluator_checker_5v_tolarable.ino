int value = 0;
float voltage;

void setup(){
  Serial.begin(9600);
}

void loop(){
  value = analogRead(A0);
  voltage = value * 5.0/1023;
  Serial.print("Voltage= ");
  Serial.println(voltage);
  delay(500);
}

