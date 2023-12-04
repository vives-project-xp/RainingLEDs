// void turnOnRandomLEDs(Adafruit_NeoPixel &strip, int numLEDs) {
//   for (int i = 0; i < strip.numPixels(); i++) {
//     strip.setPixelColor(i, strip.Color(0, 0, 0));
//   }
//   strip.show();

//   for (int i = 0; i < numLEDs; i++) {
//     int randomIndex = random(strip.numPixels());
//     strip.setPixelColor(randomIndex, strip.Color(255, 255, 255));
//   }
//   strip.show();
// }
// void colorWipe(uint32_t color, int wait) {
//   for(int i=0; i<strip.numPixels(); i++) {
//     strip.setPixelColor(i, color);
//     strip2.setPixelColor(i, color);
//     teststrip.setPixelColor(i, color);  
//     strip.show();
//     strip2.show();
//     teststrip.show();
//     delay(wait);
//   }
// }

// void colorfulExplosion(int wait) {
//   int middle = NUMPIXELS / 2;

//   for(int i = 0; i < middle; i++) {
//     uint8_t r = map(i, 0, middle, 255, 0);
//     uint8_t g = 0;
//     uint8_t b = map(i, 0, middle, 0, 255);
//     uint8_t w = 0;
//     uint32_t color = strip.Color(r, g, b, w);

//     strip.setPixelColor(middle + i, color);
//     strip.setPixelColor(middle - i, color);
//     strip2.setPixelColor(middle + i, color);
//     strip2.setPixelColor(middle - i, color);

//     strip.show();
//     strip2.show();
//     delay(wait);
//   }

//   for (int i = 0; i < middle; i++) {
//     strip.setPixelColor(i, strip.Color(0, 0, 0));
//     strip.setPixelColor(NUMPIXELS - i - 1, strip.Color(0, 0, 0));
//     strip2.setPixelColor(i, strip.Color(0, 0, 0));
//     strip2.setPixelColor(NUMPIXELS - i - 1, strip.Color(0, 0, 0));

//     strip.show();
//     strip2.show();
//     delay(wait);
//   }
// } 

// void blinkingStarlight(int delayTime, int delayTime2, int delayTime3, int delayTime4) {
//   while (continueEffects) {
//     turnOnRandomLEDs(strip, 5);   // Adjust the number of LEDs as needed
//     setBrightnessSmoothly(strip, 0, 100);  // Smoothly transition to brightness 0
//     delay(delayTime);

//     turnOnRandomLEDs(strip3, 5);
//     setBrightnessSmoothly(strip3, 0, 100);
//     delay(delayTime3);

//     turnOnRandomLEDs(strip2, 5);
//     setBrightnessSmoothly(strip2, 0, 100);
//     delay(delayTime2);

//     turnOnRandomLEDs(strip4, 5);
//     setBrightnessSmoothly(strip4, 0, 100);
//     delay(delayTime4);
//   }
// }

// void colorWipePin2(uint32_t color, int wait) {
//   for(int i=0; i<strip2.numPixels(); i++) {
//     strip2.setPixelColor(i, color);
//     strip2.show();
//     delay(wait);
//   }
// }

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "effects.h"

#define PIN_LEDSTRIP1 2
#define PIN_LEDSTRIP2 3
#define PIN_LEDSTRIP3 4
#define PIN_LEDSTRIP4 5
#define PIN_BUTTON_WHITE 1
#define PIN_BUTTON_RED 0

const int MIN_BRIGHTNESS = 10;

const int MAX_BRIGHTNESS = 80;
const int NUMPIXELS = 60;
const int DEBOUNCE_DELAY = 50;

Adafruit_NeoPixel ledstrip1 = Adafruit_NeoPixel(NUMPIXELS, PIN_LEDSTRIP1, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel ledstrip2 = Adafruit_NeoPixel(NUMPIXELS, PIN_LEDSTRIP2, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel ledstrip3 = Adafruit_NeoPixel(NUMPIXELS, PIN_LEDSTRIP3, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel ledstrip4 = Adafruit_NeoPixel(NUMPIXELS, PIN_LEDSTRIP4, NEO_GRBW + NEO_KHZ800);

Adafruit_NeoPixel LEDSTRIPS[] = {ledstrip1, ledstrip2, ledstrip3, ledstrip4};
int NUM_LEDSTRIPS = 4;

int cycle = 0;
String currentEffect = EFFECTS[0];
String previousEffect = EFFECTS[0];
int delayTime = 0;
bool redButtonState = false;
bool redButtonPreviousState = false;
bool whiteButtonState = false;
bool whiteButtonPreviousState = false;

const Color fillColor = {0, 0, 0, 255};
const int dropAmount = 31; 
const int dropLength = 3; 
const String waveColor = "blue"; 

int drops[dropAmount] = {0}; 
long hue = 0;


int GetEffectIndex(String effect);
void SwitchToNextEffect();
void SwitchToPreviousEffect();

TaskHandle_t redButtonTask, whiteButtonTask;

void redButtonThread(void *pvParameters) {
  while (1) {
    bool currentState = digitalRead(PIN_BUTTON_RED);
    vTaskDelay(10 / portTICK_PERIOD_MS);

    if (currentState != redButtonState) {
      redButtonState = currentState;
      if (currentState == HIGH) {
        SwitchToNextEffect();
      }
    }
  }
}

void whiteButtonThread(void *pvParameters) {
  while (1) {
    bool currentState = digitalRead(PIN_BUTTON_WHITE);
    vTaskDelay(10 / portTICK_PERIOD_MS); 

    if (currentState != whiteButtonState) {
      whiteButtonState = currentState;
      if (currentState == HIGH) {
        SwitchToPreviousEffect();
      }
    }
  }
}

void setup() {
  pinMode(PIN_BUTTON_RED, INPUT);
  pinMode(PIN_BUTTON_WHITE, INPUT);

  xTaskCreate(redButtonThread, "RedButtonTask", 1000, NULL, 1, &redButtonTask);
  xTaskCreate(whiteButtonThread, "WhiteButtonTask", 1000, NULL, 1, &whiteButtonTask);
  ledstrip1.begin();
  ledstrip2.begin();
  ledstrip3.begin();
  ledstrip4.begin();
  ledstrip1.setBrightness(50);
  ledstrip2.setBrightness(50);
  ledstrip3.setBrightness(50);
  ledstrip4.setBrightness(50);
  fillAll(LEDSTRIPS, NUM_LEDSTRIPS, {0, 0, 0, 0});
  ledstrip1.show();
  ledstrip2.show();
  ledstrip3.show();
  ledstrip4.show();
}

void loop() {
  if (currentEffect == "rain") {
    
    if (currentEffect != previousEffect) {
      delayTime = Delays::rain;
      initRain(LEDSTRIPS, NUM_LEDSTRIPS, drops, dropAmount);
    }
    rainEffect(LEDSTRIPS, NUM_LEDSTRIPS, {0, 0, 255, 0}, drops, dropAmount, dropLength);
  }
  else if (currentEffect == "fill") {
    fillAll(LEDSTRIPS, NUM_LEDSTRIPS, fillColor);
  }
  else if (currentEffect == "wave") {
    if (currentEffect != previousEffect) {
      delayTime = Delays::wave;
    }
    waveFade(LEDSTRIPS, NUM_LEDSTRIPS, waveColor);
  }
  else if (currentEffect == "sunrise") {
    if (currentEffect != previousEffect) {
      delayTime = Delays::sunrise;
    }
    sunriseEffect(LEDSTRIPS, NUM_LEDSTRIPS);
  }
  else if (currentEffect == "rainbow") {
    if (currentEffect != previousEffect) {
      delayTime = Delays::rainbow;
      hue = 0;
    }
    rainbowEffect(LEDSTRIPS, NUM_LEDSTRIPS, hue);
    if (hue < 5*65536){
      hue += 256;
    } else {
      hue = 0;
    }
  }
  else {
    fillAll(LEDSTRIPS, NUM_LEDSTRIPS, {0,0,0,0});
    delayTime = 0;
  }
  for (int i = 0; i < NUM_LEDSTRIPS; i++) {
    LEDSTRIPS[i].show();
  }
  
}

int GetEffectIndex(String effect) {
  for (int i = 0; i < sizeof(EFFECTS); i++) {
    if (EFFECTS[i] == effect) {
      return i;
    }
  }
  return -1;
}

void SwitchToNextEffect() {
  int index = GetEffectIndex(currentEffect);
  if (index == -1) {
    currentEffect = EFFECTS[0];
    return;
  }
  if (index == sizeof(EFFECTS) - 1) {
    currentEffect = EFFECTS[0];
    return;
  }
  currentEffect = EFFECTS[index + 1];
}

void SwitchToPreviousEffect() {
  int index = GetEffectIndex(currentEffect);
  if (index == -1) {
    currentEffect = EFFECTS[0];
    return;
  }
  if (index == 0) {
    currentEffect = EFFECTS[sizeof(EFFECTS) - 1];
    return;
  }
  currentEffect = EFFECTS[index - 1];
}