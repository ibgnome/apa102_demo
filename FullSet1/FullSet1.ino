/* This is the "full set" for my led tophat created for DragonCon 2016.  
 * Top hat was created using a Teensy 3.2 running FastLED (https://github.com/FastLED) as the main LED library, 
 * I'm running 1024 LED's in a circular format around the ~ 7 inch tall hat.  The matrix is formed
 * from four 16x16 APA102 panels and can be run from a USB power bank, utilizing under 3amp.
 * Must be compiled on Arduino IDE 1.6.5 with Teensyduino 1.35.  Make sure to change "CPU Speed" to 24Mhz optimized as some flicker
 * can occur at higher rates due to the number of leds being driven.
 
 Josh Parsons - UAHLunchbox
 */

#include <FastLED.h>
#include <Button.h> // https://github.com/madleech/Button
// Libraries from https://github.com/AaronLiddiment
#include <LEDMatrix.h>
#include <LEDSprites.h>
#include <LEDText.h>
#include <Font12x16.h>
#include <FontP16x16.h>
#include <FontMatrise.h>

#include "Sprites.h"
#include "Message.h"
#include "Vars.h"

// Set to run on the Teensy 3.2 SPI ports and run on APA102 leds
#define DATA_PIN    11
#define CLK_PIN   13
#define CHIPSET    APA102
#define COLOR_ORDER BGR

// This is set for the LED matrices on the top hat. 
#define MATRIX_WIDTH   64
#define MATRIX_HEIGHT  -16
#define MATRIX_TYPE    VERTICAL_ZIGZAG_MATRIX
#define WIDTH   64
#define HEIGHT  16

//Define the matrix.
cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

cLEDSprites Sprites(&leds);
CRGBPalette16 gPal;
uint8_t noise[MAX_DIMENSION][MAX_DIMENSION];

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void setup()
{
  FastLED.addLeds<CHIPSET, DATA_PIN, CLK_PIN, COLOR_ORDER, DATA_RATE_MHZ(5)>(leds[0], leds.Size()).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(20);
  FastLED.setDither(0);
  FastLED.clear(true);
  gPal = HeatColors_p;
  delay(500);
  delay(1000);
  count = 0;
  FastLED.show();

  ScrollingMsg.SetFont(MatriseFontData);
  ScrollingMsg.Init(&leds, leds.Width(), ScrollingMsg.FontHeight() + 1, 0, 5);
  ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
  ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0xff, 0x00, 0xff);
  Options = INSTANT_OPTIONS_MODE;
  ScrollingMsg.SetOptionsChangeMode(Options);
  
  PlasmaShift = (random8(0, 5) * 32) + 64;
  PlasmaTime = 0;

  btnA.begin();
  btnB.begin();
  btnC.begin();
  btnD.begin();

}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
  SimplePatternList gPatterns = { Dcon, MultiMario, Matrix, Maus, Circles, TrippyRainbow, Glitter, Glitter, CompCube, Plasma, Noise, Fireplace, Wave, Lines};
  SimplePatternList gPatterns1 = { Dcon, MultiMario, MultiMario, Matrix, Maus, Circles, TrippyRainbow, threeSine, threeSine, plasma2, Glitter, Glitter, slantBars, Plasma, Zelda, Zelda, Fireplace, Wave, Lines};
  SimplePatternList gPatterns2 = { Zelda, Zelda, MultiMario, MultiMario};
  SimplePatternList gPatterns3 = { Circles, TrippyRainbow, Glitter, Plasma,  Lines, Noise};
  SimplePatternList gPatterns4 = { Fireplace, Wave, Dcon };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gCurrentPatternNumber1 = 0; // Index number of which pattern is current
uint8_t gCurrentPatternNumber2 = 0; // Index number of which pattern is current
uint8_t gCurrentPatternNumber3 = 0; // Index number of which pattern is current
uint8_t gCurrentPatternNumber4 = 0; // Index number of which pattern is current

void loop()
{
  random16_add_entropy( random());

  btnA.read();
  btnB.read();
  btnC.read();
  btnD.read();
  if (btnA.pressed())
  {
  state = 2;
  Sprites.RemoveSprite(&SprMushroom);
  Sprites.RemoveSprite(&SprMarioRight);
  Sprites.RemoveSprite(&SprLuigiRight);
  Sprites.RemoveSprite(&SprGoomba);
  Sprites.RemoveSprite(&SprMushroom2);
  Sprites.RemoveSprite(&SprMarioRight2);
  Sprites.RemoveSprite(&SprLuigiRight2);
  Sprites.RemoveSprite(&SprGoomba2);
  Sprites.RemoveSprite(&SprBrow);
  Sprites.RemoveSprite(&SprMaus);
  Sprites.RemoveSprite(&SprCompCube1);
  Sprites.RemoveSprite(&SprCompCube2);
  Sprites.RemoveSprite(&SprCompCube3);
  Sprites.RemoveSprite(&SprCompCube4);
  Sprites.RemoveSprite(&SprLink);
  Sprites.RemoveSprite(&SprOctorok);
  Sprites.RemoveSprite(&SprFairy);
  Sprites.RemoveSprite(&SprTriforce);
  Sprites.RemoveSprite(&SprLink2);
  Sprites.RemoveSprite(&SprOctorok2);
  Sprites.RemoveSprite(&SprFairy2);
  Sprites.RemoveSprite(&SprTriforce2);
  zcount = 0;
  count = 0;
  count2 = 0;
  mcount = 0;
  eye_count = 0;
  cube_count = 0;
  mauscount = 0;
  nextstate = 0;
  }   
    
  if (btnB.pressed())
  {
  state = 1;
  Sprites.RemoveSprite(&SprMushroom);
  Sprites.RemoveSprite(&SprMarioRight);
  Sprites.RemoveSprite(&SprLuigiRight);
  Sprites.RemoveSprite(&SprGoomba);
  Sprites.RemoveSprite(&SprMushroom2);
  Sprites.RemoveSprite(&SprMarioRight2);
  Sprites.RemoveSprite(&SprLuigiRight2);
  Sprites.RemoveSprite(&SprGoomba2);
  Sprites.RemoveSprite(&SprBrow);
  Sprites.RemoveSprite(&SprMaus);
  Sprites.RemoveSprite(&SprCompCube1);
  Sprites.RemoveSprite(&SprCompCube2);
  Sprites.RemoveSprite(&SprCompCube3);
  Sprites.RemoveSprite(&SprCompCube4);
  Sprites.RemoveSprite(&SprLink);
  Sprites.RemoveSprite(&SprOctorok);
  Sprites.RemoveSprite(&SprFairy);
  Sprites.RemoveSprite(&SprTriforce);
  Sprites.RemoveSprite(&SprLink2);
  Sprites.RemoveSprite(&SprOctorok2);
  Sprites.RemoveSprite(&SprFairy2);
  Sprites.RemoveSprite(&SprTriforce2);
  count = 0;
  count2 = 0;
  zcount = 0;
  mcount = 0;
  eye_count = 0;
  cube_count = 0;
  mauscount = 0;
  nextstate = 0;
  }   
     
  if (btnC.pressed())
  {
  //state = 4;
  Sprites.RemoveSprite(&SprMushroom);
  Sprites.RemoveSprite(&SprMarioRight);
  Sprites.RemoveSprite(&SprLuigiRight);
  Sprites.RemoveSprite(&SprGoomba);
  Sprites.RemoveSprite(&SprMushroom2);
  Sprites.RemoveSprite(&SprMarioRight2);
  Sprites.RemoveSprite(&SprLuigiRight2);
  Sprites.RemoveSprite(&SprGoomba2);
  Sprites.RemoveSprite(&SprBrow);
  Sprites.RemoveSprite(&SprMaus);
  Sprites.RemoveSprite(&SprCompCube1);
  Sprites.RemoveSprite(&SprCompCube2);
  Sprites.RemoveSprite(&SprCompCube3);
  Sprites.RemoveSprite(&SprCompCube4);
  Sprites.RemoveSprite(&SprLink);
  Sprites.RemoveSprite(&SprOctorok);
  Sprites.RemoveSprite(&SprFairy);
  Sprites.RemoveSprite(&SprTriforce);
  Sprites.RemoveSprite(&SprLink2);
  Sprites.RemoveSprite(&SprOctorok2);
  Sprites.RemoveSprite(&SprFairy2);
  Sprites.RemoveSprite(&SprTriforce2);
  count = 0;
  count2 = 0;
  zcount = 0;
  mcount = 0;
  eye_count = 0;
  cube_count = 0;
  mauscount = 0;
  nextstate = 1;
  }
       
  if (btnD.pressed())
  {
//  state = 3;
//  Sprites.RemoveSprite(&SprMushroom);
//  Sprites.RemoveSprite(&SprMarioRight);
//  Sprites.RemoveSprite(&SprLuigiRight);
//  Sprites.RemoveSprite(&SprGoomba);
//  Sprites.RemoveSprite(&SprMushroom2);
//  Sprites.RemoveSprite(&SprMarioRight2);
//  Sprites.RemoveSprite(&SprLuigiRight2);
//  Sprites.RemoveSprite(&SprGoomba2);
//  Sprites.RemoveSprite(&SprBrow);
//  Sprites.RemoveSprite(&SprMaus);
//  Sprites.RemoveSprite(&SprCompCube1);
//  Sprites.RemoveSprite(&SprCompCube2);
//  Sprites.RemoveSprite(&SprCompCube3);
//  Sprites.RemoveSprite(&SprCompCube4);
//  count = 0;
//  mcount = 0;
//  zcount = 0;
//  eye_count = 0;
//  cube_count = 0;
//  mauscount = 0;
//  nextstate = 0;
if ( bright == 20 )
{
  bright = 40;
  FastLED.setBrightness(40);
}
else if ( bright == 40 )
{
  bright = 50;
  FastLED.setBrightness(50);
}
else if ( bright == 50 )
{
  bright = 60;
  FastLED.setBrightness(60);
}
else if ( bright == 60 )
{
  bright = 70;
  FastLED.setBrightness(70);
}
else if ( bright == 70 )
{
  bright = 80;
  FastLED.setBrightness(80);
}
else if ( bright == 80 )
{
  bright = 90;
  FastLED.setBrightness(90);
}
else if ( bright == 90 )
{
  bright = 100;
  FastLED.setBrightness(100);
}
else
{
  bright = 20;
  FastLED.setBrightness(20);
}
  }
    if (state == 1)
  {
  	gPatterns1[gCurrentPatternNumber1]();
  }
   if (state == 2)
  {
  	gPatterns2[gCurrentPatternNumber2]();
  }
  if (state == 3)
  {
  	gPatterns3[gCurrentPatternNumber3]();
  }
  if (nextstate == 1)
  {
    count = 0;
    count2 = 0;
  	nextPattern();
  }

  FastLED.show();  

EVERY_N_MILLISECONDS( 5 ) { gHue=gHue+12; }
  // do some periodic updates
  EVERY_N_SECONDS( 40 ) { nextPattern(); } // change patterns periodically
	// removed " count=0;  " from the above.
}

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
  gCurrentPatternNumber1 = (gCurrentPatternNumber1 + 1) % ARRAY_SIZE( gPatterns1);
  gCurrentPatternNumber2 = (gCurrentPatternNumber2 + 1) % ARRAY_SIZE( gPatterns2);
  gCurrentPatternNumber3 = (gCurrentPatternNumber3 + 1) % ARRAY_SIZE( gPatterns3);
  gCurrentPatternNumber4 = (gCurrentPatternNumber4 + 1) % ARRAY_SIZE( gPatterns4);
  nextstate = 0;
}

void cooldown()
{
  FastLED.clear();
  FastLED.delay(6000);
}

void TrippyRainbow()
{
  int16_t sx, sy, x, y;
  uint8_t h;

  FastLED.clear();
  
  h = hue;
  if (counter < 1500)
  {
    // ** Fill LED's with diagonal stripes
    for (x=0; x<(leds.Width()+leds.Height()); ++x)
    {
      leds.DrawLine(x - leds.Height(), leds.Height() - 1, x, 0, CHSV(h, 255, 192));
      h+=4;
    }
  }
  else
  {
    // ** Fill LED's with horizontal stripes
    for (y=0; y<leds.Height(); ++y)
    {
      leds.DrawLine(0, y, leds.Width() - 1, y, CHSV(h, 255, 192));
      h+=4;
    }
  }
  hue+=4;

  if (counter < 0)
    ;
  else if (counter < 100)
   leds.QuadrantMirror();
  else if (counter < 200)
    leds.QuadrantBottomTriangleMirror();

  counter++;
  if (counter >= 200)
    counter = 0;
  FastLED.show();
  FastLED.delay(10);
}

void Dcon()
{
    FastLED.clear();
    if (ScrollingMsg.UpdateText() == -1)
  {
    ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
    Options ^= INSTANT_OPTIONS_MODE;
    ScrollingMsg.SetOptionsChangeMode(0);
  }
  else
    FastLED.show();
  delay(10);
}

void Zelda()
{
  FastLED.clear();
  Sprites.RemoveSprite(&SprMushroom);
  Sprites.RemoveSprite(&SprMarioRight);
  Sprites.RemoveSprite(&SprLuigiRight);
  Sprites.RemoveSprite(&SprGoomba);
  Sprites.RemoveSprite(&SprMushroom2);
  Sprites.RemoveSprite(&SprMarioRight2);
  Sprites.RemoveSprite(&SprLuigiRight2);
  Sprites.RemoveSprite(&SprGoomba2);
//  Sprites.RemoveSprite(&SprCompCube1);
//  Sprites.RemoveSprite(&SprCompCube2);
//  Sprites.RemoveSprite(&SprCompCube3);
//  Sprites.RemoveSprite(&SprCompCube4);
  Sprites.RemoveSprite(&SprMaus);
//  Sprites.RemoveSprite(&SprBrow);
//    
//    for (int16_t x=0; x<64; x++)
//    {
//      for (int16_t y=0; y<16; y++)
//      {
//        leds(x, y) = CHSV(255,245,81);
//      }
//    }

  Sprites.UpdateSprites();
  Sprites.DetectCollisions();
  if (count2 == 0)
  {
  SprLink.SetPositionFrameMotionOptions(-10/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprLink);
  count2 = 1;
  }
  if (zcount == 0)
  {
   if (SprLink.m_X == 0)
   {
    SprFairy.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprFairy);
   }

   if (SprFairy.m_X == 0)
   {
    SprTriforce.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprTriforce);
   }
   
   if (SprTriforce.m_X == 1)
   {
    SprOctorok.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprOctorok);
    zcount = 1;
   }
    
  }

  
   if (SprLink.m_X == 49)
   {
    SprLink2.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprLink2);
   }
      if (SprLink2.m_X == 49)
   {
    SprLink.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprLink);
   }

      if (SprFairy.m_X == 49)
   {
    SprFairy2.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprFairy2);
   }
      if (SprFairy2.m_X == 49)
   {
    SprFairy.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprFairy);
   }

      if (SprTriforce.m_X == 49)
   {
    SprTriforce2.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 9/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprTriforce2);
   }
      if (SprTriforce2.m_X == 49)
   {
    SprTriforce.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 9/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprTriforce);
   }

      if (SprOctorok.m_X == 49)
   {
    SprOctorok2.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprOctorok2);
   }
      if (SprOctorok2.m_X == 49)
   {
    SprOctorok.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprOctorok);
   }

   Sprites.RenderSprites();
  FastLED.show();
  delay(10);
  count2++;
  eye_count=0;
  mcount=0;
  mauscount=0;
  count=0;
  
}
void MultiMario()
{
//    FastLED.clear();
//    Sprites.RemoveSprite(&SprBrow);
    Sprites.RemoveSprite(&SprMaus);
//    Sprites.RemoveSprite(&SprCompCube1);
//    Sprites.RemoveSprite(&SprCompCube2);
//    Sprites.RemoveSprite(&SprCompCube3);
//    Sprites.RemoveSprite(&SprCompCube4);
    Sprites.RemoveSprite(&SprLink);
    Sprites.RemoveSprite(&SprOctorok);
    Sprites.RemoveSprite(&SprFairy);
    Sprites.RemoveSprite(&SprTriforce);
    Sprites.RemoveSprite(&SprLink2);
    Sprites.RemoveSprite(&SprOctorok2);
    Sprites.RemoveSprite(&SprFairy2);
    Sprites.RemoveSprite(&SprTriforce2);
    
    for (int16_t x=0; x<64; x++)
    {
      for (int16_t y=0; y<16; y++)
      {
        leds(x, y) = CHSV(150,200,100);
      }
    }

  Sprites.UpdateSprites();
  Sprites.DetectCollisions();
  if (count == 0)
  {
  SprMushroom.SetPositionFrameMotionOptions(-10/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprMushroom);
  count = 1;
  }
  if (mcount == 0)
  {
   if (SprMushroom.m_X == 0)
   {
    SprMarioRight.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprMarioRight);
   }

   if (SprMarioRight.m_X == 0)
   {
    SprLuigiRight.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprLuigiRight);
   }
   
   if (SprLuigiRight.m_X == 1)
   {
    SprGoomba.SetPositionFrameMotionOptions(-16/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprGoomba);
    mcount = 1;
   }
    
  }

  
   if (SprMushroom.m_X == 49)
   {
    SprMushroom2.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprMushroom2);
   }
      if (SprMushroom2.m_X == 49)
   {
    SprMushroom.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprMushroom);
   }

      if (SprMarioRight.m_X == 49)
   {
    SprMarioRight2.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprMarioRight2);
   }
      if (SprMarioRight2.m_X == 49)
   {
    SprMarioRight.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprMarioRight);
   }

      if (SprLuigiRight.m_X == 49)
   {
    SprLuigiRight2.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprLuigiRight2);
   }
      if (SprLuigiRight2.m_X == 49)
   {
    SprLuigiRight.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprLuigiRight);
   }

      if (SprGoomba.m_X == 49)
   {
    SprGoomba2.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprGoomba2);
   }
      if (SprGoomba2.m_X == 49)
   {
    SprGoomba.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprGoomba);
   }

  Sprites.RenderSprites();
  FastLED.show();
  delay(10);
  count++;
  eye_count=0;
  zcount = 0;
  count2 = 0;
}

void Plasma()
{
    #define PLASMA_X_FACTOR  10
    #define PLASMA_Y_FACTOR  10
    for (int16_t x=0; x<64; x++)
    {
      for (int16_t y=0; y<16; y++)
      {
        int16_t r = sin16(PlasmaTime) / 256;
        int16_t h = sin16(x * r * PLASMA_X_FACTOR + PlasmaTime) + cos16(y * (-r) * PLASMA_Y_FACTOR + PlasmaTime) + sin16(y * x * (cos16(-PlasmaTime) / 256) / 2);
        leds(x, y) = CHSV((uint8_t)((h / 256) + 128), 255, 130);
      }
    }
    uint16_t OldPlasmaTime = PlasmaTime;
    PlasmaTime += PlasmaShift;
    if (OldPlasmaTime > PlasmaTime)
    PlasmaShift = (random8(0, 5) * 32) + 64;
    leds.HorizontalMirror();  
    FastLED.show();
    FastLED.delay(10);
}

void Wave()
{
  uint8_t h = sin8(angle);
  leds.ShiftLeft();

  for (int16_t y=leds.Height()-1; y>=0; --y)
  {
    if (h > 100 && h < 220)
	  {
    leds(leds.Width()-1, y) = CHSV(h, 255, 255);
    }
    h += 32;
  }
  angle += 12;
  FastLED.show();
  delay(20);
}

void Glitter()
{
fadeToBlackBy( leds[0], 1024, 90);
int star1, star2, star3, star4, star5, star6, star7, star8, star9, star10, star11, star12, star13, star14, star15, star16, star17, star18, star19, star20, star21, star22, star23, star24;
star1 = random16(1023);
star2 = random16(1023);
star3 = random16(1023);
star4 = random16(1023);
star5 = random16(1023);
star6 = random16(1023);
star7 = random16(1023);
star8 = random16(1023);
star9 = random16(1023);
star10 = random16(1023);
star11 = random16(1023);
star12 = random16(1023);
star13 = random16(1023);
star14 = random16(1023);
star15 = random16(1023);
star16 = random16(1023);
star17 = random16(1023);
star18 = random16(1023);
star19 = random16(1023);
star20 = random16(1023);
star21 = random16(1023);
star22 = random16(1023);
star23 = random16(1023);
star24 = random16(1023);

leds(star1) = CRGB::White;
leds(star2) = CRGB::White;
leds(star3) = CRGB::White;
leds(star4) = CRGB::Red;
leds(star5) = CRGB::Green;
leds(star6) = CRGB::Blue;
leds(star7) = CRGB::SkyBlue;
leds(star8) = CRGB::LimeGreen;
leds(star9) = CRGB::Pink;
leds(star10) = CRGB::Red;
leds(star11) = CRGB::Green;
leds(star12) = CRGB::Blue;
leds(star13) = CRGB::White;
leds(star14) = CRGB::White;
leds(star15) = CRGB::White;
leds(star16) = CRGB::Red;
leds(star17) = CRGB::Green;
leds(star18) = CRGB::Blue;
leds(star19) = CRGB::SkyBlue;
leds(star20) = CRGB::LimeGreen;
leds(star21) = CRGB::Pink;
leds(star22) = CRGB::Red;
leds(star23) = CRGB::Green;
leds(star24) = CRGB::Blue;

FastLED.show();
delay(30);
}

void Matrix()
{
int star1, star2, star3, star4;
star1 = random16(64);
star2 = random16(64);
star3 = random16(64);
star4 = random16(64);

leds.ShiftDown();
leds(star1, leds.Height()-1) = CRGB::Green;
leds(star2, leds.Height()-1) = CRGB::Green;
leds(star3, leds.Height()-1) = CRGB::Green;
leds(star4, leds.Height()-1) = CRGB::Green;

FastLED.show();
delay(15);
}

void Brow()
{
  Sprites.RemoveSprite(&SprMushroom);
  Sprites.RemoveSprite(&SprMarioRight);
  Sprites.RemoveSprite(&SprLuigiRight);
  Sprites.RemoveSprite(&SprGoomba);
  Sprites.RemoveSprite(&SprMushroom2);
  Sprites.RemoveSprite(&SprMarioRight2);
  Sprites.RemoveSprite(&SprLuigiRight2);
  Sprites.RemoveSprite(&SprGoomba2);
  Sprites.RemoveSprite(&SprCompCube1);
  Sprites.RemoveSprite(&SprCompCube2);
  Sprites.RemoveSprite(&SprCompCube3);
  Sprites.RemoveSprite(&SprCompCube4);
  Sprites.RemoveSprite(&SprMaus);
  Sprites.RemoveSprite(&SprLink);
  Sprites.RemoveSprite(&SprOctorok);
  Sprites.RemoveSprite(&SprFairy);
  Sprites.RemoveSprite(&SprTriforce);
  Sprites.RemoveSprite(&SprLink2);
  Sprites.RemoveSprite(&SprOctorok2);
  Sprites.RemoveSprite(&SprFairy2);
  Sprites.RemoveSprite(&SprTriforce2);
  
    for (int16_t x=0; x<64; x++)
    {
      for (int16_t y=0; y<16; y++)
      {
        leds(x, y) = CHSV(150,200,90);
      }
    }
  randbrow = random8(1,150);
  Sprites.UpdateSprites();
  Sprites.DetectCollisions();
  if (eye_count == 0)
  {
  SprBrow.SetPositionFrameMotionOptions(20/*X*/, 1/*Y*/, 0/*Frame*/, 2/*FrameRate*/, 0/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
  Sprites.AddSprite(&SprBrow);
  eye_count = 1;
  }
if (SprBrow.GetCurrentFrame() != 19)
{
  if (randbrow == 2)
  {
    for (int right=SprBrow.m_X; right > 11; right--)
    {
      FastLED.clear();
        for (int16_t x=0; x<64; x++)
     {
        for (int16_t y=0; y<16; y++)
        {
          leds(x, y) = CHSV(150,200,90);
        }
      }
  SprBrow.SetPosition(right,1);
  Sprites.RenderSprites();
  FastLED.delay(40);
  }
 }

  if (randbrow == 5)
  {
    for (int right=SprBrow.m_X; right < 29; right++)
    {
      FastLED.clear();
        for (int16_t x=0; x<64; x++)
     {
        for (int16_t y=0; y<16; y++)
        {
          leds(x, y) = CHSV(150,200,90);
        }
      }
  SprBrow.SetPosition(right,1);
  Sprites.RenderSprites();
  FastLED.delay(40);
  }
 }
   if (randbrow == 8 || randbrow == 10 || randbrow == 16 || randbrow == 100 | randbrow == 98 || randbrow == 69)
  {
    if (SprBrow.m_X > 20)
    {
        for (int right=SprBrow.m_X; right > 19; right--)
        {
          FastLED.clear();
            for (int16_t x=0; x<64; x++)
         {
            for (int16_t y=0; y<16; y++)
            {
              leds(x, y) = CHSV(150,200,90);
            }
          }
      SprBrow.SetPosition(right,1);
      Sprites.RenderSprites();
      FastLED.delay(40);
      }
    }
        if (SprBrow.m_X < 20)
    {
        for (int right=SprBrow.m_X; right < 21; right++)
        {
          FastLED.clear();
            for (int16_t x=0; x<64; x++)
         {
            for (int16_t y=0; y<16; y++)
            {
              leds(x, y) = CHSV(150,200,90);
            }
          }
      SprBrow.SetPosition(right,1);
      Sprites.RenderSprites();
      FastLED.delay(40);
      }
    }
    
 }
  else
  {
    randbrow = randbrow;
  }
}

  Sprites.RenderSprites();
  FastLED.show();
  FastLED.delay(30);
  count = 0;
  mcount = 0;
  zcount = 0;
  cube_count = 0;
  mauscount = 0;
}

void CompCube()
{
  Sprites.RemoveSprite(&SprMushroom);
  Sprites.RemoveSprite(&SprMarioRight);
  Sprites.RemoveSprite(&SprLuigiRight);
  Sprites.RemoveSprite(&SprGoomba);
  Sprites.RemoveSprite(&SprMushroom2);
  Sprites.RemoveSprite(&SprMarioRight2);
  Sprites.RemoveSprite(&SprLuigiRight2);
  Sprites.RemoveSprite(&SprGoomba2);
  Sprites.RemoveSprite(&SprBrow);
  Sprites.RemoveSprite(&SprMaus);
  Sprites.RemoveSprite(&SprLink);
  Sprites.RemoveSprite(&SprOctorok);
  Sprites.RemoveSprite(&SprFairy);
  Sprites.RemoveSprite(&SprTriforce);
  Sprites.RemoveSprite(&SprLink2);
  Sprites.RemoveSprite(&SprOctorok2);
  Sprites.RemoveSprite(&SprFairy2);
  Sprites.RemoveSprite(&SprTriforce2);
  
  FastLED.clear();
  Sprites.UpdateSprites();
  Sprites.DetectCollisions();
  if (cube_count == 0)
    {
    SprCompCube1.SetPositionFrameMotionOptions(0/*X*/, 1/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprCompCube1);
    SprCompCube3.SetPositionFrameMotionOptions(32/*X*/, 1/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprCompCube3);
    cube_count = 1;
    }

    if (SprCompCube1.m_X == 50)
   {
    SprCompCube2.SetPositionFrameMotionOptions(-14/*X*/, 1/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprCompCube2);
   }

       if (SprCompCube2.m_X == 50)
   {
    SprCompCube1.SetPositionFrameMotionOptions(-14/*X*/, 1/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprCompCube1);
   }

       if (SprCompCube3.m_X == 50)
   {
    SprCompCube4.SetPositionFrameMotionOptions(-14/*X*/, 1/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprCompCube4);
   }

       if (SprCompCube4.m_X == 50)
   {
    SprCompCube3.SetPositionFrameMotionOptions(-14/*X*/, 1/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprCompCube3);
   }
      Sprites.RenderSprites();
      FastLED.delay(30);
        count = 0;
  mcount = 0;
  zcount = 0;
  eye_count = 0;
  mauscount = 0;
}

void Fireplace () {
  FastLED.clear();
  static unsigned int spark[WIDTH]; // base heat
  CRGB stack[WIDTH][HEIGHT];        // stacks that are cooler
 
  // 1. Generate sparks to re-heat
  for( int i = 0; i < WIDTH; i++) {
    if (spark[i] < HOT ) {
      int base = HOT * 2;
      spark[i] = random16( base, MAXHOT );
    }
  }
  
  // 2. Cool all the sparks
  for( int i = 0; i < WIDTH; i++) {
    spark[i] = qsub8( spark[i], random8(0, COOLING) );
  }
  
  // 3. Build the stack
  /*    This works on the idea that pixels are "cooler"
        as they get further from the spark at the bottom */
  for( int i = 0; i < WIDTH; i++) {
    unsigned int heat = constrain(spark[i], HOT/2, MAXHOT);
    for( int j = HEIGHT-1; j >= 0; j--) {
      /* Calculate the color on the palette from how hot this
         pixel is */
      byte index = constrain(heat, 0, HOT);
      stack[i][j] = ColorFromPalette( gPal, index );
      
      /* The next higher pixel will be "cooler", so calculate
         the drop */
      unsigned int drop = random8(0,HOT);
      if (drop > heat) heat = 0; // avoid wrap-arounds from going "negative"
      else heat -= drop;
 
      heat = constrain(heat, 0, MAXHOT);
    }
  }
  // 4. map stacks to led array
  for( int i = 0; i < WIDTH; i++) {
  for( int j = 0; j < HEIGHT; j++) {
     leds(i, j) = stack[i][HEIGHT-j-1];
  }
  }
  FastLED.delay(30);
}

void fillnoise8() {
  for(int i = 0; i < MAX_DIMENSION; i++) 
  {
    int ioffset = scale * i;
    for(int j = 0; j < MAX_DIMENSION; j++) 
    {
      int joffset = scale * j;
      noise[i][j] = inoise8(f + ioffset,g + joffset,h);
    }
  }
  h += speed;
}

void Noise() {
  FastLED.clear();
  
  static uint8_t ihue=0;
  fillnoise8();
  for(int i = 0; i < 32; i++) 
  {
    for(int j = 0; j < HEIGHT; j++) 
    {
       leds(i,j) = CHSV(ihue + (noise[j][i]>>2),200,noise[i][j]);
    }
  }
  ihue+=random8(0,15);
  leds.HorizontalMirror();
  LEDS.show();
}

void Maus()
{
    Sprites.RemoveSprite(&SprMushroom);
    Sprites.RemoveSprite(&SprMarioRight);
    Sprites.RemoveSprite(&SprLuigiRight);
    Sprites.RemoveSprite(&SprGoomba);
    Sprites.RemoveSprite(&SprMushroom2);
    Sprites.RemoveSprite(&SprMarioRight2);
    Sprites.RemoveSprite(&SprLuigiRight2);
    Sprites.RemoveSprite(&SprGoomba2);
    Sprites.RemoveSprite(&SprBrow);
    Sprites.RemoveSprite(&SprCompCube1);
    Sprites.RemoveSprite(&SprCompCube2);
    Sprites.RemoveSprite(&SprCompCube3);
    Sprites.RemoveSprite(&SprCompCube4);
    Sprites.RemoveSprite(&SprLink);
    Sprites.RemoveSprite(&SprOctorok);
    Sprites.RemoveSprite(&SprFairy);
    Sprites.RemoveSprite(&SprTriforce);
    Sprites.RemoveSprite(&SprLink2);
    Sprites.RemoveSprite(&SprOctorok2);
    Sprites.RemoveSprite(&SprFairy2);
    Sprites.RemoveSprite(&SprTriforce2);

    fadeToBlackBy( leds[0], 1024, 50);
    //FastLED.clear();
    Sprites.UpdateSprites();
    if (mauscount == 0)
    {
    	SprMaus.SetPositionFrameMotionOptions(20/*X*/, 0/*Y*/, 0/*Frame*/, 6/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION | SPRITE_X_KEEPIN | SPRITE_Y_KEEPIN);
  	Sprites.AddSprite(&SprMaus);
    	mauscount = 1;
    }
    
    Sprites.RenderSprites();
    
    FastLED.show();
  count = 0;
  count2 = 0;
  mcount = 0;
  zcount = 0;
  cube_count = 0;
  eye_count=0;
}

void Circles()
{
  fadeToBlackBy( leds[0], 1024, 10);
  leds.DrawCircle(random16(WIDTH), random16(HEIGHT), random16(1,12), CHSV(gHue,255,200));
  //FastLED.delay(20);
}

void Lines()
{
  fadeToBlackBy( leds[0], 1024, 15);
  leds.DrawLine(random16(64), random16(16), random16(64), random16(16), CHSV(gHue,255,200));
}

void slantBars() 
{

  static byte slantPos = 0;
for (int16_t x=0; x<64; x++)
    {
      for (int16_t y=0; y<16; y++)
      {
  //for (byte x = 0; x < MATRIX_WIDTH; x++) {
    //for (byte y = MATRIX_HEIGHT; y > MATRIX_HEIGHT; y--) {
      leds(x, y) = CHSV(gHue, 255, squarewave8(x * 16 + y * 16 + slantPos));
    }
  }

  slantPos -= 6;
FastLED.delay(10);
}

void plasma2() {

  static byte offset  = 0; // counter for radial color wave motion
  static int plasVector = 0; // counter for orbiting plasma center

  // Calculate current center of plasma pattern (can be offscreen)
  int xOffset = cos8(plasVector / 256);
  int yOffset = sin8(plasVector / 256);

  // Draw one frame of the animation into the LED array
for (int16_t x=0; x<64; x++)
    {
      for (int16_t y=0; y<16; y++)
      {
      byte color = sin8(sqrt(sq(((float)x - 7.5) * 10 + xOffset - 127) + sq(((float)y - 2) * 10 + yOffset - 127)) + offset);
      leds(x, y) = CHSV(color, 255, 255);
    }
  }
    offset++; // wraps at 255 for sin8
  plasVector += 1024; // using an int for slower orbit (wraps at 65536)
}


void threeSine() {

  static byte sineOffset = 0; // counter for current position of sine waves

  // Draw one frame of the animation into the LED array
for (int16_t x=0; x<64; x++)
    {
      for (int16_t y=0; y<16; y++)
      {

      // Calculate "sine" waves with varying periods
      // sin8 is used for speed; cos8, quadwave8, or triwave8 would also work here
      byte sinDistanceR = qmul8(abs(y * (255 / MATRIX_HEIGHT) - quadwave8(sineOffset * 2 + x * 4)), 2);
      byte sinDistanceG = qmul8(abs(y * (255 / MATRIX_HEIGHT) - quadwave8(sineOffset * 3 + x * 4)), 2);
      byte sinDistanceB = qmul8(abs(y * (255 / MATRIX_HEIGHT) - quadwave8(sineOffset * 4 + x * 4)), 2);

      leds(x, y) = CRGB(255 - sinDistanceR, 255 - sinDistanceG, 255 - sinDistanceB);
    }
  }

  sineOffset++; // byte will wrap from 255 to 0, matching sin8 0-255 cycle
  FastLED.delay(10);
}


void rider() {

  static byte riderPos = 0;

  // Draw one frame of the animation into the LED array
  for (byte x = 0; x < 64; x++) {
    int brightness = abs(x * (256 / 64) - triwave8(riderPos) * 2 + 127) * 3;
    if (brightness > 255) brightness = 255;
    brightness = 255 - brightness;
    CRGB riderColor = CHSV(gHue, 255, brightness);
    for (byte y = 0; y <  16; y++) {
      leds(x, y) = riderColor;
    }
  }
  riderPos++;
}

void quad()
{
  static byte riderPos = 0;

  // Draw one frame of the animation into the LED array
  for (byte x = 0; x < 64; x++) {

    for (byte y = 0; y <  16; y++) {
          int brightness = abs(x * (256 / 64) - quadwave8(riderPos) * 2 + 127) * 3;
    if (brightness > 255) brightness = 255;
    brightness = 255 - brightness;
    CRGB riderColor = CHSV(gHue, 255, brightness);
      leds(x, y) = riderColor;
    }
  }
  riderPos++;
}


