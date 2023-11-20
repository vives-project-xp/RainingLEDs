#include <Adafruit_NeoPixel.h>

#define PIN            2
#define PIN2           3
#define NUMPIXELS      31
#define BUTTON         1
#define BUTTON2        0

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRBW + NEO_KHZ800);

boolean oldState = HIGH;
boolean oldState2 = HIGH;
int     mode     = 0;  

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);  
    strip2.setPixelColor(i, color);    
    strip.show();      
    strip2.show();            
    delay(wait);                   
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
    delay(500); // debounce

    if (digitalRead(button) == LOW) {
      if (button == BUTTON) {
        mode = (mode + 1) % 4;  // Increase mode for button 1
      } else if (button == BUTTON2) {
        mode = (mode - 1 + 4) % 4;  // Decrease mode for button 2
      }

      switch (mode) {
        case 0:
          colorWipe(strip.Color(0, 0, 0), 50);
          colorWipe(strip2.Color(0, 0, 0), 50);
          break;
        case 1:
          colorWipe(strip.Color(255, 0, 0), 50);
          colorWipePin2(strip2.Color(255, 0, 0), 50);
          break;
        case 2:
          colorWipe(strip.Color(0, 255, 0), 50);
          colorWipePin2(strip2.Color(0, 255, 0), 50);
          break;
        case 3:
          colorWipe(strip.Color(0, 0, 255), 50);
          colorWipePin2(strip2.Color(0, 0, 255), 50);
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