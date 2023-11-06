#include <Adafruit_NeoPixel.h>

#define PIN           3
#define PIN2          2
#define NUM_LEDS      31
#define MOVE_DELAY    200

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_LEDS, PIN2, NEO_GRBW + NEO_KHZ800);

byte ledStates[NUM_LEDS] = {0};

int position = 0;

void setup() {
  strip.begin();
  strip.show();  

    strip2.begin();
    strip2.show();
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);         
    strip.show();                          
    delay(wait);                          
  }
}

void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();
      delay(wait); 
    }
  }
}

void theaterChase2(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2.. 
      strip2.clear(); 
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip2.numPixels(); c += 3) {
         // Set pixel 'c' to value 'color'
        strip2.setPixelColor(c, color);
      }
      strip2.show(); 
      delay(wait); 
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {

  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {

    strip.rainbow(firstPixelHue);
    strip.show(); 
    delay(wait);  
  }
}

void rainbow2(int wait) {

  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {

    strip2.rainbow(firstPixelHue);
    strip2.show(); 
  delay(wait); 
  }
}

void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); 
        uint32_t color2 = strip2.gamma32(strip.ColorHSV(hue)); 

        strip.setPixelColor(c, color);
        strip2.setPixelColor(c, color2); // Set pixel 'c' to value 'color'
      }
      strip.show();
      strip2.show();            
      delay(wait);               
      firstPixelHue += 65536 / 90; 
    }
  }
}

void loop() {
  // Fill along the length of the strip in various colors...
  // colorWipe(strip.Color(255,   0,   0), 50); // Red
  // colorWipe(strip.Color(  0, 255,   0), 50); // Green
  // colorWipe(strip.Color(  0,   0, 255), 50); // Blue

  // Do a theater marquee effect in various colors...
  // theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
  // theaterChase2(strip2.Color(127,   0,   0), 50); // Red, half brightness
  // theaterChase(strip.Color(   0,   0, 127), 50); // Blue, half brightness
  
  rainbow(1);    
  rainbow2(1);         
  // theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
}
