#include <Adafruit_NeoPixel.h>

#define PIN            2
#define PIN2           3
#define PIN3           4
#define PIN4           5
#define NUMPIXELS      31
#define BUTTON         1
#define BUTTON2        0
#define NUM_DROPS      31
#define TESTPIN        6
#define BRIGHTNESS_MIN 10
#define BRIGHTNESS_MAX 80
#define DEBOUNCE_DELAY 50
#define NUM_MODES 4

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUMPIXELS, PIN3, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(NUMPIXELS, PIN4, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel teststrip = Adafruit_NeoPixel(NUMPIXELS, TESTPIN, NEO_GRBW + NEO_KHZ800);


boolean oldState = HIGH;
boolean oldState2 = HIGH;
int mode = 0;

void setBrightnessSmoothly(Adafruit_NeoPixel &strip, int targetBrightness, int transitionTime) {
  // Set brightness to maximum before transitioning to 0
  strip.setBrightness(BRIGHTNESS_MAX);
  strip.show();
  delay(transitionTime);

  int currentBrightness = strip.getBrightness();
  int brightnessStep = (targetBrightness - currentBrightness > 0) ? 1 : -1;

  for (int i = currentBrightness; i != targetBrightness; i += brightnessStep) {
    strip.setBrightness(i);
    strip.show();
    delay(transitionTime / abs(targetBrightness - currentBrightness));
  }
}

void turnOnRandomLEDs(Adafruit_NeoPixel &strip, int numLEDs) {
  // Turn off all LEDs
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();

  // Turn on new random LEDs
  for (int i = 0; i < numLEDs; i++) {
    int randomIndex = random(strip.numPixels());
    strip.setPixelColor(randomIndex, strip.Color(255, 255, 255));
  }
  strip.show();
}
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip2.setPixelColor(i, color);
    teststrip.setPixelColor(i, color);  
    strip.show();
    strip2.show();
    teststrip.show();
    delay(wait);
  }
}
void rainEffect(int r, int g, int b) {
  int drops[NUM_DROPS] = {0};

  // Initialize drop positions
  for (int i = 0; i < NUM_DROPS; i++) {
    drops[i] = i * (strip.numPixels() / NUM_DROPS) + 7;
    drops[i] = i * (strip2.numPixels() / NUM_DROPS) + 14;
    drops[i] = i * (strip3.numPixels() / NUM_DROPS) + 21;
    drops[i] = i * (strip4.numPixels() / NUM_DROPS) + 28;
  }

  while (true) {
    // For each drop...
    for (int i = 0; i < NUM_DROPS; i++) {
      // Turn off the current drop
      strip.setPixelColor(drops[i], strip.Color(0, 0, 0));
      strip2.setPixelColor(drops[i], strip2.Color(0, 0, 0));
      strip.setPixelColor((drops[i] + 1) % strip.numPixels(), strip.Color(0, 0, 0));
      strip2.setPixelColor((drops[i] + 1) % strip2.numPixels(), strip2.Color(0, 0, 0));
      strip.setPixelColor((drops[i] + 2) % strip.numPixels(), strip.Color(0, 0, 0));
      strip2.setPixelColor((drops[i] + 2) % strip2.numPixels(), strip2.Color(0, 0, 0));
      strip3.setPixelColor(drops[i], strip3.Color(0, 0, 0));
      strip4.setPixelColor(drops[i], strip4.Color(0, 0, 0));
      strip3.setPixelColor((drops[i] + 1) % strip3.numPixels(), strip.Color(0, 0, 0));
      strip4.setPixelColor((drops[i] + 2) % strip4.numPixels(), strip.Color(0, 0, 0));
      strip3.setPixelColor((drops[i] + 2) % strip3.numPixels(), strip2.Color(0, 0, 0));
      strip4.setPixelColor((drops[i] + 2) % strip4.numPixels(), strip2.Color(0, 0, 0));
// Generate a new position for the drop
      drops[i] = (drops[i] + 1) % strip.numPixels();

      // Turn on the new drop
      strip.setPixelColor(drops[i], strip.Color(r, g, b));
      strip2.setPixelColor(drops[i], strip2.Color(r, g, b));
      strip.setPixelColor(drops[i] + 1, strip.Color(r, g, b));
      strip2.setPixelColor(drops[i] + 1, strip2.Color(r, g, b));
      strip.setPixelColor(drops[i] + 2, strip.Color(r, g, b));
      strip2.setPixelColor(drops[i] + 2, strip2.Color(r, g, b));
      strip3.setPixelColor(drops[i], strip3.Color(r, g, b));
      strip4.setPixelColor(drops[i], strip4.Color(r, g, b));
      strip3.setPixelColor(drops[i] + 1, strip3.Color(r, g, b));
      strip4.setPixelColor(drops[i] + 1, strip4.Color(r, g, b));
      strip3.setPixelColor(drops[i] + 2, strip3.Color(r, g, b));
      strip4.setPixelColor(drops[i] + 2, strip4.Color(r, g, b));

    }

    strip.show();
    strip2.show();
    strip3.show();
    strip4.show();
    delay(110);
  }
}

void blueWaveSignal(int delayTime) {
  while (true) {
    for (int i = 0; i < strip.numPixels(); i++) {
      int blueIntensity = (sin((millis() / 1000.0) + i * 0.3) + 1) * 127.5;
      strip.setPixelColor(i, strip.Color(0, 0, blueIntensity));
      strip2.setPixelColor(i, strip.Color(0, 0, blueIntensity));
      strip3.setPixelColor(i, strip.Color(0, 0, blueIntensity));
      strip4.setPixelColor(i, strip.Color(0, 0, blueIntensity));
    }
    strip.show();
    strip2.show();
    strip3.show();
    strip4.show();
    delay(delayTime);
  }
} 

// void blueWaveSignal(int delayTime) {
//   for (int i = 0; i < strip.numPixels(); i++) {
//     int blueIntensity = (sin((millis() / 1000.0) + i * 0.3) + 1) * 127.5;
//     strip.setPixelColor(i, strip.Color(0, 0, blueIntensity));
//     strip2.setPixelColor(i, strip.Color(0, 0, blueIntensity));
//   }
//   strip.show();
//   strip2.show();
//   delay(delayTime);
// }

void blueCyanWhiteWave(int delayTime) {
  while (true) {
    for (int i = 0; i < strip.numPixels(); i++) {
      int blueIntensity = (sin((millis() / 1000.0) + i * 0.3) + 1) * 127.5;
      int cyanIntensity = (sin((millis() / 1000.0) + i * 0.3 + 2) + 1) * 127.5;
      int whiteIntensity = (sin((millis() / 1000.0) + i * 0.3 + 4) + 1) * 127.5;

      strip.setPixelColor(i, strip.Color(cyanIntensity, blueIntensity, whiteIntensity)); 
    }
    strip.show();
    delay(delayTime);
  }
}

void Sunrise(int delayTime) {
  while (true) {
    for (int i = 0; i < strip.numPixels(); i++) {

      int blueIntensity = (sin((millis() / 1000.0) + i * 0.3) + 1) * 127.5;

      int redIntensity = 0;
      int greenIntensity = 0;

      int gradientRange = 255;

      redIntensity = map(blueIntensity, 0, 255, 0, gradientRange);
      greenIntensity = map(blueIntensity, 0, 255, 0, gradientRange);

      strip.setPixelColor(i, strip.Color(redIntensity, greenIntensity, blueIntensity));
      strip2.setPixelColor(i, strip2.Color(redIntensity, greenIntensity, blueIntensity));
      strip3.setPixelColor(i, strip3.Color(redIntensity, greenIntensity, blueIntensity));
      strip4.setPixelColor(i, strip4.Color(redIntensity, greenIntensity, blueIntensity));
    }
    strip.show();
    strip2.show();
    strip3.show();
    strip4.show();
    delay(delayTime);
  }
}

void colorfulExplosion(int wait) {
  int middle = NUMPIXELS / 2;

  for(int i = 0; i < middle; i++) {
    uint8_t r = map(i, 0, middle, 255, 0);
    uint8_t g = 0;
    uint8_t b = map(i, 0, middle, 0, 255);
    uint8_t w = 0;
    uint32_t color = strip.Color(r, g, b, w);

    strip.setPixelColor(middle + i, color);
    strip.setPixelColor(middle - i, color);
    strip2.setPixelColor(middle + i, color);
    strip2.setPixelColor(middle - i, color);

    strip.show();
    strip2.show();
    delay(wait);
  }

  for (int i = 0; i < middle; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.setPixelColor(NUMPIXELS - i - 1, strip.Color(0, 0, 0));
    strip2.setPixelColor(i, strip.Color(0, 0, 0));
    strip2.setPixelColor(NUMPIXELS - i - 1, strip.Color(0, 0, 0));

    strip.show();
    strip2.show();
    delay(wait);
  }
} 

void blinkingStarlight(int delayTime, int delayTime2, int delayTime3, int delayTime4) {
  while (true) {
    turnOnRandomLEDs(strip, 5);   // Adjust the number of LEDs as needed
    setBrightnessSmoothly(strip, 0, 100);  // Smoothly transition to brightness 0
    delay(delayTime);

    turnOnRandomLEDs(strip3, 5);
    setBrightnessSmoothly(strip3, 0, 100);
    delay(delayTime3);

    turnOnRandomLEDs(strip2, 5);
    setBrightnessSmoothly(strip2, 0, 100);
    delay(delayTime2);

    turnOnRandomLEDs(strip4, 5);
    setBrightnessSmoothly(strip4, 0, 100);
    delay(delayTime4);
  }
}

void colorWipePin2(uint32_t color, int wait) {
  for(int i=0; i<strip2.numPixels(); i++) {
    strip2.setPixelColor(i, color);
    strip2.show();
    delay(wait);
  }
}

void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    strip.rainbow(firstPixelHue);
    strip2.rainbow(firstPixelHue);
    strip.show();
    strip2.show();
    delay(wait);
  }
}

void cyanRain() {

  static int blueledPosition = 0;
  static int whiteledPosition = 1;


while (true)
{
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
}

void cyanRainPin2() {

  static int ledPosition = 0;
  strip2.setPixelColor(ledPosition, strip2.Color(0, 0, 0, 0));

  ledPosition++;

  if (ledPosition >= NUMPIXELS) {
    ledPosition = 0;
  }

  strip2.setPixelColor(ledPosition, strip2.Color(0, 0, 255, 0));

  strip2.show();
}

void alternatingCyan() {

  static int cycle = 0;
  strip.clear();
  strip2.clear();

  if (cycle % 2 == 0) {
    for (int i = 0; i < NUMPIXELS; i++) {
      if (i % 2 == 0) {
        strip.setPixelColor(i, strip.Color(0, 0, 0, 255));
        strip2.setPixelColor(i, strip2.Color(0, 0, 0, 255));
      } else {
        strip.setPixelColor(i, strip.Color(10, 165, 255, 0));
        strip2.setPixelColor(i, strip2.Color(10, 165, 255, 0));
      }
    }
  } else {
    for (int i = 0; i < NUMPIXELS; i++) {
      if (i % 2 == 0) {
        strip.setPixelColor(i, strip.Color(10, 165, 255, 0));
        strip2.setPixelColor(i, strip.Color(10, 165, 255, 0));
      } else {
        strip.setPixelColor(i, strip.Color(0, 0, 0, 255));
        strip2.setPixelColor(i, strip2.Color(0, 0, 0, 255));
      }
    }
  }
}

void simulateRain() {

  int MAX_RAINDROPS = 6;
  int raindropPositions1[MAX_RAINDROPS];
  int raindropPositions2[MAX_RAINDROPS];

  strip.clear();
  strip2.clear();

  // Clear the previous raindrops
  for (int i = 0; i < MAX_RAINDROPS; ++i) {
    strip.setPixelColor(raindropPositions1[i], strip.Color(0, 0, 0, 0));
    strip2.setPixelColor(raindropPositions2[i], strip2.Color(0, 0, 0, 0));
  }

  // Move raindrops down
  for (int i = 0; i < MAX_RAINDROPS; ++i) {
    raindropPositions1[i] = (raindropPositions1[i] + 1) % NUMPIXELS;
    raindropPositions2[i] = (raindropPositions2[i] + 1) % NUMPIXELS;
  }

  // Set the color of the new raindrops
  for (int i = 0; i < MAX_RAINDROPS; ++i) {
    strip.setPixelColor(raindropPositions1[i], strip.Color(0, 0, 255, 0)); // Blue color
    strip2.setPixelColor(raindropPositions2[i], strip2.Color(0, 0, 255, 0)); // Blue color
  }

  // Show the updated raindrops
  strip.show();
  strip2.show();
}

void alternate() {

  bool alternateColor = false;

  for (int i = 0; i < NUMPIXELS; i++) {
    if (i % 2 == 0) {
      strip.setPixelColor(i, strip.Color(0, 0, 0, 205));
      strip2.setPixelColor(i, strip2.Color(0, 0, 0, 205));
    } else {
      strip.setPixelColor(i, strip.Color(10, 165, 255, 0));
      strip2.setPixelColor(i, strip2.Color(0, 0, 0, 205));
    }
  }

  alternateColor = !alternateColor;

  strip.show();
  strip2.show();
  delay(1000);
}

void discoLight(int delayTime) {
  while (true) {
    uint32_t randomColor = strip.Color(random(256), random(256), random(256));

    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, randomColor);
    }

    strip.show();
    delay(delayTime);
  }
}

void northernLights() {

  static int position1 = 0;
  static int position2 = 15;

  strip.setPixelColor(position1, strip.Color((0), random(255), (0), (0)));
  strip2.setPixelColor(position2, strip2.Color((0), random(255), (0), (0)));

  position1 = (position1 + 1) % NUMPIXELS;
  position2 = (position2 + 1) % NUMPIXELS;

  strip.show();
  strip2.show();
}

void seaWaveEffect() {
  static uint16_t t = 0;

  for (int i = 0; i < strip.numPixels(); i++) {
    // Calculate brightness based on a simple sine-like function
    uint8_t brightness = BRIGHTNESS_MIN + sin((i + t) * 0.2) * (BRIGHTNESS_MAX - BRIGHTNESS_MIN);

    // Set the color of each pixel based on the brightness
    uint32_t color = strip.Color(brightness, 0, 0);

    strip.setPixelColor(i, color);
  }

  strip.show();
  
  // Increment time for animation
  t++;
  
  // Add a small delay to control the speed of the wave
  delay(50);
}

void handleButtonPress(int button) {
  static unsigned long lastDebounceTime = 0;
  boolean newState = digitalRead(button);
  unsigned long currentTime = millis();

  if (currentTime - lastDebounceTime > DEBOUNCE_DELAY) {
    if (newState != oldState) {
      // Button state has changed, debounce it
      lastDebounceTime = currentTime;
      oldState = newState;
      if (newState == LOW) {
        // Button is pressed
        if (button == BUTTON) {
          mode = (mode + 1) % NUM_MODES;  // Increase mode for button 1
        } else if (button == BUTTON2) {
          mode = (mode - 1 + NUM_MODES) % NUM_MODES;  // Decrease mode for button 2
        }

      switch (mode) {
        case 1:
          break;
      }
    }
   }
  }
  oldState = newState;
}

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(BUTTON2, INPUT);
  strip.begin();
  strip2.begin();
  strip.show();
  strip2.show();
}

void loop() {
  handleButtonPress(BUTTON);
  handleButtonPress(BUTTON2);
}