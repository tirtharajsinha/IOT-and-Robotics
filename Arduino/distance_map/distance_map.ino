int trigPin = 11;
int echoPin = 12;
int ledpin = 13;
int Buzzerpin = 10;
int duration;
float distance;
int distance_limit = 50;

bool isBuzzer = false;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(Buzzerpin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  if (millis() % 1000 == 0) {
    distance=calculate_distance();
    if (distance < distance_limit) {
      toggleAlert();

    } else {
      digitalWrite(Buzzerpin, LOW);
      digitalWrite(ledpin, LOW);
    }
  }
}

float calculate_distance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance);
  return distance;
}


void toggleAlert() {
  if (isBuzzer) {
    digitalWrite(Buzzerpin, LOW);
    digitalWrite(ledpin, LOW);
    isBuzzer = false;
  } else {
    digitalWrite(Buzzerpin, HIGH);
    digitalWrite(ledpin, HIGH);
    isBuzzer = true;
  }
}