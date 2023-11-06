#include <Adafruit_NeoPixel.h>

#define PIN            2
#define PIN2           3
#define NUMPIXELS      31
#define BUTTON         1

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUMPIXELS, PIN2, NEO_GRBW + NEO_KHZ800);

boolean oldState = HIGH;
int     mode     = 0;  

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);      
    strip.show();                  
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
  strip.begin();
  strip2.begin();
  strip.show();
  strip2.show();
}

void loop() {
  boolean newState = digitalRead(BUTTON);

  if((newState == LOW) && (oldState == HIGH)) {
    delay(20);
    newState = digitalRead(BUTTON);
    if(newState == LOW) { 
      if(++mode > 8) mode = 0;
      switch(mode) {          
        case 0:
          colorWipe(strip.Color(  0,   0,   0), 50);
          colorWipePin2(strip2.Color(  0,   0,   0), 50);
          break;
        case 1:
          colorWipe(strip.Color(255,   0,   0), 50);
          colorWipe(strip2.Color(255,   0,   0), 50);
          break;
        case 2:
          colorWipe(strip.Color(  0, 255,   0), 50);
          colorWipe(strip2.Color(  0, 255,   0), 50);
          break;
        case 3:
          colorWipe(strip.Color(  0,   0, 255), 50);
          colorWipe(strip2.Color(  0,   0, 255), 50);
          break;
        case 4:
            cyanRain();
            cyanRainPin2();
            delay(75);
          break;
        case 5:
          alternatingCyan();
          delay(75);
          break;
      }
    }
  }

  oldState = newState;
}
