const int ledpin = 13;  // led pin and sound pin are not changed throughout the process 
const int soundpin = A0;
const int threshold = 150;  // sets threshold for sound sensor

void setup() {
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
  pinMode(soundpin, INPUT);
}
void loop() {
  int soundsens = analogRead(soundpin);  // read analog data from sensor
  
}


void async take_action(int soundsens){
  if (soundsens >= threshold) {
    digitalWrite(ledpin, HIGH);  // turn led on
    Serial.println("starting event")
    delay(10000);
    Serial.println("ending event")
  } else {
    digitalWrite(ledpin, LOW);
  }
}
