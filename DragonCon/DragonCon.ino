// This example shows the use of INSTANT_OPTIONS_MODE
// When set it stops the text routine from having to scroll all
// of the existing text off the display before changing the scroll
// direction.

#include <FastLED.h>

#include <LEDMatrix.h>
#include <LEDText.h>
#include <Font12x16.h>
#include <FontMatrise.h>

// Change the next 6 defines to match your matrix type and size

#define DATA_PIN    11
#define CLK_PIN   13
#define COLOR_ORDER    BGR
#define CHIPSET        APA102

#define MATRIX_WIDTH   -64
#define MATRIX_HEIGHT  16
#define MATRIX_TYPE    VERTICAL_ZIGZAG_MATRIX

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

cLEDText ScrollingMsg;

const unsigned char TxtDemo[] = { EFFECT_FRAME_RATE "\x02"
                                  EFFECT_HSV_AH "\x00\xff\xff\xff\xff\xff"
                                  EFFECT_SCROLL_RIGHT EFFECT_CHAR_DOWN "          DRAGONCON 2016"
                                  //EFFECT_SCROLL_UP "Quick "
                                  //EFFECT_SCROLL_LEFT "Brown "
                                  //EFFECT_SCROLL_DOWN "Fox"
                                  //EFFECT_SCROLL_LEFT "Jumps "
                                  //EFFECT_SCROLL_UP "Over  "
                                  //EFFECT_SCROLL_LEFT "The "
                                  //EFFECT_SCROLL_DOWN "Lazy  "
                                  //EFFECT_SCROLL_LEFT "Dog " 
                                  };
uint16_t Options;

void setup()
{
  FastLED.addLeds<CHIPSET, DATA_PIN, CLK_PIN, COLOR_ORDER, DATA_RATE_MHZ(5)>(leds[0], leds.Size());
  
  FastLED.setBrightness(20);
  FastLED.clear(true);
  delay(1000);
  FastLED.show();

  ScrollingMsg.SetFont(Font12x16Data);
  ScrollingMsg.Init(&leds, leds.Width(), ScrollingMsg.FontHeight() + 1, 0, 0);
  ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
  ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0xff, 0x00, 0xff);
  Options = INSTANT_OPTIONS_MODE;
  ScrollingMsg.SetOptionsChangeMode(Options);
}


void loop()
{
  if (ScrollingMsg.UpdateText() == -1)
  {
    ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
    Options ^= INSTANT_OPTIONS_MODE;
    ScrollingMsg.SetOptionsChangeMode(0);
    //FastLED.delay(300);
  }
  else
    //leds.HorizontalMirror();
    FastLED.show();
  delay(10);
}

