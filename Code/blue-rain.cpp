#include <Adafruit_NeoPixel.h>

#define PIN            2   
#define NUMPIXELS      31 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); 
}

void loop() {
  static int ledPosition = 0;

  strip.setPixelColor(ledPosition, strip.Color(0, 0, 0, 0));

  ledPosition++;

  if (ledPosition >= NUMPIXELS) {
    ledPosition = 0;
  }

  strip.setPixelColor(ledPosition, strip.Color(0, 0, 255, 0));

  strip.show();
  delay(75); 
}
