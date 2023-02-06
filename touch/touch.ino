#define sensorpin 2
int ledpin1 = 13;

void setup() {
  Serial.begin(9600);
  pinMode(ledpin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);
  pinMode(ledpin3, OUTPUT);
  pinMode(sensorpin, INPUT);
}

void loop() {
  int senseValue = digitalRead(sensorpin);
  if (senseValue == HIGH) {
    digitalWrite(ledpin1, HIGH);
    Serial.println("TOUCHED TO HIGH");
  } else {
    digitalWrite(ledpin1, LOW);
    Serial.println("TOUCHED TO LOW");
  }
}