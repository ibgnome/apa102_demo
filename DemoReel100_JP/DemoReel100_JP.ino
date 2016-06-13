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
#define COLOR_ORDER BGR
#define NUM_LEDS    1024
CRGB leds[NUM_LEDS];
const uint8_t kMatrixWidth = 16;
const uint8_t kMatrixHeight = 16;
const bool    kMatrixSerpentineLayout = true;
#define BRIGHTNESS         20
#define FRAMES_PER_SECOND  120

void setup() {
  FastLED.clear();
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
    FastLED.addLeds<LED_TYPE, DATA_PIN, CLK_PIN, COLOR_ORDER, DATA_RATE_MHZ(5)>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  //FastLED.setDither(0);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
//SimplePatternList gPatterns = { addGlitter1, confetti, sinelon, juggle, bpm};
SimplePatternList gPatterns = { sweep, sinelon, addGlitter1, confetti, lavender, bpm};
//SimplePatternList gPatterns = { sinelon };

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
  EVERY_N_MILLISECONDS( 5 ) { gHue=gHue+16; } // slowly cycle the "base color" through the rainbow
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
 
  
  //if( random8() < 800) {
    int sparkle = random16(NUM_LEDS);
    leds[ sparkle ] += CRGB::White;
    //leds[ sparkle ] += CHSV( random(255), random(255), random(255));
    fadeToBlackBy( leds, NUM_LEDS, 5);
    //FastLED.clear();
  //}
}

void lavender()
{
  FastLED.clear();
  CRGBPalette16 palette22 = ForestColors_p;
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( palette22, gHue+i, 75 );
  }
  FastLED.delay(20);
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 2);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  
  //int pos = beatsin16(60,0,kMatrixHeight);
  for( int pos = 0; pos < 16; pos++){
  for( int i = 0; i < kMatrixHeight; i++){
  
    leds[XY(pos,i)] += CHSV( gHue, 255, 192);
    leds[XY(i,pos)] += CHSV( gHue, 255, 192);
    leds[XY(15-pos,i)] += CHSV( gHue, 255, 192);
    leds[XY(i,15-pos)] += CHSV( gHue, 255, 192);
    leds[XY(pos,i+15)] += CHSV( gHue, 255, 192);
    leds[XY(i,pos+15)] += CHSV( gHue, 255, 192);
    leds[XY(31-pos+15,i)] += CHSV( gHue, 255, 192);
    leds[XY(i,31-pos)] += CHSV( gHue, 255, 192);
    leds[XY(pos,i+31)] += CHSV( gHue, 255, 192);
    leds[XY(i,pos+31)] += CHSV( gHue, 255, 192);
    leds[XY(15-pos,i+31)] += CHSV( gHue, 255, 192);
    leds[XY(i,47-pos)] += CHSV( gHue, 255, 192);
    leds[XY(pos,i+47)] += CHSV( gHue, 255, 192);
    leds[XY(i,pos+47)] += CHSV( gHue, 255, 192);
    leds[XY(15-pos,i+47)] += CHSV( gHue, 255, 192);
    leds[XY(i,63-pos)] += CHSV( gHue, 255, 192);
    
  }  
  FastLED.delay(30);
  fadeToBlackBy( leds, NUM_LEDS, 95);
  }
  
}

void sweep()
{
  for( int i = 0; i < 64; i++ )
  
  {
      for( int j = 0; j<16; j++)
      {  
      leds[XY(j,i)] += CHSV(gHue, 255, 192);
      leds[XY(j,63-i)] += CHSV(gHue+64, 255, 192);
     
      
      }
       FastLED.delay(10);
      fadeToBlackBy( leds, NUM_LEDS, 30);
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
  
  for( int i = 0; i < 64; i++) {
     for ( int j = 0; j < 16; j++) {
      leds[ XY(j,i) ] = ColorFromPalette(palette, gHue+(i), beat-gHue*(j));
      
    }
  }
  FastLED.delay(50);
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

