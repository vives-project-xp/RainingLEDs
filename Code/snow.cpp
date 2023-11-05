#include <Adafruit_NeoPixel.h>

#define PIN           3
#define NUM_LEDS      31
#define MOVE_DELAY    200

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

byte ledStates[NUM_LEDS] = {0};

int position = 0;

void setup() {
  strip.begin();
  strip.show(); 
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0, 0));
  }
  
  strip.setPixelColor(position, strip.Color(0, 0, 0, 255));
  strip.setPixelColor((position + 1) % NUM_LEDS, strip.Color(0, 0, 0, 0));
  strip.setPixelColor((position + 2) % NUM_LEDS, strip.Color(0, 0, 0, 0));
  strip.setPixelColor((position + 3) % NUM_LEDS, strip.Color(0, 0, 0, 255));

  strip.show();
  delay(MOVE_DELAY);

  position = (position + 1) % NUM_LEDS;
}
