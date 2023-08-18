#include "effects.h"

#include "patterns.h"

/**
 ********************  effect helpers ********************
*/

void colorWipe(Adafruit_NeoPixel* strip, bool* stopEffect, uint32_t c, uint8_t wait) 
{
  for(uint16_t i=0; i<strip->numPixels(); i++) 
  {
    if(*stopEffect)
      return;
    strip->setPixelColor(i, c);
    strip->show();

    delay(wait);
  }
}

/**
 ******************  End effect helpers ******************
*/

void drawName(Adafruit_NeoPixel* strip, bool* stopEffect)
{
    drawMem(strip, pattern::name, true);
    strip->show();
}

void drawNameRB(Adafruit_NeoPixel* strip, bool* stopEffect)
{
    drawMemRB(strip, pattern::name, true, stopEffect);
    strip->show();
}

void colorStrips(Adafruit_NeoPixel* strip, bool* stopEffect)
{
    colorWipe(strip, stopEffect, strip->Color(127, 0, 0), 25); // Red
    colorWipe(strip, stopEffect, strip->Color(0, 127, 0), 25); // Green
    colorWipe(strip, stopEffect, strip->Color(0, 0, 127), 25); // Blue
    colorWipe(strip, stopEffect, strip->Color(127,127,0), 25); // Yellow
}

void drawRainbow(Adafruit_NeoPixel* strip, bool* stopEffect)
{
    AFrainbowCycle(strip, stopEffect, 50);
}

void drawCarBlue(Adafruit_NeoPixel* strip, bool* stopEffect)
{
    drawMemOffset(strip, pattern::car, colOffset, true);
    drawMemOffset(strip, pattern::carWheel, colOffset, false, strip->Color(128,15,25));
    drawMemOffset(strip, pattern::carInternal, colOffset, false, strip->Color(55, 40, 175));
    strip->show();

    colOffset += 2;

    if(colOffset >= 32)
    {
      colOffset = 0;
    }
    delay(250);
}

void drawCarGreen(Adafruit_NeoPixel* strip, bool* stopEffect)
{
  drawMemOffset(strip, pattern::car, colOffset, true, strip->Color(65, 255, 45));
  drawMemOffset(strip, pattern::carWheel, colOffset, false, strip->Color(180,140,25));
  drawMemOffset(strip, pattern::carInternal, colOffset, false, strip->Color(110, 205, 105));
  strip->show();

  colOffset += 2;

  if(colOffset >= 32)
  {
  colOffset = 0;
  }
  delay(250);
}

void theaterChase(Adafruit_NeoPixel* strip, bool* stopEffect)
{
  AFtheaterChase(strip, stopEffect, strip->Color(127, 127, 127),100);
  AFtheaterChase(strip, stopEffect, strip->Color( 30,  40,  50),100);
  AFtheaterChase(strip, stopEffect, strip->Color(  0, 123, 123),100);
}


/**
 * Always LAST EFFECT
*/
void noImage(Adafruit_NeoPixel* strip, bool* stopEffect)
{
  strip->clear();
  strip->show();
  delay(50);
}

/**
 ******************  Adafruit effects ******************
*/
void AFrainbow(Adafruit_NeoPixel* strip, bool* stopEffect, uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip->numPixels(); i++) {
      if(*stopEffect) return;
      strip->setPixelColor(i, Wheel(strip, (i+j) & 255));
    }
    strip->show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void AFrainbowCycle(Adafruit_NeoPixel* strip, bool* stopEffect, uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip->numPixels(); i++) {
      if(*stopEffect) return;
      strip->setPixelColor(i, Wheel(strip, ((i * 256 / strip->numPixels()) + j) & 255));
    }
    strip->show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void AFtheaterChase(Adafruit_NeoPixel* strip, bool* stopEffect, uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip->numPixels(); i=i+3) {
        if(*stopEffect) return;
        strip->setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip->show();

      delay(wait);

      for (uint16_t i=0; i < strip->numPixels(); i=i+3) {
        strip->setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void AFtheaterChaseRainbow(Adafruit_NeoPixel* strip, bool* stopEffect, uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip->numPixels(); i=i+3) {
        strip->setPixelColor(i+q, Wheel(strip, (i+j) % 255));    //turn every third pixel on
      }
      strip->show();

      delay(wait);

      for (uint16_t i=0; i < strip->numPixels(); i=i+3) {
        strip->setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
