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

const int MAX_BRIGHTNESS = 60;
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

const Color fillColor = {100, 0, 100, 55};
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
  ledstrip1.setBrightness(30);
  ledstrip2.setBrightness(30);
  ledstrip3.setBrightness(30);
  ledstrip4.setBrightness(30);
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
  else if (currentEffect == "starlight"){
    if (currentEffect != previousEffect) {
      delayTime = Delays::starlight;
    }
    blinkingStarlight(LEDSTRIPS, 200);
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

  } 
  else if (currentEffect == "ripple") {
    if (currentEffect != previousEffect) {
      delayTime = Delays::ripple;
    }
    rippleEffect(LEDSTRIPS, NUM_LEDSTRIPS, {152, 255, 152, 100});
  }
  else if (currentEffect == "other"){
   if (currentEffect != previousEffect) {
      delayTime = Delays::other;
    }
    everyOther(LEDSTRIPS, NUM_LEDSTRIPS, {0, 255, 0, 0});
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
    currentEffect = EFFECTS[sizeof(EFFECTS) - 1];
    return;
  }
  if (index == 0) {
    currentEffect = EFFECTS[sizeof(EFFECTS) - 1];
    return;
  }
  currentEffect = EFFECTS[index - 1];
}