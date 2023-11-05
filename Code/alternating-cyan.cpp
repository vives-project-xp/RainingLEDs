#include <Adafruit_NeoPixel.h>

#define PIN            3 
#define NUMPIXELS      31

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

bool alternateColor = false;

void setup() {
  strip.begin();
  strip.show();
}

void loop() {
  for (int i = 0; i < NUMPIXELS; i++) {
    if (i % 2 == 0) {
      strip.setPixelColor(i, strip.Color(0, 0, 0, 205));
    } else {
      strip.setPixelColor(i, strip.Color(10, 165, 255, 0));
    }
  }

  alternateColor = !alternateColor;
  
  strip.show();
  delay(1000);
}
