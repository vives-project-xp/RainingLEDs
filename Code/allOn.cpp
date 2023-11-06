#include <Adafruit_NeoPixel.h>

#define PIN            2
#define PIN2           3
#define NUMPIXELS      31

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRBW + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
}

void loop() {
  for (int ledPosition = 0; ledPosition < NUMPIXELS; ledPosition++) {
    strip.setPixelColor(ledPosition, strip.Color(0, 0, 255, 0));
    strip2.setPixelColor(ledPosition, strip2.Color(0, 0, 255, 0));
  }
  
  strip.show();
  strip2.show();
  delay(1000);
}