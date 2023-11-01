#include <Adafruit_NeoPixel.h>

#define LED_COUNT 1
#define LED_PIN 18

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned long noti;

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(50);
  Serial.begin(9600);
}


void loop() {
  rainbow(10);
}

void rainbow(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < strip.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(wait);
    if(millis()-noti>5000){
      Serial.println("neopixel rainbow with arduino framework");
      noti=millis();
    }
    
  }
}