#include <Adafruit_NeoPixel.h>

#define PIN 6      // Pin
#define N_LEDS 16  //Number of led in total strips

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
unsigned long noti;

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(50);

  uint32_t c[] = {
    strip.Color(0, 0, 255),
    strip.Color(0, 255, 0),
    strip.Color(0, 255, 255),
    strip.Color(255, 0, 0),
    strip.Color(255, 0, 255),
    strip.Color(255, 255, 0),
    strip.Color(255, 255, 255),
  };


  chase(c,7,30);
  // rainbow(10);
}

void loop() {}

static void chase(uint32_t c[],int N, int wait) {
  int current_color = 0;
  uint16_t i = 0;

  while (true) {
    while (i < N_LEDS) {
      // Serial.println(i);
      strip.setPixelColor(i, c[current_color]);  // Draw new pixel
      strip.setPixelColor(i - 4, 0);             // Erase pixel a few steps back
      strip.show();
      delay(wait);
      i++;
    }

    current_color++;
    if (current_color > N) {
      current_color = 0;
    }

    i = 0;

    for (int a = 4; a > 0; a--) {
      // Serial.println(i);
      strip.setPixelColor(N_LEDS - a, 0);
      strip.setPixelColor(i, c[current_color]);
      i++;
      strip.show();
      delay(wait);
    }
  }
}

boolean checkPossible(int i) {
  if (i >= 0 and i <= 16) {
    return true;
  }
  return false;
}


void rainbow(int wait) {
  while (true) {

    for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
      for (int i = 0; i < strip.numPixels(); i++) {
        int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      }
      strip.show();
      delay(wait);
      if (millis() - noti > 5000) {
        Serial.println("neopixel rainbow with arduino framework");
        noti = millis();
      }
    }
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}