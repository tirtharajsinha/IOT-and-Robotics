#include <Adafruit_NeoPixel.h>


#define AUDIOPIN A0
#define PIN 6          // Pin
#define N_LEDS 16      //Number of led in total strips
#define THRESHOLD 600  // sets threshold for sound sensor

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
int maxamp = 0;
unsigned long noti;

uint32_t c[N_LEDS];

void setup() {
  pinMode(AUDIOPIN, INPUT);
  pinMode(A1, OUTPUT);
  pinMode(3, INPUT);
  digitalWrite(A1, HIGH);
  Serial.begin(9600);
  strip.begin();
  for (int i = 0; i < N_LEDS; i++) {
    c[i] = strip.Color(0, 0, 0);
  }
}

void loop() {
  int soundsens = analogRead(AUDIOPIN);  // read analog data from sensor
  maxamp=max(maxamp,soundsens);
  Serial.print(soundsens);
  Serial.print(",");
  Serial.println(maxamp);

  uint32_t served = colorServe(soundsens);
  if (millis() - noti > 10) {
    chase(served);
    noti = millis();
  }
}




void chase(uint32_t served) {
  int count = 0;
  for (int i = N_LEDS - 1; i > 0; i--) {
    c[i] = c[i - 1];
    strip.setPixelColor(i, c[i]);
    if (c[i] != 0) {
      count++;
    }
  }
  c[0] = served;
  strip.setPixelColor(0, c[0]);
  strip.show();
}

uint32_t colorServe(int val) {
  if (val < THRESHOLD) {
    return 0;
  } else if (val < THRESHOLD+30) {
    return strip.Color(100, 100, 100);
  } else if (val < THRESHOLD+50) {
    return strip.Color(0, 0, 255);
  } else if (val < THRESHOLD+60) {
    return strip.Color(0, 255, 0);
  } else if (val < THRESHOLD+70) {
    return strip.Color(255, 255, 0);
  } else if (val < THRESHOLD+80) {
    return strip.Color(255, 0, 255);
  } else if (val < THRESHOLD+100) {
    return strip.Color(0, 255, 255);
  } else {
    return strip.Color(255, 0, 0);
  }
}
