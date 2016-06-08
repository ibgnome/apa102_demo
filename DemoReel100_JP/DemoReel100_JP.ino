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
#define FRAMES_PER_SECOND  60

void setup() {
  FastLED.clear();
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
    FastLED.addLeds<LED_TYPE, DATA_PIN, CLK_PIN, COLOR_ORDER, DATA_RATE_MHZ(5)>(leds, NUM_LEDS)setCorrection(TypicalLEDStrip);
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
 }
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
  uint8_t BeatsPerMinute = 30;
  CRGBPalette16 palette = CloudColors_p;
  uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
  //for( int i = 0; i < NUM_LEDS; i++) { //9948
  //leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*20));
  
  for( int i = 0; i < 64; i++) {
     for ( int j = 0; j < 16; j++) {
      leds[ XY(j,i) ] = ColorFromPalette(palette, gHue+(i), beat-gHue*(j));
      
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

