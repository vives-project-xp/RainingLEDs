#include <Adafruit_NeoPixel.h>

#define PIN2            2
#define PIN            3   
#define NUMPIXELS      31  

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);

Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRBW + NEO_KHZ800);

  static int blueledPosition = 0;
  static int whiteledPosition = 1;

void setup() {
  strip.begin();
  strip2.begin();
  strip.show(); 
  strip2.show();

}

void cyanRain() {
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
}

void cyanRain2() {

    static int ledPosition = 0;
  strip2.setPixelColor(ledPosition, strip2.Color(0, 0, 0, 0));

  ledPosition++;

  if (ledPosition >= NUMPIXELS) {
    ledPosition = 0;
  }

  strip2.setPixelColor(ledPosition, strip2.Color(0, 0, 255, 0));

  strip2.show();
  
}

void loop() {
  cyanRain();
  cyanRain2();
  delay(75);
}
