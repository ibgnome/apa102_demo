#include <FastLED.h>

#include <LEDMatrix.h>
#include <LEDSprites.h>

// Change the next 6 defines to match your matrix type and size


#define DATA_PIN    11
#define CLK_PIN   13
#define COLOR_ORDER    BGR
#define CHIPSET        APA102

#define MATRIX_WIDTH   64
#define MATRIX_HEIGHT  -16
#define MATRIX_TYPE    VERTICAL_ZIGZAG_MATRIX

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;


#define SHAPE_WIDTH    5
#define SHAPE_HEIGHT   16
const uint8_t ShapeData[] = 
{
  B8_1BIT(11111),
  B8_1BIT(11111),
  B8_1BIT(11111),
  B8_1BIT(11111),
  B8_1BIT(11111),
  B8_1BIT(11111),
  B8_1BIT(11111),
  B8_1BIT(11111),
  B8_1BIT(11111),
  B8_1BIT(11111),
  B8_1BIT(11111),
  B8_1BIT(11111),
  B8_1BIT(11111),
  B8_1BIT(11111),
  B8_1BIT(11111),
  B8_1BIT(11111),
  

};
struct CRGB ColTable[1] = { CRGB(64, 128, 255) };
cLEDSprites Sprites(&leds);
cSprite Shape(SHAPE_WIDTH, SHAPE_HEIGHT, ShapeData, 1, _1BIT, ColTable, ShapeData);


void setup()
{
  FastLED.addLeds<CHIPSET, DATA_PIN, CLK_PIN, COLOR_ORDER, DATA_RATE_MHZ(5)>(leds[0], leds.Size()).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(20);
  FastLED.clear(true);
  delay(500);
//  FastLED.showColor(CRGB::Red);
//  delay(1000);
//  FastLED.showColor(CRGB::Lime);
//  delay(1000);
//  FastLED.showColor(CRGB::Blue);
//  delay(1000);
//  FastLED.showColor(CRGB::White);
  delay(1000);
  FastLED.show();

  Shape.SetPositionFrameMotionOptions(0/*X*/, 0/*Y*/, 0/*Frame*/, 15/*FrameRate*/, +1/*XChange*/, 1/*XRate*/, 0/*YChange*/, 1/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN | SPRITE_Y_KEEPIN);
  Sprites.AddSprite(&Shape);
}


void loop()
{
  FastLED.clear();
  Sprites.UpdateSprites();
  Sprites.RenderSprites();
  FastLED.show();
  delay(50);
}
