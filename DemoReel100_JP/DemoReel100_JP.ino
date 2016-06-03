#include "FastLED.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    3
#define CLK_PIN   4
#define LED_TYPE    APA102
#define COLOR_ORDER RGB
#define NUM_LEDS    256
CRGB leds[NUM_LEDS];
const uint8_t kMatrixWidth = 16;
const uint8_t kMatrixHeight = 16;
const bool    kMatrixSerpentineLayout = true;
#define BRIGHTNESS         15
#define FRAMES_PER_SECOND  80

void setup() {
  FastLED.clear();
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  //FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<APA102, DATA_PIN, CLK_PIN, BGR, DATA_RATE_MHZ(20)>(leds, NUM_LEDS);
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
//SimplePatternList gPatterns = { addGlitter1, confetti, sinelon, juggle, bpm};
SimplePatternList gPatterns = { addGlitter1, confetti, sinelon};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
  
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 5 ) { gHue=gHue+1; } // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}
uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;
  
  if( kMatrixSerpentineLayout == false) {
    i = (y * kMatrixWidth) + x;
  }

  if( kMatrixSerpentineLayout == true) {
    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (kMatrixWidth - 1) - x;
      i = (y * kMatrixWidth) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * kMatrixWidth) + x;
    }
  }
  
  return i;
}

void matrix()
{

  int pos1 = random16(16);
  int pos2 = random16(16);
  int pos3 = random16(16);
  for (int i = 15; i >= 0; i--) {
    leds [ XY(pos1,i) ] = CRGB::Green;
    leds [ XY(pos2,i) ] = CRGB::Green;
    leds [ XY(pos3,i) ] = CRGB::Green;
    fadeToBlackBy( leds, NUM_LEDS, 80);
    FastLED.delay(30);
  }
}

void mario()
{
  leds[ XY(2,0) ] = CRGB::Brown;
  leds[ XY(3,0) ] = CRGB::Brown;
  leds[ XY(4,0) ] = CRGB::Brown;
  leds[ XY(5,0) ] = CRGB::Brown;
  leds[ XY(6,0) ] = CRGB::Brown;
  leds[ XY(9,0) ] = CRGB::Brown;
  leds[ XY(10,0) ] = CRGB::Brown;
  leds[ XY(11,0) ] = CRGB::Brown;
  leds[ XY(12,0) ] = CRGB::Brown;
  leds[ XY(13,0) ] = CRGB::Brown;
  leds[ XY(3,1) ] = CRGB::Brown;
  leds[ XY(4,1) ] = CRGB::Brown;
  leds[ XY(5,1) ] = CRGB::Brown;
  leds[ XY(6,1) ] = CRGB::Brown;
  leds[ XY(9,1) ] = CRGB::Brown;
  leds[ XY(10,1) ] = CRGB::Brown;
  leds[ XY(11,1) ] = CRGB::Brown;
  leds[ XY(12,1) ] = CRGB::Brown;
  leds[ XY(3,10) ] = CRGB::Brown;
  leds[ XY(4,10) ] = CRGB::Brown;
  leds[ XY(3,11) ] = CRGB::Brown;
  leds[ XY(5,11) ] = CRGB::Brown;
  leds[ XY(3,12) ] = CRGB::Brown;
  leds[ XY(5,12) ] = CRGB::Brown;
  leds[ XY(4,13) ] = CRGB::Brown;
  leds[ XY(5,13) ] = CRGB::Brown;
  leds[ XY(6,13) ] = CRGB::Brown;
  leds[ XY(4,2) ] = CRGB::Blue;
  leds[ XY(5,2) ] = CRGB::Blue;
  leds[ XY(6,2) ] = CRGB::Blue;
  leds[ XY(9,2) ] = CRGB::Blue;
  leds[ XY(10,2) ] = CRGB::Blue;
  leds[ XY(11,2) ] = CRGB::Blue;
  leds[ XY(4,3) ] = CRGB::Blue;
  leds[ XY(5,3) ] = CRGB::Blue;
  leds[ XY(6,3) ] = CRGB::Blue;
  leds[ XY(7,3) ] = CRGB::Blue;
  leds[ XY(8,3) ] = CRGB::Blue;
  leds[ XY(9,3) ] = CRGB::Blue;
  leds[ XY(10,3) ] = CRGB::Blue;
  leds[ XY(11,3) ] = CRGB::Blue;
  leds[ XY(5,4) ] = CRGB::Blue;
  leds[ XY(6,4) ] = CRGB::Blue;
  leds[ XY(7,4) ] = CRGB::Blue;
  leds[ XY(8,4) ] = CRGB::Blue;
  leds[ XY(9,4) ] = CRGB::Blue;
  leds[ XY(10,4) ] = CRGB::Blue;
  leds[ XY(5,5) ] = CRGB::Blue;
  leds[ XY(7,5) ] = CRGB::Blue;
  leds[ XY(8,5) ] = CRGB::Blue;
  leds[ XY(10,5) ] = CRGB::Blue;
  leds[ XY(6,6) ] = CRGB::Blue;
  leds[ XY(7,6) ] = CRGB::Blue;
  leds[ XY(8,6) ] = CRGB::Blue;
  leds[ XY(9,6) ] = CRGB::Blue; 
  leds[ XY(6,7) ] = CRGB::Blue;
  leds[ XY(9,7) ] = CRGB::Blue;
  leds[ XY(6,8) ] = CRGB::Blue;
  leds[ XY(10,8) ] = CRGB::Blue;
  leds[ XY(6,5) ] = CRGB::Red;
  leds[ XY(9,5) ] = CRGB::Red;
  leds[ XY(2,6) ] = CRGB::Red;
  leds[ XY(3,6) ] = CRGB::Red;
  leds[ XY(4,6) ] = CRGB::Red;
  leds[ XY(5,6) ] = CRGB::Red;
  leds[ XY(13,6) ] = CRGB::Red;
  leds[ XY(10,6) ] = CRGB::Red;
  leds[ XY(11,6) ] = CRGB::Red;
  leds[ XY(12,6) ] = CRGB::Red;
  
}
void lunchbox()
{
  
  FastLED.clear();
  leds[ XY(0,0) ] = CRGB::Green;
  leds[ XY(1,0) ] = CRGB::Green;
  leds[ XY(2,0) ] = CRGB::Green;
  leds[ XY(3,0) ] = CRGB::Green;
  leds[ XY(4,0) ] = CRGB::Green;
  leds[ XY(5,0) ] = CRGB::Green;
  leds[ XY(6,0) ] = CRGB::Green;
  leds[ XY(7,0) ] = CRGB::Green;
  leds[ XY(7,1) ] = CRGB::Green;
  leds[ XY(7,2) ] = CRGB::Green;
  leds[ XY(7,3) ] = CRGB::Green;
  leds[ XY(7,4) ] = CRGB::Green;
  leds[ XY(7,5) ] = CRGB::Green;
  leds[ XY(7,6) ] = CRGB::Green;
  leds[ XY(7,7) ] = CRGB::Green;
  FastLED.delay(1000);
  FastLED.clear();
  leds[ XY(1,0) ] = CRGB::Green;
  leds[ XY(2,0) ] = CRGB::Green;
  leds[ XY(3,0) ] = CRGB::Green;
  leds[ XY(4,0) ] = CRGB::Green;
  leds[ XY(5,0) ] = CRGB::Green;
  leds[ XY(6,0) ] = CRGB::Green;
  leds[ XY(0,1) ] = CRGB::Green;
  leds[ XY(0,2) ] = CRGB::Green;
  leds[ XY(0,3) ] = CRGB::Green;
  leds[ XY(0,4) ] = CRGB::Green;
  leds[ XY(0,5) ] = CRGB::Green;
  leds[ XY(0,6) ] = CRGB::Green;
  leds[ XY(0,7) ] = CRGB::Green;
  leds[ XY(7,1) ] = CRGB::Green;
  leds[ XY(7,2) ] = CRGB::Green;
  leds[ XY(7,3) ] = CRGB::Green;
  leds[ XY(7,4) ] = CRGB::Green;
  leds[ XY(7,5) ] = CRGB::Green;
  leds[ XY(7,6) ] = CRGB::Green;
  leds[ XY(7,7) ] = CRGB::Green;
  FastLED.delay(1000);
  FastLED.clear();
  leds[ XY(0,0) ] = CRGB::Green;
  leds[ XY(0,1) ] = CRGB::Green;
  leds[ XY(0,2) ] = CRGB::Green;
  leds[ XY(0,3) ] = CRGB::Green;
  leds[ XY(0,4) ] = CRGB::Green;
  leds[ XY(0,5) ] = CRGB::Green;
  leds[ XY(0,6) ] = CRGB::Green;
  leds[ XY(0,7) ] = CRGB::Green;
  leds[ XY(7,0) ] = CRGB::Green;
  leds[ XY(7,1) ] = CRGB::Green;
  leds[ XY(7,2) ] = CRGB::Green;
  leds[ XY(7,3) ] = CRGB::Green;
  leds[ XY(7,4) ] = CRGB::Green;
  leds[ XY(7,5) ] = CRGB::Green;
  leds[ XY(7,6) ] = CRGB::Green;
  leds[ XY(7,7) ] = CRGB::Green;
  leds[ XY(1,1) ] = CRGB::Green;
  leds[ XY(2,2) ] = CRGB::Green;
  leds[ XY(3,3) ] = CRGB::Green;
  leds[ XY(4,4) ] = CRGB::Green;
  leds[ XY(5,5) ] = CRGB::Green;
  leds[ XY(6,6) ] = CRGB::Green;
  FastLED.delay(1000);
  FastLED.clear();
  leds[ XY(1,0) ] = CRGB::Green;
  leds[ XY(2,0) ] = CRGB::Green;
  leds[ XY(3,0) ] = CRGB::Green;
  leds[ XY(4,0) ] = CRGB::Green;
  leds[ XY(5,0) ] = CRGB::Green;
  leds[ XY(0,1) ] = CRGB::Green;
  leds[ XY(6,1) ] = CRGB::Green;
  leds[ XY(7,2) ] = CRGB::Green;
  leds[ XY(7,3) ] = CRGB::Green;
  leds[ XY(7,4) ] = CRGB::Green;
  leds[ XY(7,5) ] = CRGB::Green;
  leds[ XY(0,6) ] = CRGB::Green;
  leds[ XY(6,6) ] = CRGB::Green;
  leds[ XY(1,7) ] = CRGB::Green;
  leds[ XY(2,7) ] = CRGB::Green;
  leds[ XY(3,7) ] = CRGB::Green;
  leds[ XY(4,7) ] = CRGB::Green;
  leds[ XY(5,7) ] = CRGB::Green;
  FastLED.delay(1000);
  FastLED.clear();
  leds[ XY(0,0) ] = CRGB::Green;
  leds[ XY(0,1) ] = CRGB::Green;
  leds[ XY(0,2) ] = CRGB::Green;
  leds[ XY(0,3) ] = CRGB::Green;
  leds[ XY(0,4) ] = CRGB::Green;
  leds[ XY(0,5) ] = CRGB::Green;
  leds[ XY(0,6) ] = CRGB::Green;
  leds[ XY(0,7) ] = CRGB::Green;
  leds[ XY(7,0) ] = CRGB::Green;
  leds[ XY(7,1) ] = CRGB::Green;
  leds[ XY(7,2) ] = CRGB::Green;
  leds[ XY(7,3) ] = CRGB::Green;
  leds[ XY(7,4) ] = CRGB::Green;
  leds[ XY(7,5) ] = CRGB::Green;
  leds[ XY(7,6) ] = CRGB::Green;
  leds[ XY(7,7) ] = CRGB::Green;
  leds[ XY(0,3) ] = CRGB::Green;
  leds[ XY(1,3) ] = CRGB::Green;
  leds[ XY(2,3) ] = CRGB::Green;
  leds[ XY(3,3) ] = CRGB::Green;
  leds[ XY(4,3) ] = CRGB::Green;
  leds[ XY(5,3) ] = CRGB::Green;
  leds[ XY(6,3) ] = CRGB::Green;
  FastLED.delay(1000);
  FastLED.clear();
  leds[ XY(1,0) ] = CRGB::Green;
  leds[ XY(2,0) ] = CRGB::Green;
  leds[ XY(3,0) ] = CRGB::Green;
  leds[ XY(4,0) ] = CRGB::Green;
  leds[ XY(5,0) ] = CRGB::Green;
  leds[ XY(6,0) ] = CRGB::Green;
  leds[ XY(7,0) ] = CRGB::Green;
  leds[ XY(0,1) ] = CRGB::Green;
  leds[ XY(7,1) ] = CRGB::Green;
  leds[ XY(0,2) ] = CRGB::Green;
  leds[ XY(7,2) ] = CRGB::Green;
  leds[ XY(0,3) ] = CRGB::Green;
  leds[ XY(7,3) ] = CRGB::Green;
  leds[ XY(1,4) ] = CRGB::Green;
  leds[ XY(2,4) ] = CRGB::Green;
  leds[ XY(3,4) ] = CRGB::Green;
  leds[ XY(4,4) ] = CRGB::Green;
  leds[ XY(5,4) ] = CRGB::Green;
  leds[ XY(6,4) ] = CRGB::Green;
  leds[ XY(7,4) ] = CRGB::Green;
  leds[ XY(0,5) ] = CRGB::Green;
  leds[ XY(7,5) ] = CRGB::Green;
  leds[ XY(0,6) ] = CRGB::Green;
  leds[ XY(7,6) ] = CRGB::Green;
  leds[ XY(1,7) ] = CRGB::Green;
  leds[ XY(2,7) ] = CRGB::Green;
  leds[ XY(3,7) ] = CRGB::Green;
  leds[ XY(4,7) ] = CRGB::Green;
  leds[ XY(5,7) ] = CRGB::Green;
  leds[ XY(6,7) ] = CRGB::Green;
  leds[ XY(7,7) ] = CRGB::Green;
  FastLED.delay(1000);
  FastLED.clear();
  leds[ XY(1,0) ] = CRGB::Green;
  leds[ XY(2,0) ] = CRGB::Green;
  leds[ XY(3,0) ] = CRGB::Green;
  leds[ XY(4,0) ] = CRGB::Green;
  leds[ XY(5,0) ] = CRGB::Green;
  leds[ XY(6,0) ] = CRGB::Green;
  leds[ XY(0,1) ] = CRGB::Green;
  leds[ XY(7,1) ] = CRGB::Green;
  leds[ XY(0,2) ] = CRGB::Green;
  leds[ XY(7,2) ] = CRGB::Green;
  leds[ XY(0,3) ] = CRGB::Green;
  leds[ XY(7,3) ] = CRGB::Green;
  leds[ XY(0,4) ] = CRGB::Green;
  leds[ XY(7,4) ] = CRGB::Green;
  leds[ XY(0,5) ] = CRGB::Green;
  leds[ XY(7,5) ] = CRGB::Green;
  leds[ XY(0,6) ] = CRGB::Green;
  leds[ XY(7,6) ] = CRGB::Green;
  leds[ XY(1,7) ] = CRGB::Green;
  leds[ XY(2,7) ] = CRGB::Green;
  leds[ XY(3,7) ] = CRGB::Green;
  leds[ XY(4,7) ] = CRGB::Green;
  leds[ XY(5,7) ] = CRGB::Green;
  leds[ XY(6,7) ] = CRGB::Green;
  FastLED.delay(1000);
  FastLED.clear();
  leds[ XY(0,0) ] = CRGB::Green;
  leds[ XY(7,0) ] = CRGB::Green;
  leds[ XY(1,1) ] = CRGB::Green;
  leds[ XY(6,1) ] = CRGB::Green;
  leds[ XY(2,2) ] = CRGB::Green;
  leds[ XY(5,2) ] = CRGB::Green;
  leds[ XY(3,3) ] = CRGB::Green;
  leds[ XY(4,3) ] = CRGB::Green;
  leds[ XY(4,4) ] = CRGB::Green;
  leds[ XY(3,4) ] = CRGB::Green;
  leds[ XY(5,5) ] = CRGB::Green;
  leds[ XY(2,5) ] = CRGB::Green;
  leds[ XY(6,6) ] = CRGB::Green;
  leds[ XY(1,6) ] = CRGB::Green;
  leds[ XY(7,7) ] = CRGB::Green;
  leds[ XY(0,7) ] = CRGB::Green;
  FastLED.delay(1000);
  FastLED.clear();
  
  
}


void lowBat()
{
  FastLED.clear();
  FastLED.setBrightness(50);
  leds[16] += CRGB::White;
  leds[17] += CRGB::White;
  leds[18] += CRGB::White;
  leds[19] += CRGB::White;
  leds[20] += CRGB::White;
  leds[21] += CRGB::White;
  leds[22] += CRGB::White;
  leds[23] += CRGB::White;
  leds[24] += CRGB::White;
  leds[25] += CRGB::Red;
  leds[31] += CRGB::White;
  leds[32] += CRGB::White;
  leds[38] += CRGB::Red;
  leds[39] += CRGB::White;
  leds[40] += CRGB::White;
  leds[41] += CRGB::White;
  leds[42] += CRGB::White;
  leds[43] += CRGB::White;
  leds[44] += CRGB::White;
  leds[45] += CRGB::White;
  leds[46] += CRGB::White;
  leds[47] += CRGB::White;
}
void kurt()
{
  FastLED.clear();
  leds[0] += CRGB::Yellow;
  leds[1] += CRGB::Yellow;
  leds[2] += CRGB::Yellow;
  leds[3] += CRGB::Yellow;
  leds[4] += CRGB::Yellow;
  leds[5] += CRGB::Yellow;
  leds[6] += CRGB::Yellow;
  leds[7] += CRGB::Yellow;
  leds[8] += CRGB::Yellow;
  leds[9] += CRGB::Yellow;
  leds[10] += CRGB::Yellow;
  leds[11] += CRGB::White;
  leds[12] += CRGB::White;
  leds[13] += CRGB::Yellow;
  leds[14] += CRGB::Yellow;
  leds[15] += CRGB::Yellow;
  leds[16] += CRGB::Yellow;
  leds[17] += CRGB::Yellow;
  leds[18] += CRGB::Yellow;
  leds[19] += CRGB::Yellow;
  leds[20] += CRGB::Yellow;
  leds[21] += CRGB::Yellow;
  leds[22] += CRGB::Yellow;
  leds[23] += CRGB::Yellow;
  leds[24] += CRGB::White;
  leds[25] += CRGB::White;
  leds[26] += CRGB::White;
  leds[27] += CRGB::White;
  leds[28] += CRGB::White;
  leds[29] += CRGB::White;
  leds[30] += CRGB::White;
  leds[31] += CRGB::White;
  leds[32] += CRGB::White;
  leds[33] += CRGB::Red;
  leds[34] += CRGB::Red;
  leds[35] += CRGB::White;
  leds[36] += CRGB::White;
  leds[37] += CRGB::Blue;
  leds[38] += CRGB::Blue;
  leds[39] += CRGB::White;
  leds[40] += CRGB::White;
  leds[41] += CRGB::White;
  leds[42] += CRGB::White;
  leds[43] += CRGB::White;
  leds[44] += CRGB::White;
  leds[45] += CRGB::White;
  leds[46] += CRGB::White;
  leds[47] += CRGB::White;
  leds[48] += CRGB::Brown;
  leds[49] += CRGB::Brown;
  leds[50] += CRGB::Yellow;
  leds[51] += CRGB::Yellow;
  leds[52] += CRGB::Yellow;
  leds[53] += CRGB::Yellow;
  leds[54] += CRGB::Yellow;
  leds[55] += CRGB::Brown;
  leds[56] += CRGB::Brown;
  leds[57] += CRGB::Brown;
  leds[58] += CRGB::Brown;
  leds[59] += CRGB::Brown;
  leds[60] += CRGB::Brown;
  leds[61] += CRGB::Brown;
  leds[62] += CRGB::Brown;
  leds[63] += CRGB::Brown;
}
void creeper()
{
  FastLED.clear();
  leds[0] += CHSV(98,100,40);
  leds[1] += CRGB::Green;
  leds[2] += CRGB::Blue;
  leds[3] += CRGB::Green;
  leds[4] += CRGB::Green;
  leds[5] += CRGB::Blue;
  leds[6] += CRGB::Green;
  leds[7] += CRGB::Green;
  leds[8] += CRGB::Green;
  leds[9] += CRGB::Green;
  leds[10] += CRGB::Blue;
  leds[11] += CRGB::Blue;
  leds[12] += CRGB::Blue;
  leds[13] += CRGB::Blue;
  leds[14] += CRGB::Green;
  leds[15] += CRGB::Green;
  leds[16] += CRGB::Green;
  leds[17] += CRGB::Green;
  leds[18] += CRGB::Blue;
  leds[19] += CRGB::Blue;
  leds[20] += CRGB::Blue;
  leds[21] += CRGB::Blue;
  leds[22] += CRGB::Green;
  leds[23] += CRGB::Green;
  leds[24] += CRGB::Green;
  leds[25] += CRGB::Green;
  leds[26] += CRGB::Green;
  leds[27] += CRGB::Blue;
  leds[28] += CRGB::Blue;
  leds[29] += CRGB::Green;
  leds[30] += CRGB::Green;
  leds[31] += CRGB::Green;
  leds[32] += CRGB::Green;
  leds[33] += CRGB::Blue;
  leds[34] += CRGB::Blue;
  leds[35] += CRGB::Green;
  leds[36] += CRGB::Green;
  leds[37] += CRGB::Blue;
  leds[38] += CRGB::Blue;
  leds[39] += CRGB::Green;
  leds[40] += CRGB::Green;
  leds[41] += CRGB::Blue;
  leds[42] += CRGB::Blue;
  leds[43] += CRGB::Green;
  leds[44] += CRGB::Green;
  leds[45] += CRGB::Blue;
  leds[46] += CRGB::Blue;
  leds[47] += CRGB::Green;
  leds[48] += CRGB::Green;
  leds[49] += CRGB::Green;
leds[50] += CRGB::Green;
leds[51] += CRGB::Green;
leds[52] += CRGB::Green;
leds[53] += CRGB::Green;
leds[54] += CRGB::Green;
leds[55] += CRGB::Green;
leds[56] += CRGB::Green;
leds[57] += CRGB::Green;
leds[58] += CRGB::Green;
leds[59] += CRGB::Green;
leds[60] += CRGB::Green;
leds[61] += CRGB::Green;
leds[62] += CRGB::Green;
leds[63] += CRGB::Green;
}
void rainbow() 
{
  // FastLED's built-in rainbow generator
  
  fill_rainbow( leds, NUM_LEDS, gHue, 1);
  FastLED.delay(30);
  
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}


void addGlitter1() 
{
 
  fadeToBlackBy( leds, NUM_LEDS, 5);
  if( random8() < 100) {
    int sparkle = random16(NUM_LEDS);
    leds[ sparkle ] += CRGB::White;
    //leds[ sparkle ] += CHSV( random(255), random(255), random(255));
    FastLED.delay(5);
    fadeToBlackBy( leds, NUM_LEDS, 50);
    //FastLED.clear();
  }
}

void lavender()
{
  FastLED.clear();
  CRGBPalette16 palette22 = CloudColors_p;
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( palette22, gHue+i, 75 );
    //leds[i] += CRGB::Yellow;
  }
}
void others()
{
  
  for( byte dothue = 0; dothue <= 255; dothue+=1 ){
       
  
  for( int i = 0; i < NUM_LEDS/4; i++) {
     leds[i] = CHSV(dothue, 255, 150);
     leds[i+(NUM_LEDS*1/4)] = CHSV(dothue, 200, 150);
     leds[i+(NUM_LEDS*2/4)] = CHSV(dothue, 255, 150);
     leds[i+(NUM_LEDS*3/4)] = CHSV(dothue, 200, 150);
     FastLED.delay(50);
     fadeToBlackBy(leds, NUM_LEDS, 80);
  }   
  
     

//    if ( i % 3 == 0) {
//      leds[i] += CRGB::Green;
//    }
//    if ( i % 3 == 1) {
//      leds[i] += 0xB22222;
//    }
//    if ( i % 3 == 2) {
//      leds[i] += CRGB::LawnGreen;
//    }
  }
}
void disco()
{
 
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] += CRGB( random16(0,255), random16(0,255), random16(0,255) );
  }
  FastLED.delay(500);
  FastLED.clear();
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 40);
  int pos = beatsin16(25,0,kMatrixWidth);
  for( int i = 0; i < kMatrixHeight; i++)
  {
    leds[XY(pos,i)] += CHSV( gHue, 255, 192);
    leds[XY(i,pos)] += CHSV( gHue, 255, 192);
    
  }
}


void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 10;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
  //for( int i = 0; i < NUM_LEDS; i++) { //9948
    //leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*20));
    for( int i = 0; i < kMatrixWidth; i++) { //9948
      for ( int j = 0; j < kMatrixHeight; j++) {
      leds[ XY(i,j) ] = ColorFromPalette(palette, gHue+(i), beat-gHue*(j));
      
      }
    }
}


void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  FastLED.clear();
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  
    
  }
}

