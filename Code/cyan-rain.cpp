#include <Adafruit_NeoPixel.h>

#define PIN            3   
#define NUMPIXELS      31  

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

  static int blueledPosition = 0;
  static int whiteledPosition = 1;

void setup() {
  strip.begin();
  strip.show(); 
}

void loop() {

  strip.setPixelColor(blueledPosition, strip.Color(0, 0, 0, 0));
  strip.setPixelColor(whiteledPosition, strip.Color(0, 0, 0, 0));

  blueledPosition++;

  if (blueledPosition >= NUMPIXELS) {
    blueledPosition = 0;
  }
  
    whiteledPosition = (blueledPosition + 1) % NUMPIXELS;

  strip.setPixelColor(blueledPosition, strip.Color(0, 0, 0, 255));  
  strip.setPixelColor(whiteledPosition, strip.Color(175, 255, 255, 0));

  strip.show();
  delay(75); 
}
