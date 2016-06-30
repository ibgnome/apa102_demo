#include <FastLED.h>
// Libraries from https://github.com/AaronLiddiment
#include <LEDMatrix.h>
#include <LEDSprites.h>
#include <LEDText.h>
#include <Font12x16.h>
#include <FontMatrise.h>


// Set to run on the Teensy 3.2 SPI ports and run on APA102 leds
#define DATA_PIN    11
#define CLK_PIN   13
#define CHIPSET    APA102
#define COLOR_ORDER BGR

// This is set for the LED matrices on the top hat. 
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
uint8_t angle = 0;
int randcount;
int count, eye_count = 0;
uint8_t hue = 0;
uint8_t gHue = 0;
int16_t counter = 0;

uint16_t PlasmaTime, PlasmaShift;

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

const struct CRGB MarioColTab[] =  {  CRGB::Red, CRGB(152,102,17), CRGB::Gold  };
const struct CRGB LuigiColTab[] =  {  CRGB::White, CRGB::Green, CRGB::Gold  };

const uint8_t MushroomData[] =
{
  B8_2BIT(00001111),B8_2BIT(11110000),
  B8_2BIT(00011223),B8_2BIT(32211000),
  B8_2BIT(00112223),B8_2BIT(32221100),
  B8_2BIT(01132233),B8_2BIT(33223110),
  B8_2BIT(01233333),B8_2BIT(33333210),
  B8_2BIT(11223322),B8_2BIT(22332211),
  B8_2BIT(12223222),B8_2BIT(22232221),
  B8_2BIT(12223222),B8_2BIT(22232221),
  B8_2BIT(12233222),B8_2BIT(22233221),
  B8_2BIT(13333322),B8_2BIT(22333331),
  B8_2BIT(13311111),B8_2BIT(11111331),
  B8_2BIT(11112212),B8_2BIT(21221111),
  B8_2BIT(01122212),B8_2BIT(21222110),
  B8_2BIT(00122222),B8_2BIT(22222100),
  B8_2BIT(00112222),B8_2BIT(22221100),
  B8_2BIT(00011111),B8_2BIT(11111000)

  
};

const uint8_t MushroomMask[] = 
{
  B8_2BIT(00001111),B8_2BIT(11110000),
  B8_2BIT(00011111),B8_2BIT(1111000),
  B8_2BIT(00111111),B8_2BIT(11111100),
  B8_2BIT(01111111),B8_2BIT(11111110),
  B8_2BIT(01111111),B8_2BIT(11111110),
  B8_2BIT(11111111),B8_2BIT(11111111),
  B8_2BIT(11111111),B8_2BIT(11111111),
  B8_2BIT(11111111),B8_2BIT(11111111),
  B8_2BIT(11111111),B8_2BIT(11111111),
  B8_2BIT(11111111),B8_2BIT(11111111),
  B8_2BIT(11111111),B8_2BIT(11111111),
  B8_2BIT(11111111),B8_2BIT(11111111),
  B8_2BIT(01111111),B8_2BIT(11111110),
  B8_2BIT(00111111),B8_2BIT(11111100),
  B8_2BIT(00111111),B8_2BIT(11111100),
  B8_2BIT(00011111),B8_2BIT(11111000)
};

const struct CRGB MushroomColTab[] =  {  CRGB::Black, CRGB::White, CRGB::Red  };

const uint8_t GoombaData[] =
{
  B8_2BIT(00000011),B8_2BIT(11000000),
  B8_2BIT(00000111),B8_2BIT(11100000),
  B8_2BIT(00001111),B8_2BIT(11110000),
  B8_2BIT(00011111),B8_2BIT(11111000),
  B8_2BIT(00122111),B8_2BIT(11122100),
  B8_2BIT(01113211),B8_2BIT(11231110),
  B8_2BIT(01113222),B8_2BIT(22231110),
  B8_2BIT(11113231),B8_2BIT(13231111),
  B8_2BIT(11113331),B8_2BIT(13331111),
  B8_2BIT(11111111),B8_2BIT(11111111),
  B8_2BIT(01111333),B8_2BIT(33311110),
  B8_2BIT(00003333),B8_2BIT(33330000),
  B8_2BIT(00003333),B8_2BIT(33332200),
  B8_2BIT(00022333),B8_2BIT(32222220),
  B8_2BIT(00022233),B8_2BIT(22222220),
  B8_2BIT(00002220),B8_2BIT(02222200),

  B8_2BIT(00000011),B8_2BIT(11000000),
  B8_2BIT(00000111),B8_2BIT(11100000),
  B8_2BIT(00001111),B8_2BIT(11110000),
  B8_2BIT(00011111),B8_2BIT(11111000),
  B8_2BIT(00122111),B8_2BIT(11122100),
  B8_2BIT(01113211),B8_2BIT(11231110),
  B8_2BIT(01113222),B8_2BIT(22231110),
  B8_2BIT(11113231),B8_2BIT(13231111),
  B8_2BIT(11113331),B8_2BIT(13331111),
  B8_2BIT(11111111),B8_2BIT(11111111),
  B8_2BIT(01111333),B8_2BIT(33311110),
  B8_2BIT(00003333),B8_2BIT(33330000),
  B8_2BIT(00223333),B8_2BIT(33330000),
  B8_2BIT(02222223),B8_2BIT(33322000),
  B8_2BIT(02222222),B8_2BIT(33222000),
  B8_2BIT(00222220),B8_2BIT(02220000)

  
};

const uint8_t GoombaMask[] =
{
  B8_2BIT(00000011),B8_2BIT(11000000),
  B8_2BIT(00000111),B8_2BIT(11100000),
  B8_2BIT(00001111),B8_2BIT(11110000),
  B8_2BIT(00011111),B8_2BIT(11111000),
  B8_2BIT(00111111),B8_2BIT(11111100),
  B8_2BIT(01111111),B8_2BIT(11111110),
  B8_2BIT(01111111),B8_2BIT(11111110),
  B8_2BIT(11111111),B8_2BIT(11111111),
  B8_2BIT(11111111),B8_2BIT(11111111),
  B8_2BIT(11111111),B8_2BIT(11111111),
  B8_2BIT(01111111),B8_2BIT(11111110),
  B8_2BIT(00001111),B8_2BIT(11110000),
  B8_2BIT(00001111),B8_2BIT(11111100),
  B8_2BIT(00011111),B8_2BIT(11111110),
  B8_2BIT(00011111),B8_2BIT(11111110),
  B8_2BIT(00001110),B8_2BIT(01111100),

  B8_2BIT(00000011),B8_2BIT(11000000),
  B8_2BIT(00000111),B8_2BIT(11100000),
  B8_2BIT(00001111),B8_2BIT(11110000),
  B8_2BIT(00011111),B8_2BIT(11111000),
  B8_2BIT(00111111),B8_2BIT(11111100),
  B8_2BIT(01111111),B8_2BIT(11111110),
  B8_2BIT(01111111),B8_2BIT(11111110),
  B8_2BIT(11111111),B8_2BIT(11111111),
  B8_2BIT(11111111),B8_2BIT(11111111),
  B8_2BIT(11111111),B8_2BIT(11111111),
  B8_2BIT(01111111),B8_2BIT(11111110),
  B8_2BIT(00001111),B8_2BIT(11110000),
  B8_2BIT(00111111),B8_2BIT(11110000),
  B8_2BIT(01111111),B8_2BIT(11111000),
  B8_2BIT(01111111),B8_2BIT(11111000),
  B8_2BIT(00111110),B8_2BIT(01110000)

  
};

const struct CRGB GoombaColTab[] =  {  CRGB(152,102,17), CRGB::Black, CRGB::White  };

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

const uint8_t Eyes1Data[] = 
{
  B8_2BIT(01110001),B8_2BIT(11000000),
  B8_2BIT(11111011),B8_2BIT(11100000),
  B8_2BIT(11122011),B8_2BIT(12200000),
  B8_2BIT(11122011),B8_2BIT(12200000),
  B8_2BIT(01110001),B8_2BIT(11000000)
};
const uint8_t Eyes2Data[] =
{
  B8_2BIT(01110001),B8_2BIT(11000000),
  B8_2BIT(11122011),B8_2BIT(12200000),
  B8_2BIT(11122011),B8_2BIT(12200000),
  B8_2BIT(11111011),B8_2BIT(11100000),
  B8_2BIT(01110001),B8_2BIT(11000000)
};
const uint8_t Eyes3Data[] =  
{
  B8_2BIT(01110001),B8_2BIT(11000000),
  B8_2BIT(11111011),B8_2BIT(11100000),
  B8_2BIT(22111022),B8_2BIT(11100000),
  B8_2BIT(22111022),B8_2BIT(11100000),
  B8_2BIT(01110001),B8_2BIT(11000000)
};
const uint8_t Eyes4Data[] =  
{
  B8_2BIT(01110001),B8_2BIT(11000000),
  B8_2BIT(22111022),B8_2BIT(11100000),
  B8_2BIT(22111022),B8_2BIT(11100000),
  B8_2BIT(11111011),B8_2BIT(11100000),
  B8_2BIT(01110001),B8_2BIT(11000000)
};
const uint8_t Eyes5Data[] =
{
  B8_2BIT(01110001),B8_2BIT(11000000),
  B8_2BIT(11221012),B8_2BIT(21100000),
  B8_2BIT(11221012),B8_2BIT(21100000),
  B8_2BIT(11111011),B8_2BIT(11100000),
  B8_2BIT(01110001),B8_2BIT(11000000)
};
const uint8_t EyesMask[] = 
{

  B8_1BIT(01110001),B8_1BIT(11000000),
  B8_1BIT(11111011),B8_1BIT(11100000),
  B8_1BIT(11111011),B8_1BIT(11100000),
  B8_1BIT(11111011),B8_1BIT(11100000),
  B8_1BIT(01110001),B8_1BIT(11000000)
  
};
const struct CRGB EyesColTab[] =  {  CRGB(255, 255, 255), CRGB(0, 0, 255), CRGB(0, 0, 0)  };


cSprite SprPacmanRight(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PacmanRightData, PACMAN_FRAMES, _2BIT, PacmanRightColTab, PacmanRightMask);
cSprite SprMarioRight(MARIO_SIZE, MARIO_SIZE, MarioData, MARIO_FRAMES, _2BIT, MarioColTab, MarioMask);
cSprite SprMarioRight2(MARIO_SIZE, MARIO_SIZE, MarioData, MARIO_FRAMES, _2BIT, LuigiColTab, MarioMask);
cSprite SprMarioRight3(MARIO_SIZE, MARIO_SIZE, MarioData, MARIO_FRAMES, _2BIT, MarioColTab, MarioMask);
cSprite SprMarioRight4(MARIO_SIZE, MARIO_SIZE, MarioData, MARIO_FRAMES, _2BIT, MarioColTab, MarioMask);
cSprite SprPinky(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PinkyData, PINKY_FRAMES, _2BIT, PinkyColTab, PinkyMask);
cSprite SprBlinky(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PinkyData, PINKY_FRAMES, _2BIT, BlinkyColTab, PinkyMask);
cSprite SprInky(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PinkyData, PINKY_FRAMES, _2BIT, InkyColTab, PinkyMask);
cSprite SprClyde(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PinkyData, PINKY_FRAMES, _2BIT, ClydeColTab, PinkyMask);
cSprite SprPacmanLeft(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PacmanLeftData, PACMAN_FRAMES, _2BIT, PacmanLeftColTab, PacmanLeftMask);
cSprite SprGhost(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, GhostData, PINKY_FRAMES, _2BIT, GhostColTab, GhostMask);
cSprite SprPill(POWER_PILL_SIZE, POWER_PILL_SIZE, PowerPillData, 1, _1BIT, PowerPillColTab, PowerPillData);
cSprite Spr200(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, S200Data, 1, _1BIT, S200ColTab, S200Data);
cSprite SprEyesRightDown(11, 5, Eyes1Data, 1, _2BIT, EyesColTab, EyesMask);
cSprite SprEyesRightUp(11, 5, Eyes2Data, 1, _2BIT, EyesColTab, EyesMask);
cSprite SprEyesLeftDown(11, 5, Eyes3Data, 1, _2BIT, EyesColTab, EyesMask);
cSprite SprEyesLeftUp(11, 5, Eyes4Data, 1, _2BIT, EyesColTab, EyesMask);
cSprite SprEyesCenter(11, 5, Eyes5Data, 1, _2BIT, EyesColTab, EyesMask);
cSprite SprMushroom(MARIO_SIZE, MARIO_SIZE, MushroomData, 1, _2BIT, MushroomColTab, MushroomMask);
cSprite SprGoomba(MARIO_SIZE, MARIO_SIZE, GoombaData, 2, _2BIT, GoombaColTab, GoombaMask);
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
  

    PlasmaShift = (random8(0, 5) * 32) + 64;
  PlasmaTime = 0;
}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();

//SimplePatternList gPatterns = { Dcon, MultiMario, TrippyRainbow, Plasma, Wave };
SimplePatternList gPatterns = { Eyes };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current

void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  

EVERY_N_MILLISECONDS( 5 ) { gHue=gHue+16; }
  // do some periodic updates
  EVERY_N_SECONDS( 60 ) { nextPattern(); } // change patterns periodically
}

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
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

void MultiMario()
{
    FastLED.clear();
    Sprites.RemoveSprite(&SprEyesRightDown);
    Sprites.RemoveSprite(&SprEyesRightUp);
    Sprites.RemoveSprite(&SprEyesLeftDown);
    Sprites.RemoveSprite(&SprEyesLeftUp);
    Sprites.RemoveSprite(&SprEyesCenter);
    
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

   if (SprMushroom.GetFlags() & SPRITE_MATRIX_X_OFF)
   { 
      SprMushroom.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
      Sprites.AddSprite(&SprMushroom);
   }
   if (SprMushroom.m_X == 4)
   {
    SprMarioRight.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprMarioRight);
   }

   if (SprMarioRight.m_X == 4)
   {
    SprMarioRight2.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprMarioRight2);
   }

   
   if (SprMarioRight2.m_X == 4)
   {
    SprGoomba.SetPositionFrameMotionOptions(-15/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprGoomba);
   }

  Sprites.RenderSprites();
  FastLED.show();
  delay(10);
  count++;
  
}

void Plasma()
{

    // Fill background with dim plasma
    #define PLASMA_X_FACTOR  16
    #define PLASMA_Y_FACTOR  16
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
      
    FastLED.show();
    FastLED.delay(10);
}

void Eyes()
{
  FastLED.clear();

  Sprites.RemoveSprite(&SprMushroom);
  Sprites.RemoveSprite(&SprMarioRight);
  Sprites.RemoveSprite(&SprMarioRight2);
  Sprites.RemoveSprite(&SprGoomba);
  
  Sprites.UpdateSprites();
  Sprites.DetectCollisions();
if (eye_count == 0)
{
  SprEyesLeftUp.SetPositionFrameMotionOptions(26/*X*/, 5/*Y*/, 1/*Frame*/, 0/*FrameRate*/, 0/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
  
  Sprites.AddSprite(&SprEyesLeftUp);
}


int randcount = random8(1,7);
if (randcount == 1)
{
  Sprites.RemoveSprite(&SprEyesRightDown);
  Sprites.RemoveSprite(&SprEyesRightUp);
  Sprites.RemoveSprite(&SprEyesLeftDown);
  Sprites.RemoveSprite(&SprEyesLeftUp);
  Sprites.RemoveSprite(&SprEyesCenter);
  SprEyesRightDown.SetPositionFrameMotionOptions(26/*X*/, 5/*Y*/, 0/*Frame*/, 0/*FrameRate*/, 0/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
  
  Sprites.AddSprite(&SprEyesRightDown);
}
else if (randcount == 2)
{
  Sprites.RemoveSprite(&SprEyesRightDown);
  Sprites.RemoveSprite(&SprEyesRightUp);
  Sprites.RemoveSprite(&SprEyesLeftDown);
  Sprites.RemoveSprite(&SprEyesLeftUp);
  Sprites.RemoveSprite(&SprEyesCenter);
  SprEyesRightUp.SetPositionFrameMotionOptions(26/*X*/, 5/*Y*/, 0/*Frame*/, 0/*FrameRate*/, 0/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
  
  Sprites.AddSprite(&SprEyesRightUp);
}
else if (randcount == 3)
{
  Sprites.RemoveSprite(&SprEyesRightDown);
  Sprites.RemoveSprite(&SprEyesRightUp);
  Sprites.RemoveSprite(&SprEyesLeftDown);
  Sprites.RemoveSprite(&SprEyesLeftUp);
  Sprites.RemoveSprite(&SprEyesCenter);
  SprEyesLeftDown.SetPositionFrameMotionOptions(26/*X*/, 5/*Y*/, 0/*Frame*/, 0/*FrameRate*/, 0/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
  
  Sprites.AddSprite(&SprEyesLeftDown);
}
else if (randcount == 5)
{
  Sprites.RemoveSprite(&SprEyesRightDown);
  Sprites.RemoveSprite(&SprEyesRightUp);
  Sprites.RemoveSprite(&SprEyesLeftDown);
  Sprites.RemoveSprite(&SprEyesLeftUp);
  Sprites.RemoveSprite(&SprEyesCenter);
  SprEyesLeftUp.SetPositionFrameMotionOptions(26/*X*/, 5/*Y*/, 0/*Frame*/, 0/*FrameRate*/, 0/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
  
  Sprites.AddSprite(&SprEyesLeftUp);
}
else  
{
  Sprites.RemoveSprite(&SprEyesRightDown);
  Sprites.RemoveSprite(&SprEyesRightUp);
  Sprites.RemoveSprite(&SprEyesLeftDown);
  Sprites.RemoveSprite(&SprEyesLeftUp);
  Sprites.RemoveSprite(&SprEyesCenter);
  SprEyesCenter.SetPositionFrameMotionOptions(26/*X*/, 5/*Y*/, 0/*Frame*/, 0/*FrameRate*/, 0/*XChange*/, 2/*XRate*/, 0/*YChange*/, 0/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
  
  Sprites.AddSprite(&SprEyesCenter);
}

    Sprites.RenderSprites();
  FastLED.show();
  delay(random16(1500));
  eye_count++;
}

void Wave()
{
  uint8_t h = sin8(angle);
  leds.ShiftLeft();
  for (int16_t y=leds.Height()-1; y>=0; --y)
  {
    if (h > 160 && h < 240)
	{
    leds(leds.Width()-1, y) = CHSV(h, 255, 255);
    	}
    h += 32;
  }
  angle += 4;
  FastLED.show();
  delay(20);
}

void starfield()
{
FastLED.clear();

}

void confetti()
{
}

