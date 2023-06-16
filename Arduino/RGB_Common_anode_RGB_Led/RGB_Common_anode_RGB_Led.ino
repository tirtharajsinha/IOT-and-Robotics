// LEDs must be connected to arduino PWM pins - see board pinout
#define RED  6   // pin that red led is connected to    
#define GREEN  5 // pin that green led is connected to     
#define BLUE  3  // pin that blue led is connected to    
#define DELAY  20  // internal delay in ms

void setup() { 
  // LED connection pins to be set as an output
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  // fade from red to green
  for(int i=0; i<255; i++) {
    analogWrite(RED, i); // red initially ON
    analogWrite(GREEN, 255-i); // green initially OFF
    analogWrite(BLUE, 255); // blue OFF
    delay(DELAY); // wait before next transition
  }

  // fade from green to blue
  for(int i=0; i<255; i++) {
    analogWrite(RED, 255); // red OFF
    analogWrite(GREEN, i); // green initially ON
    analogWrite(BLUE, 255-i); // blue initially OFF
    delay(DELAY);
  }

  // fade from blue to red
  for(int i=0; i<255; i++) {
    analogWrite(RED, 255-i); // red initially OFF
    analogWrite(GREEN, 255); // green OFF
    analogWrite(BLUE, i); // blue initially ON
    delay(DELAY);
  }
}