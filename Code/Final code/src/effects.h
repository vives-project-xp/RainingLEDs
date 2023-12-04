#pragma once

// Include libraries
#include <Adafruit_NeoPixel.h>

// Define effects
const String EFFECTS[] = {
  "rain", 
  "fill",
  "wave",
  "sunrise",
  "rainbow",
};

// Define delays for each effect
enum Delays {
  fill = 100,
  rain = 100,
  wave = 100,
  sunrise = 100,
  rainbow = 100,
};

// Define custom types
struct Color {
  int r;
  int g;
  int b;
  int w;
};

// Function prototypes
void initRain(Adafruit_NeoPixel ledstrips[], int num_ledstrips, int drops[], int numDrops);
void rainEffect(Adafruit_NeoPixel ledstrips[], int num_ledstrips, Color color, int drops[], int numDrops, int dropLength = 3);
void waveFade(Adafruit_NeoPixel ledstrips[], int num_ledstrips, String color);
void sunriseEffect(Adafruit_NeoPixel ledstrips[], int num_ledstrips);
void rainbowEffect(Adafruit_NeoPixel ledstrips[], int num_ledstrips, long hue);
void setPixelColorAll(Adafruit_NeoPixel ledstrips[], int num_ledstrips, int pixel, Color color);
void fillAll(Adafruit_NeoPixel ledstrips[], int num_ledstrips, Color color);