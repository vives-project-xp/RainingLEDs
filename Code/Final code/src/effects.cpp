#include "effects.h"

void initRain(Adafruit_NeoPixel ledstrips[], int num_ledstrips, int drops[], int numDrops){
  for (int i = 0; i < numDrops; i++) {
    drops[i] = i * (ledstrips[0].numPixels() / numDrops) + 7;
    drops[i] = i * (ledstrips[1].numPixels() / numDrops) + 14;
    drops[i] = i * (ledstrips[2].numPixels() / numDrops) + 21;
    drops[i] = i * (ledstrips[3].numPixels() / numDrops) + 28;
  }
}

void rainEffect(Adafruit_NeoPixel ledstrips[], int num_ledstrips, Color color, int drops[], int numDrops, int dropLength){
  for (int i = 0; i < numDrops; i++) {
    fillAll(ledstrips, num_ledstrips, {0,0,0,0});
    drops[i] = (drops[i] + 1) % ledstrips[0].numPixels();
    for (int j = 0; j < dropLength; j++) {
      ledstrips[0].setPixelColor(drops[i] + j, color.r, color.g, color.b, color.w);
      ledstrips[1].setPixelColor(drops[i] + j, color.r, color.g, color.b, color.w);
      ledstrips[2].setPixelColor(drops[i] + j, color.r, color.g, color.b, color.w);
      ledstrips[3].setPixelColor(drops[i] + j, color.r, color.g, color.b, color.w);
    }
  }
}

void waveFade(Adafruit_NeoPixel ledstrips[], int num_ledstrips, String color){
  for (int i = 0; i < ledstrips[0].numPixels(); i++) {
    int colorIntensity = (sin((millis() / 1000.0) + i * 0.3) + 1) * 127.5;
    if (color == "red"){
      setPixelColorAll(ledstrips, num_ledstrips, i, {colorIntensity, 0, 0, 0});
    }
    else if (color == "green") {
      setPixelColorAll(ledstrips, num_ledstrips, i, {0, colorIntensity, 0, 0});
    }
    else if (color == "blue") {
      setPixelColorAll(ledstrips, num_ledstrips, i, {0, 0, colorIntensity, 0});
    }
    else if (color == "white") {
      setPixelColorAll(ledstrips, num_ledstrips, i, {0, 0, 0, colorIntensity});
    }
    else {
      setPixelColorAll(ledstrips, num_ledstrips, i, {0, 0, 0, 0});
    }
  }
}

void sunriseEffect(Adafruit_NeoPixel ledstrips[], int num_ledstrips){
  for (int i = 0; i < ledstrips[0].numPixels(); i++) {
    int gradientRange = 255;
    int blueIntensity = (sin((millis() / 1000.0) + i * 0.3) + 1) * 127.5;
    int redIntensity = map(blueIntensity, 0, 255, 0, gradientRange);
    int greenIntensity = map(blueIntensity, 0, 255, 0, gradientRange);
    setPixelColorAll(ledstrips, num_ledstrips, i, {redIntensity, greenIntensity, blueIntensity, 0});
  }
}

void rainbowEffect(Adafruit_NeoPixel ledstrips[], int num_ledstrips, long hue){
  for (int j = 0; j < num_ledstrips; j++){
    ledstrips[j].rainbow(hue);
  }
}

void setPixelColorAll(Adafruit_NeoPixel ledstrips[], int num_ledstrips, int pixel, Color color){
    for (int i = 0; i < num_ledstrips; i++) {
    ledstrips[i].setPixelColor(pixel, color.r, color.g, color.b, color.w);
  }
}

void fillAll(Adafruit_NeoPixel ledstrips[], int num_ledstrips, Color color){
  for (int i = 0; i < num_ledstrips; i++) {
    ledstrips[i].fill(ledstrips[i].Color(color.r, color.g, color.b, color.w), 0, ledstrips[i].numPixels());
  }
}