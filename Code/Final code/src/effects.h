#pragma once

// Include libraries
#include <Adafruit_NeoPixel.h>

// Define effects
const String EFFECTS[] = {
  "rainEffect", 
  "fill",
  "waveFade",
  "blinkingStarlight",
  "sunrise",
  "rainbow",
  "meteor",
  "rippleEffect",
  "everyOther"
};

// Define delays for each effect
enum Delays {
  fill = 100,
  rainEffect = 100,
  waveFade = 100,
  blinkingStarlight = 100,
  sunrise = 100,
  rainbow = 100,
  rippleEffect = 100,
  other = 100,
};

// Define custom types
struct Color {
  int r;
  int g;
  int b;
  int w;
};

// Function prototypes
void rainEffects(Adafruit_NeoPixel ledstrips[], int num_ledstrips, Color color, int drops[], int numDrops, int dropLength = 3); 
void waveFadeEffect(Adafruit_NeoPixel ledstrips[], int num_ledstrips, String color); 
void sunriseEffect(Adafruit_NeoPixel ledstrips[], int num_ledstrips); 
void rainbowEffect(Adafruit_NeoPixel ledstrips[], int num_ledstrips, long &hue); 
void setPixelColorAll(Adafruit_NeoPixel ledstrips[], int num_ledstrips, int pixel, Color color);
void fillAll(Adafruit_NeoPixel ledstrips[], int num_ledstrips, Color color);
void turnOnRandomLEDs(Adafruit_NeoPixel ledstrips[], int numLEDs); 
void blinkingStarlights(Adafruit_NeoPixel ledstrips[], int delayTime); 
void rippleEffects(Adafruit_NeoPixel ledstrips[], int num_ledstrips, Color color); 
void everyOther(Adafruit_NeoPixel ledstrips[], int num_ledstrips, Color color); 
