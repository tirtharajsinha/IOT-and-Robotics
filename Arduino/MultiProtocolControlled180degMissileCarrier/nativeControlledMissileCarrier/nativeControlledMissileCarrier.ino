#include <Servo.h>


// Servo Conf
int ServoPinX = 5;
int ServoPinY = 3;

Servo ServoX;
Servo ServoY;

int PosX = 0;
int PosY = 0;

int ServoLimitHigh = 180;
int ServoLimitLow = 0;

int ServoStep = 10;  // movement angel on each command



// Joystick enable indecation LED
int led = 13;

// Joystick enable button
int btn = 2;
bool ENABLE = false;
long btntime = 0;


// joystick conf
#define joyX A0
#define joyY A1

double xValue = 0;
double yValue = 0;

int threshhold_latency = 150;
int threshhold_fix = 500;

long long commandTimeoutX = 0;
long long commandTimeoutY = 0;
int commandTimeout = 100;


void setup() {
  Serial.begin(9600);


  // put your setup code here, to run once:
  ServoX.attach(ServoPinX);
  ServoY.attach(ServoPinY);

  // Setting servo to initial position
  // Serial.println("SERVO Ready");
  ServoY.write(PosY);
  ServoX.write(PosX);

  // Configuring the led and button
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT_PULLUP);


  // Serial.println("Joystick DISABLED");
}

void loop() {

  joystick_manager();
}


void UP() {
  // Go up
  if (manageAngel(PosY, 1)) {
    // Serial.println("Going UP");
    PosY += ServoStep;
    ServoY.write(PosY);
  }
}

void DOWN() {
  // Go Down
  if (manageAngel(PosY, 0)) {
    // Serial.println("Going DOWN");
    PosY -= ServoStep;
    ServoY.write(PosY);
  }
}


void RIGHT() {
  // Go Right
  if (manageAngel(PosX, 1)) {
    // Serial.println("Going RIGHT");
    PosX += ServoStep;
    ServoX.write(PosX);
  }
}


void LEFT() {
  // Go Left
  if (manageAngel(PosX, 0)) {
    // Serial.println("Going LEFT");
    PosX -= ServoStep;
    ServoX.write(PosX);
  }
}

bool manageAngel(int a, int direction) {
  if (direction == 1) {
    if ((a + ServoStep) <= ServoLimitHigh) {
      return true;
    } else {
      return false;
    }
  } else {
    if ((a - ServoStep) >= ServoLimitLow) {
      return true;
    } else {
      return false;
    }
  }
}


// exp-now receiver




// Joystick Controller
void controller_joystick() {
  CheckjoystickPermission();
  if (ENABLE) {
    checkJoystick();
  }
}

void CheckjoystickPermission() {
  // Serial.println(digitalRead(btn));
  if (digitalRead(btn) == LOW) {
    if ((millis() - btntime) > 1000) {
      btntime = millis();
      ENABLE = !ENABLE;
      if (ENABLE) {
        // Serial.println("Joystick ENABLED");
        digitalWrite(led, HIGH);
      } else {
        // Serial.println("Joystick DISABLED");
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

    if ((millis() - commandTimeoutX) > commandTimeout) {
      commandTimeoutX = millis();
      if ((xValue - threshhold_fix) > threshhold_latency) {
        LEFT();
      }
      if ((xValue - threshhold_fix) < (-1 * threshhold_latency)) {
        RIGHT();
      }
    }


    if ((millis() - commandTimeoutY) > commandTimeout) {
      commandTimeoutY = millis();
      if ((yValue - threshhold_fix) > threshhold_latency) {
        UP();
      }

      if ((yValue - threshhold_fix) < (-1 * threshhold_latency)) {
        DOWN();
      }
    }

    Serial.print(PosX);
    Serial.print("\t");
    Serial.println(PosY);
  }
}
