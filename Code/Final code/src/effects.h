#pragma once

// Include libraries
#include <Adafruit_NeoPixel.h>

// Define effects
const String EFFECTS[] = {
  "rain", 
  "fill",
  "wave",
  "starlight",
  "sunrise",
  "rainbow",
  "meteor",
  "ripple",
  "other"

};

// Define delays for each effect
enum Delays {
  fill = 100,
  rain = 100,
  wave = 100,
  starlight = 100,
  sunrise = 100,
  rainbow = 100,
  ripple = 100,
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
void rainEffect(Adafruit_NeoPixel ledstrips[], int num_ledstrips, Color color, int drops[], int numDrops, int dropLength = 3);
void waveFade(Adafruit_NeoPixel ledstrips[], int num_ledstrips, String color);
void sunriseEffect(Adafruit_NeoPixel ledstrips[], int num_ledstrips);
void rainbowEffect(Adafruit_NeoPixel ledstrips[], int num_ledstrips, long &hue);
void setPixelColorAll(Adafruit_NeoPixel ledstrips[], int num_ledstrips, int pixel, Color color);
void fillAll(Adafruit_NeoPixel ledstrips[], int num_ledstrips, Color color);
void turnOnRandomLEDs(Adafruit_NeoPixel ledstrips[], int numLEDs);
void blinkingStarlight(Adafruit_NeoPixel ledstrips[], int delayTime);
void rippleEffect(Adafruit_NeoPixel ledstrips[], int num_ledstrips, Color color);
void everyOther(Adafruit_NeoPixel ledstrips[], int num_ledstrips, Color color);
