#include <FastLED.h>

#include <LEDMatrix.h>

// Change the next 6 defines to match your matrix type and size


#define DATA_PIN    11
#define CLK_PIN   13
#define CHIPSET    APA102
#define COLOR_ORDER BGR

#define MATRIX_WIDTH   64
#define MATRIX_HEIGHT  -16
#define MATRIX_TYPE    VERTICAL_ZIGZAG_MATRIX

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

uint8_t hue;
int16_t counter;

void setup()
{
  FastLED.addLeds<CHIPSET, DATA_PIN, CLK_PIN, COLOR_ORDER, DATA_RATE_MHZ(5)>(leds[0], leds.Size()).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(20);
  FastLED.clear(true);
//  delay(500);
//  FastLED.showColor(CRGB::Red);
//  delay(1000);
//  FastLED.showColor(CRGB::Lime);
//  delay(1000);
//  FastLED.showColor(CRGB::Blue);
//  delay(1000);
//  FastLED.showColor(CRGB::White);
  delay(1000);
  FastLED.clear(true);

  hue = 0;
  counter = 0;
}


void loop()
{
  int16_t sx, sy, x, y;
  uint8_t h;

  FastLED.clear();
  
  h = hue;
  if (counter < 1125)
  {
    // ** Fill LED's with diagonal stripes
    for (x=0; x<(leds.Width()+leds.Height()); ++x)
    {
      leds.DrawLine(x - leds.Height(), leds.Height() - 1, x, 0, CHSV(h, 255, 192));
      h+=16;
    }
  }
  else
  {
    // ** Fill LED's with horizontal stripes
    for (y=0; y<leds.Height(); ++y)
    {
      leds.DrawLine(0, y, leds.Width() - 1, y, CHSV(h, 255, 192));
      h+=16;
    }
  }
  hue+=4;

  if (counter < 0)
    ;
  else if (counter < 375)
    leds.HorizontalMirror();
  else if (counter < 625)
    leds.VerticalMirror();
  else if (counter < 875)
    leds.QuadrantMirror();
  else if (counter < 1250)
    leds.QuadrantRotateMirror();
  //else if (counter < 1250)
    //;
  else if (counter < 1500)
    leds.TriangleTopMirror();
  else if (counter < 1750)
    leds.TriangleBottomMirror();
  else if (counter < 2000)
    leds.QuadrantTopTriangleMirror();
  else if (counter < 2250)
    leds.QuadrantBottomTriangleMirror();

  counter++;
  if (counter >= 2250)
    counter = 0;
  FastLED.show();
  FastLED.delay(20);
}

