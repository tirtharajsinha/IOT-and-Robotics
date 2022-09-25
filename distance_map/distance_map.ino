int triggerpin = 11;
int echopin = 12;
int ledpin = 13;
int time;
int distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(triggerpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(triggerpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerpin, LOW);
  time = pulseIn(echopin, HIGH);
  distance = (time * 0.034);
  if (distance <= 50) {
    Serial.println("Door Open");
    Serial.print("distance=");
    Serial.println(distance);
    digitalWrite(13, HIGH);
    delay(100);
  } else {
    Serial.println("Door Close");
    Serial.print("distance=");
    Serial.println(distance);
    digitalWrite(13, LOW);
    delay(100);
  }
}