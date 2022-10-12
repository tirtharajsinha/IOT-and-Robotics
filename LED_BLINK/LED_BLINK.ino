

 



void setup() {
  // put your setup code here, to ru
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  delay(1500);
  digitalWrite(12, HIGH);
  delay(1500);
  digitalWrite(10, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(400);
  digitalWrite(12, LOW);
  delay(400);
  digitalWrite(10, LOW);
  delay(400);
}