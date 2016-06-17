#include <FastLED.h>

#include <LEDMatrix.h>
#include <LEDSprites.h>

// Change the next 6 defines to match your matrix type and size

#define DATA_PIN    11
#define CLK_PIN   13
#define CHIPSET    APA102
#define COLOR_ORDER BGR

#define MATRIX_WIDTH   64
#define MATRIX_HEIGHT  -16
#define MATRIX_TYPE    VERTICAL_ZIGZAG_MATRIX

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;


cLEDSprites Sprites(&leds);

#define MY_SPRITE_WIDTH  11
#define MY_SPRITE_HEIGHT 10
#define PACMAN_FRAMES  3
#define PINKY_FRAMES  2

#define POWER_PILL_SIZE	4
const uint8_t PowerPillData[] = 
{
  B8_1BIT(01100000),
  B8_1BIT(11110000),
  B8_1BIT(11110000),
  B8_1BIT(01100000)
};
const struct CRGB PowerPillColTab[] =  {  CRGB(48, 48, 255)  };

const uint8_t PacmanRightData[] = 
{
  // Pacman Open
  B8_2BIT(00021112),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(00000000),
  B8_2BIT(21111110),B8_2BIT(00000000),
  B8_2BIT(11111000),B8_2BIT(00000000),
  B8_2BIT(11111000),B8_2BIT(00000000),
  B8_2BIT(21111110),B8_2BIT(00000000),
  B8_2BIT(01111111),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00021112),B8_2BIT(00000000),
  // Pacman Half
  B8_2BIT(00021112),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(11111200),B8_2BIT(00000000),
  B8_2BIT(11111200),B8_2BIT(00000000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00021112),B8_2BIT(00000000),
  // Pacman Closed
  B8_2BIT(00021112),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00021112),B8_2BIT(00000000)
};
const uint8_t PacmanRightMask[] = 
{
  // Pacman Open
  B8_1BIT(00011111),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(01111111),B8_1BIT(00000000),
  B8_1BIT(11111110),B8_1BIT(00000000),
  B8_1BIT(11111000),B8_1BIT(00000000),
  B8_1BIT(11111000),B8_1BIT(00000000),
  B8_1BIT(11111110),B8_1BIT(00000000),
  B8_1BIT(01111111),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(00011111),B8_1BIT(00000000),
  // Pacman Half
  B8_1BIT(00011111),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111100),B8_1BIT(00000000),
  B8_1BIT(11111100),B8_1BIT(00000000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(00011111),B8_1BIT(00000000),
  // Pacman Closed
  B8_1BIT(00011111),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(00011111),B8_1BIT(00000000)
};
const struct CRGB PacmanRightColTab[] =  {  CRGB(255, 255, 0), CRGB(100, 100, 0), CRGB(255, 255, 255)  };

const uint8_t PinkyData[] = 
{
  // Pinky Frame 1
  B8_2BIT(00001110),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(01122212),B8_2BIT(22000000),
  B8_2BIT(11122312),B8_2BIT(23100000),
  B8_2BIT(11122212),B8_2BIT(22100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11001110),B8_2BIT(01100000),
  // Pinky Frame 2
  B8_2BIT(00001110),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(01122212),B8_2BIT(22000000),
  B8_2BIT(11122312),B8_2BIT(23100000),
  B8_2BIT(11122212),B8_2BIT(22100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(10011011),B8_2BIT(00100000),
};
const uint8_t PinkyMask[] = 
{
  // Pinky Frame 1
  B8_1BIT(00001110),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11001110),B8_1BIT(01100000),
  // Pinky Frame 2
  B8_1BIT(00001110),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(10011011),B8_1BIT(00100000),
};
const struct CRGB PinkyColTab[] =  {  CRGB(255, 0, 0), CRGB(255, 255, 255), CRGB(0, 0, 255)  };

const uint8_t PacmanLeftData[] = 
{
  // Pacman Open
  B8_2BIT(00021112),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00011111),B8_2BIT(11000000),
  B8_2BIT(00001111),B8_2BIT(11200000),
  B8_2BIT(00000011),B8_2BIT(11100000),
  B8_2BIT(00000011),B8_2BIT(11100000),
  B8_2BIT(00001111),B8_2BIT(11200000),
  B8_2BIT(00011111),B8_2BIT(11000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00021112),B8_2BIT(00000000),
  // Pacman Half
  B8_2BIT(00021112),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(00000211),B8_2BIT(11100000),
  B8_2BIT(00000211),B8_2BIT(11100000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00021112),B8_2BIT(00000000),
  // Pacman Closed
  B8_2BIT(00021112),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00021112),B8_2BIT(00000000)
};
const uint8_t PacmanLeftMask[] = 
{
  // Pacman Open
  B8_1BIT(00011111),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(00011111),B8_1BIT(11000000),
  B8_1BIT(00001111),B8_1BIT(11100000),
  B8_1BIT(00000011),B8_1BIT(11100000),
  B8_1BIT(00000011),B8_1BIT(11100000),
  B8_1BIT(00001111),B8_1BIT(11100000),
  B8_1BIT(00011111),B8_1BIT(11000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(00011111),B8_1BIT(00000000),
  // Pacman Half
  B8_1BIT(00011111),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(00000111),B8_1BIT(11100000),
  B8_1BIT(00000111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(00011111),B8_1BIT(00000000),
  // Pacman Closed
  B8_1BIT(00011111),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(00011111),B8_1BIT(00000000)
};
const struct CRGB PacmanLeftColTab[] =  {  CRGB(255, 255, 0), CRGB(100, 100, 0), CRGB(255, 255, 255)  };

const uint8_t GhostData[] = 
{
  // Ghost Frame 1
  B8_2BIT(00001110),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(01122122),B8_2BIT(11000000),
  B8_2BIT(11122122),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11131313),B8_2BIT(11100000),
  B8_2BIT(11313131),B8_2BIT(31100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11001110),B8_2BIT(01100000),
  // Ghost Frame 2
  B8_2BIT(00001110),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(01122122),B8_2BIT(11000000),
  B8_2BIT(11122122),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11131313),B8_2BIT(11100000),
  B8_2BIT(11313131),B8_2BIT(31100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(10011011),B8_2BIT(00100000)
};
const uint8_t GhostMask[] = 
{
  // Ghost Frame 1
  B8_1BIT(00001110),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11001110),B8_1BIT(01100000),
  // Ghost Frame 2
  B8_1BIT(00001110),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(10011011),B8_1BIT(00100000)
};
const struct CRGB GhostColTab[] =  {  CRGB(0, 0, 255), CRGB(255, 255, 255), CRGB(255, 90, 120)  };

const uint8_t S200Data[] = 
{
  B8_1BIT(00000000),B8_1BIT(00000000),
  B8_1BIT(01000100),B8_1BIT(01000000),
  B8_1BIT(10101010),B8_1BIT(10100000),
  B8_1BIT(10101010),B8_1BIT(10100000),
  B8_1BIT(00101010),B8_1BIT(10100000),
  B8_1BIT(01001010),B8_1BIT(10100000),
  B8_1BIT(11100100),B8_1BIT(01000000),
  B8_1BIT(00000000),B8_1BIT(00000000),
  B8_1BIT(00000000),B8_1BIT(00000000),
  B8_1BIT(00000000),B8_1BIT(00000000)
};
const struct CRGB S200ColTab[] =  {  CRGB(0, 192, 255)  };

const uint8_t EyesData[] = 
{
  B8_2BIT(00000000),B8_2BIT(00000000),
  B8_2BIT(00000000),B8_2BIT(00000000),
  B8_2BIT(01110001),B8_2BIT(11000000),
  B8_2BIT(11111011),B8_2BIT(11100000),
  B8_2BIT(11122011),B8_2BIT(12200000),
  B8_2BIT(11122011),B8_2BIT(12200000),
  B8_2BIT(01110001),B8_2BIT(11000000),
  B8_2BIT(00000000),B8_2BIT(00000000),
  B8_2BIT(00000000),B8_2BIT(00000000),
  B8_2BIT(00000000),B8_2BIT(00000000)
};
const uint8_t EyesMask[] = 
{
  B8_1BIT(00000000),B8_1BIT(00000000),
  B8_1BIT(00000000),B8_1BIT(00000000),
  B8_1BIT(01110001),B8_1BIT(11000000),
  B8_1BIT(11111011),B8_1BIT(11100000),
  B8_1BIT(11111011),B8_1BIT(11100000),
  B8_1BIT(11111011),B8_1BIT(11100000),
  B8_1BIT(01110001),B8_1BIT(11000000),
  B8_1BIT(00000000),B8_1BIT(00000000),
  B8_1BIT(00000000),B8_1BIT(00000000),
  B8_1BIT(00000000),B8_1BIT(00000000)
};
const struct CRGB EyesColTab[] =  {  CRGB(255, 255, 255), CRGB(0, 0, 255), CRGB(0, 0, 0)  };

cSprite SprPacmanRight(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PacmanRightData, PACMAN_FRAMES, _2BIT, PacmanRightColTab, PacmanRightMask);
cSprite SprPinky(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PinkyData, PINKY_FRAMES, _2BIT, PinkyColTab, PinkyMask);
cSprite SprPacmanLeft(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PacmanLeftData, PACMAN_FRAMES, _2BIT, PacmanLeftColTab, PacmanLeftMask);
cSprite SprGhost(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, GhostData, PINKY_FRAMES, _2BIT, GhostColTab, GhostMask);
cSprite SprPill(POWER_PILL_SIZE, POWER_PILL_SIZE, PowerPillData, 1, _1BIT, PowerPillColTab, PowerPillData);
cSprite Spr200(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, S200Data, 1, _1BIT, S200ColTab, S200Data);
cSprite SprEyes(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, EyesData, 1, _2BIT, EyesColTab, EyesMask);


void setup()
{
  FastLED.addLeds<CHIPSET, DATA_PIN, CLK_PIN, COLOR_ORDER, DATA_RATE_MHZ(5)>(leds[0], leds.Size());
  FastLED.setBrightness(20);
  FastLED.clear(true);
  delay(500);
  //FastLED.showColor(CRGB::Red);
  //delay(1000);
  //FastLED.showColor(CRGB::Lime);
  //delay(1000);
  //FastLED.showColor(CRGB::Blue);
  //delay(1000);
  FastLED.showColor(CRGB::White);
  delay(1000);
  FastLED.show();

  SprPill.SetPositionFrameMotionOptions(MATRIX_WIDTH - POWER_PILL_SIZE - 1/*X*/, (MY_SPRITE_HEIGHT - POWER_PILL_SIZE) / 2/*Y*/, 0/*Frame*/, 0/*FrameRate*/, 0/*XChange*/, 0/*XRate*/, 0/*YChange*/, 0/*YRate*/);
  Sprites.AddSprite(&SprPill);
  SprPacmanRight.SetPositionFrameMotionOptions(-12/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
  Sprites.AddSprite(&SprPacmanRight);
  SprPinky.SetPositionFrameMotionOptions(-26/*X*/, 0/*Y*/, 0/*Frame*/, 2/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE);
  Sprites.AddSprite(&SprPinky);
}


void loop()
{
  FastLED.clear();
  Sprites.UpdateSprites();
  Sprites.DetectCollisions();
  if (Sprites.IsSprite(&SprPinky))
  {
    if (SprPill.GetFlags() & SPRITE_COLLISION)
    {
      Sprites.RemoveSprite(&SprPinky);
      Sprites.RemoveSprite(&SprPacmanRight);
      Sprites.RemoveSprite(&SprPill);
      SprGhost.SetPositionFrameMotionOptions(SprPinky.m_X, SprPinky.m_Y, 0, 3, -1, 3, 0, 0, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
      Sprites.AddSprite(&SprGhost);
      SprPacmanLeft.SetPositionFrameMotionOptions(SprPacmanRight.m_X, SprPacmanRight.m_Y, 0, 4, -1, 2, 0, 0, SPRITE_DETECT_EDGE);
      Sprites.AddSprite(&SprPacmanLeft);
    }
  }
  else if (Sprites.IsSprite(&SprGhost))
  {
    if (SprGhost.GetFlags() & SPRITE_COLLISION)
    {
      Sprites.RemoveSprite(&SprGhost);
      Spr200.SetPositionFrameMotionOptions(SprGhost.m_X, SprGhost.m_Y, 0, 0, 0, 0, 0, 0);
      Sprites.AddSprite(&Spr200);
      Sprites.ChangePriority(&Spr200, SPR_BACK);
    }
  }
  else if (Sprites.IsSprite(&Spr200))
  {
    if (SprPacmanLeft.GetFlags() & SPRITE_EDGE_X_MIN)
    {
      Sprites.RemoveSprite(&Spr200);
      SprEyes.SetPositionFrameMotionOptions(Spr200.m_X, Spr200.m_Y, 0, 0, +1, 2, 0, 0, SPRITE_DETECT_EDGE);
      Sprites.AddSprite(&SprEyes);
      Sprites.ChangePriority(&SprEyes, SPR_BACK);
    }
  }
  else
  {
    if (SprEyes.GetFlags() & SPRITE_MATRIX_X_OFF)
    {
      Sprites.RemoveSprite(&SprEyes);
      Sprites.RemoveSprite(&SprPacmanLeft);
      SprPill.SetPositionFrameMotionOptions(MATRIX_WIDTH - POWER_PILL_SIZE - 1/*X*/, (MY_SPRITE_HEIGHT - POWER_PILL_SIZE) / 2/*Y*/, 0/*Frame*/, 0/*FrameRate*/, 0/*XChange*/, 0/*XRate*/, 0/*YChange*/, 0/*YRate*/);
      Sprites.AddSprite(&SprPill);
      SprPacmanRight.SetPositionFrameMotionOptions(-12/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
      Sprites.AddSprite(&SprPacmanRight);
      SprPinky.SetPositionFrameMotionOptions(-26/*X*/, 0/*Y*/, 0/*Frame*/, 2/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE);
      Sprites.AddSprite(&SprPinky);
    }
  }
  Sprites.RenderSprites();
  FastLED.show();
  delay(10);
}
