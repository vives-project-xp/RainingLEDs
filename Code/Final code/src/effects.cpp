#include "effects.h"

void turnOnRandomLEDs(Adafruit_NeoPixel &strip, int numLEDs) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();

  for (int i = 0; i < numLEDs; i++) {
    int randomIndex = random(strip.numPixels());
    strip.setPixelColor(randomIndex, strip.Color(255, 255, 255));
  }
  strip.show();
}

void blinkingStarlights(Adafruit_NeoPixel ledstrips[], int delayTime) {
  static unsigned long previousMillis = 0;
  static int currentIndex = 0;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= delayTime) {
    turnOnRandomLEDs(ledstrips[currentIndex], 8);
    previousMillis = currentMillis;

    currentIndex++;
    if (currentIndex >= 4) {
      currentIndex = 0;
    }
  }
}

void rainEffects(Adafruit_NeoPixel ledstrips[], int num_ledstrips, Color color, int drops[], int numDrops, int dropLength){
  int offsets[] = {0, 50, 100, 150}; // Add an offset for each LED strip

  for (int i = 0; i < numDrops; i++) {
    fillAll(ledstrips, num_ledstrips, {0,0,0,0});
    drops[i] = (drops[i] + 1) % ledstrips[0].numPixels();

    for (int j = 0; j < dropLength; j++) {
      for (int k = 0; k < num_ledstrips; k++) {
        int position = (drops[i] + j + offsets[k]) % ledstrips[k].numPixels();
        ledstrips[k].setPixelColor(position, color.r, color.g, color.b, color.w);
      }
    }
  }
}

void waveFadeEffect(Adafruit_NeoPixel ledstrips[], int num_ledstrips, String color){
  for (int i = 0; i < ledstrips[0].numPixels(); i++) {
    int colorIntensity = (sin((millis() / 1000.0) + i * 0.3) + 1) * 127.5 * 0.5;
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

void rainbowEffect(Adafruit_NeoPixel ledstrips[], int num_ledstrips, long &hue) {
  for (int j = 0; j < num_ledstrips; j++) {
    for (int i = 0; i < ledstrips[j].numPixels(); i++) {
      int pixelHue = (i * 65536 / ledstrips[j].numPixels()) + hue;
      ledstrips[j].setPixelColor(i, ledstrips[j].gamma32(ledstrips[j].ColorHSV(pixelHue)));
    }
  }
  hue += 256;  
}

void rippleEffects(Adafruit_NeoPixel ledstrips[], int num_ledstrips, Color color) {
  static int rippleSize = 0;
  int maxRippleSize = ledstrips[0].numPixels() / 2;

  fillAll(ledstrips, num_ledstrips, {0, 0, 0, 0});

  for (int i = 0; i < rippleSize; i++) {
    int centerPixel = ledstrips[0].numPixels() / 2;
    int innerPixel = (centerPixel - i + ledstrips[0].numPixels()) % ledstrips[0].numPixels();
    int outerPixel = (centerPixel + i) % ledstrips[0].numPixels();

    Color innerColor = color;
    Color outerColor = color;

    setPixelColorAll(ledstrips, num_ledstrips, innerPixel, innerColor);
    setPixelColorAll(ledstrips, num_ledstrips, outerPixel, outerColor);
  }

  rippleSize = (rippleSize + 1) % (maxRippleSize + 1);
}


// void everyOther(Adafruit_NeoPixel ledstrips[], int num_ledstrips, Color color) {
//   static int position = 0;
//   int change = 2;

//   for (int i = 0; i < num_ledstrips; i++) {
//     setPixelColorAll(ledstrips, num_ledstrips, position, color);
//   }

//   position = (position + change) % ledstrips[0].numPixels();
// }

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
