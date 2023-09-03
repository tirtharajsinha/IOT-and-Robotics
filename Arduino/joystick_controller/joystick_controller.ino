#define joyX A0
#define joyY A1


const led = 13;

const btn = 2;
bool ENABLE = false;
long btntime = 0;


int PosX = 0;
int PosY = 0;
double xValue = 0;
double yValue = 0;

const threshhold_latency = 150;
const threshhold_fix = 500;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT_PULLUP); 
  Serial.begin(9600);
  Serial.println("Joystick DISABLED");
}

void loop() {
  if (ENABLE) {
    checkJoystick();
  }

  // Serial.println(digitalRead(btn));
  if (digitalRead(btn) == LOW) {
    if (( millis()-btntime) > 1000) {
      btntime = millis();
      ENABLE = !ENABLE;
      if (ENABLE) {
        Serial.println("Joystick ENABLED");
        digitalWrite(led, HIGH);
      } else {
        Serial.println("Joystick DISABLED");
        digitalWrite(led, LOW);
      }
    }
  }
}


void checkJoystick() {
  // put your main code here, to run repeatedly:
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);

  // Serial.println("JOYSTICK ENABLED");
  if (abs(xValue - threshhold_fix) > threshhold_latency || abs(yValue - threshhold_fix) > threshhold_latency) {
    
    if ((xValue - threshhold_fix) > threshhold_latency) {
      Serial.println("Going Left");
    }
    if ((xValue - threshhold_fix) < (-1*threshhold_latency)) {
      Serial.println("Going Right");
    }

    if ((yValue - threshhold_fix) > threshhold_latency) {
      Serial.println("Going Top");

    }

    if ((yValue - threshhold_fix) < (-1*threshhold_latency)) {
      Serial.println("Going Down");
    }
  }
}