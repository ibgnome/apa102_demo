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


#define RAINBOW_WIDTH    16
#define RAINBOW_HEIGHT   10
const uint8_t RainbowData[] = 
{
  B8_3BIT(01111111),B8_3BIT(11111110),
  B8_3BIT(11222222),B8_3BIT(22222211),
  B8_3BIT(12233333),B8_3BIT(33333221),
  B8_3BIT(12334444),B8_3BIT(44443321),
  B8_3BIT(12344555),B8_3BIT(55544321),
  B8_3BIT(12345566),B8_3BIT(66554321),
  B8_3BIT(12345667),B8_3BIT(76654321),
  B8_3BIT(12345677),B8_3BIT(77654321),
  B8_3BIT(12345670),B8_3BIT(07654321),
  B8_3BIT(12345670),B8_3BIT(07654321),
};
const uint8_t RainbowMask[] = 
{
  B8_1BIT(01111111),B8_1BIT(11111110),
  B8_1BIT(11111111),B8_1BIT(11111111),
  B8_1BIT(11111111),B8_1BIT(11111111),
  B8_1BIT(11111111),B8_1BIT(11111111),
  B8_1BIT(11111111),B8_1BIT(11111111),
  B8_1BIT(11111111),B8_1BIT(11111111),
  B8_1BIT(11111111),B8_1BIT(11111111),
  B8_1BIT(11111111),B8_1BIT(11111111),
  B8_1BIT(11111110),B8_1BIT(01111111),
  B8_1BIT(11111110),B8_1BIT(01111111),
};
struct CRGB RainbowColTable[7] = { CHSV(216, 255, 255), CHSV(180, 255, 255), CHSV(144, 255, 255), CHSV(108, 255, 255), CHSV(72, 255, 255), CHSV(36, 255, 255), CHSV(0, 255, 255) };

#define SHAPE_WIDTH    7
#define SHAPE_HEIGHT   7
const uint8_t ShapeData[] = 
{
  B8_1BIT(00010000),
  B8_1BIT(00111000),
  B8_1BIT(01111100),
  B8_1BIT(11111110),
  B8_1BIT(01111100),
  B8_1BIT(00111000),
  B8_1BIT(00010000),
};
struct CRGB ShapeColTable[1] = { CRGB::Red };
struct CRGB ShapeColTable2[1] = { CRGB::DarkOrange };
struct CRGB ShapeColTable3[1] = { CRGB::Yellow };
struct CRGB ShapeColTable4[1] = { CRGB::Green };
cLEDSprites Sprites(&leds);
cSprite Rainbow(RAINBOW_WIDTH, RAINBOW_HEIGHT, RainbowData, 1, _3BIT, RainbowColTable, RainbowMask);
cSprite Shape(SHAPE_WIDTH, SHAPE_HEIGHT, ShapeData, 1, _1BIT, ShapeColTable, ShapeData);
cSprite Shape2(SHAPE_WIDTH, SHAPE_HEIGHT, ShapeData, 1, _1BIT, ShapeColTable2, ShapeData);
cSprite Shape3(SHAPE_WIDTH, SHAPE_HEIGHT, ShapeData, 1, _1BIT, ShapeColTable3, ShapeData);
cSprite Shape4(SHAPE_WIDTH, SHAPE_HEIGHT, ShapeData, 1, _1BIT, ShapeColTable4, ShapeData);
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

  //Rainbow.SetPositionFrameMotionOptions((MATRIX_WIDTH - RAINBOW_WIDTH) / 2/*X*/, (MATRIX_HEIGHT - RAINBOW_HEIGHT) / 2/*Y*/, 0/*Frame*/, 0/*FrameRate*/, 1/*XChange*/, 1/*XRate*/, 1/*YChange*/, 1/*YRate*/,SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN | SPRITE_Y_KEEPIN | SPRITE_DETECT_COLLISION);
  //Sprites.AddSprite(&Rainbow);

  Shape.SetPositionFrameMotionOptions(0/*X*/, 0/*Y*/, 0/*Frame*/, 0/*FrameRate*/, +1/*XChange*/, 1/*XRate*/, +1/*YChange*/, 1/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN | SPRITE_Y_KEEPIN | SPRITE_DETECT_COLLISION);
  Sprites.AddSprite(&Shape);
  Shape2.SetPositionFrameMotionOptions(10/*X*/, 4/*Y*/, 0/*Frame*/, 1/*FrameRate*/, +1/*XChange*/, 1/*XRate*/, +1/*YChange*/, 1/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN | SPRITE_Y_KEEPIN | SPRITE_DETECT_COLLISION);
  Sprites.AddSprite(&Shape2);
  Shape3.SetPositionFrameMotionOptions(20/*X*/, 8/*Y*/, 0/*Frame*/, 2/*FrameRate*/, +1/*XChange*/, 1/*XRate*/, +1/*YChange*/, 1/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN | SPRITE_Y_KEEPIN | SPRITE_DETECT_COLLISION);
  Sprites.AddSprite(&Shape3);
  Shape4.SetPositionFrameMotionOptions(30/*X*/, 12/*Y*/, 0/*Frame*/, 3/*FrameRate*/, +1/*XChange*/, 1/*XRate*/, +1/*YChange*/, 1/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN | SPRITE_Y_KEEPIN | SPRITE_DETECT_COLLISION);
  Sprites.AddSprite(&Shape4);
}


void loop()
{
  FastLED.clear();
  Sprites.UpdateSprites();
  Sprites.RenderSprites();
  FastLED.show();
  delay(10);
}
