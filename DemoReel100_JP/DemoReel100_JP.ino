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

#define DATA_PIN    11
#define CLK_PIN   13
#define LED_TYPE    APA102
#define COLOR_ORDER RGB
#define NUM_LEDS    1024
CRGB leds[NUM_LEDS];
const uint8_t kMatrixWidth = 16;
const uint8_t kMatrixHeight = 16;
const bool    kMatrixSerpentineLayout = true;
#define BRIGHTNESS         20
#define FRAMES_PER_SECOND  80

void setup() {
  FastLED.clear();
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  //FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<APA102, DATA_PIN, CLK_PIN, BGR, DATA_RATE_MHZ(5)>(leds, NUM_LEDS);
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
//SimplePatternList gPatterns = { addGlitter1, confetti, sinelon, juggle, bpm};
//SimplePatternList gPatterns = { sinelon, addGlitter1, confetti, bpm};
SimplePatternList gPatterns = { sweep };

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
  EVERY_N_MILLISECONDS( 5 ) { gHue=gHue+8; } // slowly cycle the "base color" through the rainbow
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


void rainbow() 
{
  // FastLED's built-in rainbow generator
  
  fill_rainbow( leds, NUM_LEDS, gHue, 1);
  FastLED.delay(10);
  
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
  if( random8() < 800) {
    int sparkle = random16(NUM_LEDS);
    leds[ sparkle ] += CRGB::White;
    //leds[ sparkle ] += CHSV( random(255), random(255), random(255));
    FastLED.delay(5);
    fadeToBlackBy( leds, NUM_LEDS, 20);
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
  int pos = beatsin16(60,0,kMatrixHeight);
  int pos2 = 0;
  for( int i = 0; i < kMatrixHeight; i++){
  
    leds[XY(pos,i)] += CHSV( gHue, 255, 192);
    leds[XY(i,pos)] += CHSV( gHue, 255, 192);
    leds[XY(pos,i+16)] += CHSV( gHue, 255, 192);
    leds[XY(i+16,pos)] += CHSV( gHue, 255, 192);
    if (pos == 0){
          leds[XY(15,i)] += CHSV( gHue, 255, 192);
          leds[XY(i,15)] += CHSV( gHue, 255, 192);
          leds[XY(15,i+16)] += CHSV( gHue, 255, 192);
          leds[XY(i+16,15)] += CHSV( gHue, 255, 192);
    }
    if (pos == 1){
          leds[XY(14,i)] += CHSV( gHue, 255, 192);
          leds[XY(i,14)] += CHSV( gHue, 255, 192);
          leds[XY(14,i+16)] += CHSV( gHue, 255, 192);
          leds[XY(i+16,14)] += CHSV( gHue, 255, 192);
    }
    if (pos == 2){
          leds[XY(13,i)] += CHSV( gHue, 255, 192);
          leds[XY(i,13)] += CHSV( gHue, 255, 192);
          leds[XY(13,i+16)] += CHSV( gHue, 255, 192);
          leds[XY(i+16,13)] += CHSV( gHue, 255, 192);
    }
    if (pos == 3){
          leds[XY(12,i)] += CHSV( gHue, 255, 192);
          leds[XY(i,12)] += CHSV( gHue, 255, 192);
          leds[XY(12,i+16)] += CHSV( gHue, 255, 192);
          leds[XY(i+16,12)] += CHSV( gHue, 255, 192);
    }
    if (pos == 4){
          leds[XY(11,i)] += CHSV( gHue, 255, 192);
          leds[XY(i,11)] += CHSV( gHue, 255, 192);
          leds[XY(11,i+16)] += CHSV( gHue, 255, 192);
          leds[XY(i+16,11)] += CHSV( gHue, 255, 192);
    }
    if (pos == 5){
          leds[XY(10,i)] += CHSV( gHue, 255, 192);
          leds[XY(i,10)] += CHSV( gHue, 255, 192);
          leds[XY(10,i+16)] += CHSV( gHue, 255, 192);
          leds[XY(i+16,10)] += CHSV( gHue, 255, 192);
    }
    if (pos == 6){
          leds[XY(9,i)] += CHSV( gHue, 255, 192);
          leds[XY(i,9)] += CHSV( gHue, 255, 192);
          leds[XY(9,i+16)] += CHSV( gHue, 255, 192);
          leds[XY(i+16,9)] += CHSV( gHue, 255, 192);
    }
    if (pos == 7){
          leds[XY(8,i)] += CHSV( gHue, 255, 192);
          leds[XY(i,8)] += CHSV( gHue, 255, 192);
          leds[XY(8,i+16)] += CHSV( gHue, 255, 192);
          leds[XY(i+16,8)] += CHSV( gHue, 255, 192);
    }
    if (pos == 8){
          leds[XY(7,i)] += CHSV( gHue, 255, 192);
          leds[XY(i,7)] += CHSV( gHue, 255, 192);
          leds[XY(7,i+16)] += CHSV( gHue, 255, 192);
          leds[XY(i+16,7)] += CHSV( gHue, 255, 192);
    }
    if (pos == 9){
          leds[XY(6,i)] += CHSV( gHue, 255, 192);
          leds[XY(i,6)] += CHSV( gHue, 255, 192);
          leds[XY(6,i+16)] += CHSV( gHue, 255, 192);
          leds[XY(i+16,6)] += CHSV( gHue, 255, 192);
    }
    if (pos == 10){
          leds[XY(5,i)] += CHSV( gHue, 255, 192);
           leds[XY(i,5)] += CHSV( gHue, 255, 192);
           leds[XY(5,i+16)] += CHSV( gHue, 255, 192);
           leds[XY(i+16,5)] += CHSV( gHue, 255, 192);
    }
    if (pos == 11){
          leds[XY(4,i)] += CHSV( gHue, 255, 192);
          leds[XY(i,4)] += CHSV( gHue, 255, 192);
          leds[XY(4,i+16)] += CHSV( gHue, 255, 192);
          leds[XY(i+16,4)] += CHSV( gHue, 255, 192);
    }
    if (pos == 12){
          leds[XY(3,i)] += CHSV( gHue, 255, 192);
          leds[XY(i,3)] += CHSV( gHue, 255, 192);
          leds[XY(3,i+16)] += CHSV( gHue, 255, 192);
          leds[XY(i+16,3)] += CHSV( gHue, 255, 192);
    }
    if (pos == 13){
          leds[XY(2,i)] += CHSV( gHue, 255, 192);
          leds[XY(i,2)] += CHSV( gHue, 255, 192);
          leds[XY(2,i+16)] += CHSV( gHue, 255, 192);
          leds[XY(i+16,2)] += CHSV( gHue, 255, 192);
    }
    if (pos == 14){
          leds[XY(1,i)] += CHSV( gHue, 255, 192);
          leds[XY(i,1)] += CHSV( gHue, 255, 192);
          leds[XY(1,i+16)] += CHSV( gHue, 255, 192);
          leds[XY(i+16,1)] += CHSV( gHue, 255, 192);
    }
    if (pos == 15){
          leds[XY(0,i)] += CHSV( gHue, 255, 192);
          leds[XY(i,0)] += CHSV( gHue, 255, 192);
          leds[XY(0,i+16)] += CHSV( gHue, 255, 192);
          leds[XY(i+16,0)] += CHSV( gHue, 255, 192);
    }

  }
 // for( int j = kMatrixHeight-1; j > 0; j--)
  //{
  //   leds[XY(j,pos2)] += CHSV( gHue, 255, 192);
   // leds[XY(pos2,j)] += CHSV( gHue, 255, 192);
  //}
}
void sweep()
{
  for( int i = 0; i < 64; i++ )
  
  {
      for( int j = 0; j<16; j++)
      {  
      leds[XY(j,i)] += CHSV(gHue, 255, 192);
     
      
      }
       FastLED.delay(10);
      fadeToBlackBy( leds, NUM_LEDS, 30);
  }
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 10;
  CRGBPalette16 palette = CloudColors_p;
  uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*20));
    //for( int i = 0; i < 16; i++) { //9948
      //for ( int j = 0; j < 32; j++) {
      //leds[ XY(i,j) ] = ColorFromPalette(palette, gHue+(i), beat-gHue*(j));
      
      //}
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

