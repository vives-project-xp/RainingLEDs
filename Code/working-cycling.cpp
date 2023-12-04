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
#define BRIGHTNESS_MAX 100
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
int current_mode = 0;

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip2.setPixelColor(i, color);
    strip3.setPixelColor(i, color);
    strip4.setPixelColor(i, color);
    teststrip.setPixelColor(i, color);  
    strip.show();
    strip2.show();
    strip3.show();
    strip4.show();
    teststrip.show();
    delay(wait);
  }
}

void rainEffect() {
  int drops[NUM_DROPS] = {0};

  // Initialize drop positions
  for (int i = 0; i < NUM_DROPS; i++) {
    drops[i] = i * (strip.numPixels() / NUM_DROPS);
  }
  while (true) {
    // For each drop...
    for (int i = 0; i < NUM_DROPS; i++) {
      // Turn off the current drop
      strip.setPixelColor(drops[i], strip.Color(0, 0, 0));
      strip2.setPixelColor(drops[i], strip2.Color(0, 0, 0));
      strip3.setPixelColor(drops[i], strip3.Color(0, 0, 0));
      strip4.setPixelColor(drops[i], strip4.Color(0, 0, 0));

      // Generate a new position for the drop
      drops[i] = random(strip.numPixels() - 3);

      // Turn on the new drop
      strip.setPixelColor(drops[i], strip.Color(255, 255, 255));
      strip2.setPixelColor(drops[i], strip2.Color(255, 255, 255));
      strip3.setPixelColor(drops[i], strip3.Color(255, 255, 255));
      strip4.setPixelColor(drops[i], strip4.Color(255, 255, 255));
    }

    strip.show();
    strip2.show();
    strip3.show();
    strip4.show();
    delay(200);  
  }
}

// void rainEffect() {
//   int drops[NUM_DROPS] = {0};

//   // Initialize drop positions
//   for (int i = 0; i < NUM_DROPS; i++) {
//     drops[i] = i * (strip.numPixels() / NUM_DROPS);
//   }
//   while (true) {
//     // For each drop...
//     for (int i = 0; i < NUM_DROPS; i++) {
//       // Turn off the current drop
//       strip.setPixelColor(drops[i], strip.Color(0, 0, 0));
//       strip.setPixelColor(drops[i] + 1, strip.Color(0, 0, 0));
//       strip.setPixelColor(drops[i] + 2, strip.Color(0, 0, 0));

//       // Generate a new position for the drop
//       drops[i] = random(strip.numPixels() - 3);

//       // Turn on the new drop
//       strip.setPixelColor(drops[i], strip.Color(0, 0, 255));
//       strip.setPixelColor(drops[i] + 1, strip.Color(0, 0, 255));
//       strip.setPixelColor(drops[i] + 2, strip.Color(0, 0, 255));
//     }

//     strip.show();
//     delay(500);
// }
// }

void blueWaveSignal(int delayTime) {
  int blueIntensity[strip.numPixels()];

  while (true) {
    for (int i = 0; i < strip.numPixels(); i++) {
      blueIntensity[i] = (sin((millis() / 1000.0) + i * 0.3) + 1) * 127.5;
    }

    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0, 0, blueIntensity[i]));
      strip2.setPixelColor(i, strip.Color(0, 0, blueIntensity[i]));
      strip3.setPixelColor(i, strip.Color(0, 0, blueIntensity[i]));
      strip4.setPixelColor(i, strip.Color(0, 0, blueIntensity[i]));
    }

    strip.show();
    strip2.show();
    strip3.show();
    strip4.show();
    delay(delayTime);

    if(digitalRead(BUTTON) == HIGH){
      mode += 1;
      break;
    }
    if(digitalRead(BUTTON2) == HIGH){
      mode -= 1;
      break;
    }
  }

}

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

void blinkingStarlight(int delayTime, int delayTime2, int delayTime3, int delayTime4) {
  while (true) {
    for (int i = 0; i < strip.numPixels(); i++) {
      if (random(5) == 0) {
        strip.setPixelColor(i, strip.Color(255, 255, 255)); 
      } else {
        strip.setPixelColor(i, strip.Color(0, 0, 0)); 
      }
      strip.show();
      delay(delayTime);
    }

    for (int i = 0; i < strip2.numPixels(); i++) {
      if (random(5) == 0) {
        strip2.setPixelColor(i, strip2.Color(255, 255, 255)); 
      } else {
        strip2.setPixelColor(i, strip2.Color(0, 0, 0)); 
      }
      strip2.show();
      delay(delayTime2);
    }

    for (int i = 0; i < strip3.numPixels(); i++) {
      if (random(5) == 0) {
        strip3.setPixelColor(i, strip3.Color(255, 255, 255)); 
      } else {
        strip3.setPixelColor(i, strip3.Color(0, 0, 0)); 
      }
      strip3.show();
      delay(delayTime3);
    }

    for (int i = 0; i < strip4.numPixels(); i++) {
      if (random(5) == 0) {
        strip4.setPixelColor(i, strip4.Color(255, 255, 255)); 
      } else {
        strip4.setPixelColor(i, strip4.Color(0, 0, 0)); 
      }
      strip4.show();
      delay(delayTime4);
    }
  }
}


// void colorRainbow(int wait) {
//   for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
//     strip.rainbow(firstPixelHue);
//     strip2.rainbow(firstPixelHue);
//     strip3.rainbow(firstPixelHue);
//     strip4.rainbow(firstPixelHue);
//     strip.show();
//     strip2.show();
//     strip3.show();
//     strip4.show();
//     delay(wait);
//   }
// }

void colorRainbow(int wait) {
  static unsigned long lastUpdate = 0;
  static long firstPixelHue = 0;

  // Only update the LEDs if enough time has passed since the last update
  if (millis() - lastUpdate >= wait) {
    lastUpdate = millis();

    strip.rainbow(firstPixelHue);
    strip2.rainbow(firstPixelHue);
    strip3.rainbow(firstPixelHue);
    strip4.rainbow(firstPixelHue);
    strip.show();
    strip2.show();
    strip3.show();
    strip4.show();

    firstPixelHue += 256;
    if (firstPixelHue >= 5*65536) {
      firstPixelHue = 0;
    }
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

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(BUTTON2, INPUT);
  strip.begin();
  strip2.begin();
  strip.show();
  strip2.show();
}

void handleButtonPress(int button) {
  boolean newState = digitalRead(button);

  if (newState == LOW && oldState == HIGH) {
    delay(100); // debounce

    if (digitalRead(button) == LOW) {
      if (button == BUTTON) {
        mode += 1;
        if (mode == 4){
           mode = 1;
        }  // Increase mode for button 1
      } if (button == BUTTON2) {
         mode -= 1;  // Decrease mode for button 2
         if(mode == 0){
           mode = 3;
         }
      }

      switch (mode) {
        case 1:
          colorWipe(strip.Color(255, 0, 0), 50);
          break;
        case 2:
          blueWaveSignal(50);
          break;
        case 3:
          colorWipe(strip.Color(0, 0, 255), 50);
          break;
      }
    }
  }
oldState = newState;
}

void loop() {
  handleButtonPress(BUTTON);
  handleButtonPress(BUTTON2);
}