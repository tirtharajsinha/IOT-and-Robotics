// ESP Code 
// BoardName - Waveshare ESP32 S3 Pico

int value = 0;
float voltage;

int gpio[] = {1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42 };
int num_of_gpio = sizeof(gpio) / sizeof(gpio[0]);
int current_target = -1;
long int ptime = 0;

void setup() {
  pinMode(0, INPUT);
  Serial.begin(9600);
  Serial.println("Press BTN connected to GPIO0 / PRESS [BOOT] BUTTON to start pin evaluator :) ");
  Serial.println("Also Press BTN connected to GPIO0 / PRESS [BOOT] BUTTON to evaluate next pin ==>");
}

void loop() {


  int a = digitalRead(0);
  if (a == LOW) {
    if (millis() - ptime > 2000) {
      if (current_target == num_of_gpio) {
        current_target = -1;
      }
      if(current_target!=-1){
        digitalWrite(gpio[current_target], LOW);
      }
      current_target++;
      
      Serial.println("\nEvaluating " + String(gpio[current_target]) + " ...");
      pinMode(gpio[current_target], OUTPUT);
      digitalWrite(gpio[current_target], HIGH);
      ptime = millis();
      
    }
  }
}
