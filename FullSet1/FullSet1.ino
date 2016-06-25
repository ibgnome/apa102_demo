#include <FastLED.h>

#include <LEDMatrix.h>
#include <LEDSprites.h>
#include <LEDText.h>
#include <Font12x16.h>
#include <FontMatrise.h>

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
#define MARIO_FRAMES  3

#define MARIO_SIZE 16

#define POWER_PILL_SIZE	4


#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

  cLEDText ScrollingMsg;

const unsigned char TxtDemo[] = { EFFECT_FRAME_RATE "\x02"
                                  EFFECT_HSV_AV "\x00\xff\xff\xff\xff\xff"
                                  EFFECT_SCROLL_LEFT "         DRAGONCON" 
                                  };
uint16_t Options;

int count;
uint8_t hue = 0;
int16_t counter = 0;
const uint8_t MarioData[] =
{
  // Mario Run 1
  B8_2BIT(00000111),B8_2BIT(11100000),
  B8_2BIT(00001111),B8_2BIT(11111100),
  B8_2BIT(00002222),B8_2BIT(33230000),
  B8_2BIT(00022323),B8_2BIT(33233300),
  B8_2BIT(00022322),B8_2BIT(33323330),
  B8_2BIT(00022233),B8_2BIT(33222200),
  B8_2BIT(00000333),B8_2BIT(33333000),
  B8_2BIT(00222221),B8_2BIT(12200000),
  B8_2BIT(33322221),B8_2BIT(11222333),
  B8_2BIT(33332221),B8_2BIT(31112233),
  B8_2BIT(33301111),B8_2BIT(11110220),
  B8_2BIT(00011111),B8_2BIT(11111220),
  B8_2BIT(00111111),B8_2BIT(11111220),
  B8_2BIT(02221110),B8_2BIT(01111220),
  B8_2BIT(02222000),B8_2BIT(00000000),
  B8_2BIT(00222200),B8_2BIT(00000000),
  // Pacman Half
  B8_2BIT(00000000),B8_2BIT(00000000),
  B8_2BIT(00000111),B8_2BIT(11100000),
  B8_2BIT(00001111),B8_2BIT(11111100),
  B8_2BIT(00002222),B8_2BIT(33230000),
  B8_2BIT(00022323),B8_2BIT(33233300),
  B8_2BIT(00022322),B8_2BIT(33323330),
  B8_2BIT(00022233),B8_2BIT(33222200),
  B8_2BIT(00000333),B8_2BIT(33333000),
  B8_2BIT(00002222),B8_2BIT(21233000),
  B8_2BIT(00033222),B8_2BIT(22233300),
  B8_2BIT(00333122),B8_2BIT(22233000),
  B8_2BIT(00222111),B8_2BIT(11110000),
  B8_2BIT(00221111),B8_2BIT(11110000),
  B8_2BIT(02221111),B8_2BIT(11100000),
  B8_2BIT(02200022),B8_2BIT(22000000),
  B8_2BIT(00000022),B8_2BIT(22200000),
  // Pacman Closed
  B8_2BIT(00000111),B8_2BIT(11100000),
  B8_2BIT(00001111),B8_2BIT(11111100),
  B8_2BIT(00002222),B8_2BIT(33230000),
  B8_2BIT(00022323),B8_2BIT(33233300),
  B8_2BIT(00022322),B8_2BIT(33323330),
  B8_2BIT(00022233),B8_2BIT(33222200),
  B8_2BIT(00000333),B8_2BIT(33333000),
  B8_2BIT(00022221),B8_2BIT(22200000),
  B8_2BIT(00222222),B8_2BIT(11220000),
  B8_2BIT(00222221),B8_2BIT(13113000),
  B8_2BIT(00222222),B8_2BIT(11111000),
  B8_2BIT(00112233),B8_2BIT(31111000),
  B8_2BIT(00011223),B8_2BIT(11110000),
  B8_2BIT(00001111),B8_2BIT(22220000),
  B8_2BIT(00002222),B8_2BIT(22222000),
  B8_2BIT(00002222),B8_2BIT(22000000)

  
};

const uint8_t MarioMask[] = 
{
  // Pacman Open
  B8_2BIT(00000111),B8_2BIT(11100000),
  B8_2BIT(00001111),B8_2BIT(11111100),
  B8_2BIT(00001111),B8_2BIT(11110000),
  B8_2BIT(00011111),B8_2BIT(11111100),
  B8_2BIT(00011111),B8_2BIT(11111110),
  B8_2BIT(00011111),B8_2BIT(11111100),
  B8_2BIT(00000111),B8_2BIT(11111000),
  B8_2BIT(00111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11111111),
  B8_2BIT(11111111),B8_2BIT(11111111),
  B8_2BIT(11101111),B8_2BIT(11110110),
  B8_2BIT(00011111),B8_2BIT(11111110),
  B8_2BIT(00111111),B8_2BIT(11111110),
  B8_2BIT(01111110),B8_2BIT(01111110),
  B8_2BIT(01111000),B8_2BIT(00000000),
  B8_2BIT(00111100),B8_2BIT(00000000),
  // Pacman Half
    // Pacman Open
  B8_2BIT(00000000),B8_2BIT(00000000),
  B8_2BIT(00000111),B8_2BIT(11100000),
  B8_2BIT(00001111),B8_2BIT(11111100),
  B8_2BIT(00001111),B8_2BIT(11110000),
  B8_2BIT(00011111),B8_2BIT(11111100),
  B8_2BIT(00011111),B8_2BIT(11111110),
  B8_2BIT(00011111),B8_2BIT(11111100),
  B8_2BIT(00000111),B8_2BIT(11111000),
  B8_2BIT(00001111),B8_2BIT(11111000),
  B8_2BIT(00011111),B8_2BIT(11111100),
  B8_2BIT(00111111),B8_2BIT(11111000),
  B8_2BIT(00111111),B8_2BIT(11110000),
  B8_2BIT(00111111),B8_2BIT(11110000),
  B8_2BIT(01111111),B8_2BIT(11100000),
  B8_2BIT(01100011),B8_2BIT(11000000),
  B8_2BIT(00000011),B8_2BIT(11100000),
  // Pacman Closed
  // Pacman Open
  B8_2BIT(00000111),B8_2BIT(11100000),
  B8_2BIT(00001111),B8_2BIT(11111100),
  B8_2BIT(00001111),B8_2BIT(11110000),
  B8_2BIT(00011111),B8_2BIT(11111100),
  B8_2BIT(00011111),B8_2BIT(11111110),
  B8_2BIT(00011111),B8_2BIT(11111100),
  B8_2BIT(00000111),B8_2BIT(11111000),
  B8_2BIT(00011111),B8_2BIT(11100000),
  B8_2BIT(00111111),B8_2BIT(11110000),
  B8_2BIT(00111111),B8_2BIT(11111000),
  B8_2BIT(00111111),B8_2BIT(11111000),
  B8_2BIT(00111111),B8_2BIT(11111000),
  B8_2BIT(00011111),B8_2BIT(11110000),
  B8_2BIT(00001111),B8_2BIT(11110000),
  B8_2BIT(00001111),B8_2BIT(11111000),
  B8_2BIT(00001111),B8_2BIT(11000000)
};

const struct CRGB MarioColTab[] =  {  CRGB::Red, CRGB::Brown, CRGB::Yellow  };


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
const struct CRGB BlinkyColTab[] =  {  CRGB::Pink, CRGB(255, 255, 255), CRGB(0, 0, 255)  };
const struct CRGB InkyColTab[] =  {  CRGB::Cyan, CRGB(255, 255, 255), CRGB(0, 0, 255)  };
const struct CRGB ClydeColTab[] =  {  CRGB::Orange, CRGB(255, 255, 255), CRGB(0, 0, 255)  };
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
cSprite SprMarioRight(MARIO_SIZE, MARIO_SIZE, MarioData, MARIO_FRAMES, _2BIT, MarioColTab, MarioMask);
cSprite SprPinky(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PinkyData, PINKY_FRAMES, _2BIT, PinkyColTab, PinkyMask);
cSprite SprBlinky(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PinkyData, PINKY_FRAMES, _2BIT, BlinkyColTab, PinkyMask);
cSprite SprInky(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PinkyData, PINKY_FRAMES, _2BIT, InkyColTab, PinkyMask);
cSprite SprClyde(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PinkyData, PINKY_FRAMES, _2BIT, ClydeColTab, PinkyMask);
cSprite SprPacmanLeft(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PacmanLeftData, PACMAN_FRAMES, _2BIT, PacmanLeftColTab, PacmanLeftMask);
cSprite SprGhost(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, GhostData, PINKY_FRAMES, _2BIT, GhostColTab, GhostMask);
cSprite SprPill(POWER_PILL_SIZE, POWER_PILL_SIZE, PowerPillData, 1, _1BIT, PowerPillColTab, PowerPillData);
cSprite Spr200(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, S200Data, 1, _1BIT, S200ColTab, S200Data);
cSprite SprEyes(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, EyesData, 1, _2BIT, EyesColTab, EyesMask);


void setup()
{
  FastLED.addLeds<CHIPSET, DATA_PIN, CLK_PIN, COLOR_ORDER, DATA_RATE_MHZ(5)>(leds[0], leds.Size()).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(20);
  FastLED.clear(true);
  delay(500);
  delay(1000);
  count = 0;
  FastLED.show();

    ScrollingMsg.SetFont(Font12x16Data);
  ScrollingMsg.Init(&leds, leds.Width(), ScrollingMsg.FontHeight() + 1, 0, 0);
  ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
  ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0xff, 0x00, 0xff);
  Options = INSTANT_OPTIONS_MODE;
  ScrollingMsg.SetOptionsChangeMode(Options);

  //SprPill.SetPositionFrameMotionOptions(MATRIX_WIDTH - POWER_PILL_SIZE - 1/*X*/, (MY_SPRITE_HEIGHT - POWER_PILL_SIZE) / 2/*Y*/, 0/*Frame*/, 0/*FrameRate*/, 0/*XChange*/, 0/*XRate*/, 0/*YChange*/, 0/*YRate*/);
  //Sprites.AddSprite(&SprPill);

//  SprPinky.SetPositionFrameMotionOptions(26/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE  | SPRITE_Y_KEEPIN);
//  Sprites.AddSprite(&SprPinky);
}
// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();

SimplePatternList gPatterns = { Dcon, Mario, TrippyRainbow};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current

void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  

  // do some periodic updates
  EVERY_N_SECONDS( 30 ) { nextPattern(); } // change patterns periodically
}

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void Mario()
{
  FastLED.clear();
  Sprites.UpdateSprites();
  Sprites.DetectCollisions();
  if (count == 0)
  {
  SprMarioRight.SetPositionFrameMotionOptions(0/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION | SPRITE_Y_KEEPIN);
  Sprites.AddSprite(&SprMarioRight);
  count = 1;
  }
  if (Sprites.IsSprite(&SprMarioRight))
  {
   if (SprMarioRight.GetFlags() & SPRITE_MATRIX_X_OFF)
   {
      Sprites.RemoveSprite(&SprMarioRight); 
      //Sprites.RemoveSprite(&SprPinky);  
      SprPacmanRight.SetPositionFrameMotionOptions(-10/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
      Sprites.AddSprite(&SprPacmanRight);
    
   }
  }
 else if (Sprites.IsSprite(&SprPacmanRight))
  {
   if (SprPacmanRight.GetFlags() & SPRITE_MATRIX_X_OFF)
   {
      Sprites.RemoveSprite(&SprPacmanRight); 
      //Sprites.RemoveSprite(&SprPinky);  
      SprPinky.SetPositionFrameMotionOptions(-10/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
      Sprites.AddSprite(&SprPinky);
    
   }
  }
  else if (Sprites.IsSprite(&SprPinky))
  {
 if ( SprPinky.GetFlags() & SPRITE_MATRIX_X_OFF)
  {
   Sprites.RemoveSprite(&SprPinky);
 //   Sprites.RemoveSprite(&SprMarioRight); 
   SprBlinky.SetPositionFrameMotionOptions(-10/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_Y_KEEPIN);
  Sprites.AddSprite(&SprBlinky);
  
 }
  }
  else if (Sprites.IsSprite(&SprBlinky))
  {
 if ( SprBlinky.GetFlags() & SPRITE_MATRIX_X_OFF)
  {
   Sprites.RemoveSprite(&SprBlinky);
 //   Sprites.RemoveSprite(&SprMarioRight); 
   SprClyde.SetPositionFrameMotionOptions(-10/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_Y_KEEPIN);
  Sprites.AddSprite(&SprClyde);
  }
  }
  else if (Sprites.IsSprite(&SprClyde))
  {
 if ( SprClyde.GetFlags() & SPRITE_MATRIX_X_OFF)
  {
   Sprites.RemoveSprite(&SprClyde);
 //   Sprites.RemoveSprite(&SprMarioRight); 
   SprInky.SetPositionFrameMotionOptions(-10/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_Y_KEEPIN);
  Sprites.AddSprite(&SprInky);
  }
  }
  else
  {
 if ( SprInky.GetFlags() & SPRITE_MATRIX_X_OFF)
  {
   Sprites.RemoveSprite(&SprInky);
 //   Sprites.RemoveSprite(&SprMarioRight); 
   SprMarioRight.SetPositionFrameMotionOptions(-10/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_Y_KEEPIN);
  Sprites.AddSprite(&SprMarioRight);
  
 }
  }
  
//  if (Sprites.IsSprite(&SprMarioRight))
//  {
//    if (SprPill.GetFlags() & )
//    {
//      Sprites.RemoveSprite(&SprPinky);
//      Sprites.RemoveSprite(&SprPacmanRight);
//      Sprites.RemoveSprite(&SprPill);
//      SprGhost.SetPositionFrameMotionOptions(SprPinky.m_X, SprPinky.m_Y, 0, 3, -1, 3, 0, 0, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
//      Sprites.AddSprite(&SprGhost);
 // Shape.SetPositionFrameMotionOptions(0/*X*/, 0/*Y*/, 0/*Frame*/, 0/*FrameRate*/, +1/*XChange*/, 1/*XRate*/, +1/*YChange*/, 2/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN | SPRITE_Y_KEEPIN
      //SprPacmanLeft.SetPositionFrameMotionOptions(SprPacmanRight.m_X, SprPacmanRight.m_Y, 0, 4, -1, 2, 0, 0, SPRITE_DETECT_EDGE | SPRITE_X_KEEPIN | SPRITE_Y_KEEPIN);
      //Sprites.AddSprite(&SprPacmanLeft);
//    }
//  }
//  else if (Sprites.IsSprite(&SprGhost))
//  {
//    if (SprGhost.GetFlags() & SPRITE_COLLISION)
//    {
//      Sprites.RemoveSprite(&SprGhost);
//      Spr200.SetPositionFrameMotionOptions(SprGhost.m_X, SprGhost.m_Y, 0, 0, 0, 0, 0, 0);
//      Sprites.AddSprite(&Spr200);
//      Sprites.ChangePriority(&Spr200, SPR_BACK);
//    }
//  }
//  else if (Sprites.IsSprite(&Spr200))
//  {
//    if (SprPacmanLeft.GetFlags() & SPRITE_EDGE_X_MIN)
//    {
//      Sprites.RemoveSprite(&Spr200);
//      SprEyes.SetPositionFrameMotionOptions(Spr200.m_X, Spr200.m_Y, 0, 0, +1, 2, 0, 0, SPRITE_DETECT_EDGE);
//      Sprites.AddSprite(&SprEyes);
//      Sprites.ChangePriority(&SprEyes, SPR_BACK);
//    }
//  }
//  else
//  {
//    if (SprEyes.GetFlags() & SPRITE_MATRIX_X_OFF)
//    {
//      Sprites.RemoveSprite(&SprEyes);
//      Sprites.RemoveSprite(&SprPacmanLeft);
//      SprPill.SetPositionFrameMotionOptions(MATRIX_WIDTH - POWER_PILL_SIZE - 1/*X*/, (MY_SPRITE_HEIGHT - POWER_PILL_SIZE) / 2/*Y*/, 0/*Frame*/, 0/*FrameRate*/, 0/*XChange*/, 0/*XRate*/, 0/*YChange*/, 0/*YRate*/);
//      Sprites.AddSprite(&SprPill);
//      SprPacmanRight.SetPositionFrameMotionOptions(-12/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
//      Sprites.AddSprite(&SprPacmanRight);
//      SprPinky.SetPositionFrameMotionOptions(-26/*X*/, 0/*Y*/, 0/*Frame*/, 2/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE);
//      Sprites.AddSprite(&SprPinky);
//    }
//  }
  Sprites.RenderSprites();
  FastLED.show();
  delay(15);
  count++;
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
      h+=20;
    }
  }
  else
  {
    // ** Fill LED's with horizontal stripes
    for (y=0; y<leds.Height(); ++y)
    {
      leds.DrawLine(0, y, leds.Width() - 1, y, CHSV(h, 255, 192));
      h+=20;
    }
  }
  hue+=4;

  if (counter < 0)
    ;
  else if (counter < 500)
    leds.HorizontalMirror();
  else if (counter < 1000)
    leds.VerticalMirror();
  else if (counter < 1500)
   leds.QuadrantMirror();
 // else if (counter < 1250)
   // leds.QuadrantRotateMirror();
  //else if (counter < 1250)
    //;
//  else if (counter < 1500)
//    leds.TriangleTopMirror();
  //else if (counter < 1750)
 //   leds.TriangleBottomMirror();
 // else if (counter < 2000)
 //   leds.QuadrantTopTriangleMirror();
  else if (counter < 2000)
    leds.QuadrantBottomTriangleMirror();

  counter++;
  if (counter >= 2000)
    counter = 0;
  FastLED.show();
  FastLED.delay(10);
}

void Dcon()
{


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

