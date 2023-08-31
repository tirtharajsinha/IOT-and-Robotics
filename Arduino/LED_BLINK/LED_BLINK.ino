// the setup function runs once when you press reset or power the board


// int LED=13; 
int LED=1;

void setup() {
  // initialize digital pin LED_BUILTIN or pin 13 as an output.
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(2000);                      // wait for a second
  digitalWrite(LED, LOW);   // turn the LED off by making the voltage LOW
  delay(2000);                      // wait for a second
  Serial.println("Led Blink sketch..");
}
