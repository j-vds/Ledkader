#include "stripUtils.h"


void drawMem(Adafruit_NeoPixel* strip, const uint8_t* drawing, bool clear)
{ 
  drawMem(strip, drawing, clear, 0xabab);
}

void drawMem(Adafruit_NeoPixel* strip, const uint8_t* drawing, bool clear, uint32_t color)
{ 
  if(clear)
    strip->clear();

  const uint8_t amount = pgm_read_byte(drawing);
  for(int i = 1; i<amount; i++)
  {
    strip->setPixelColor(pgm_read_byte(drawing + i), color);
  }
  // strip->show();
}

void drawMemRB(Adafruit_NeoPixel* strip, const uint8_t* drawing, bool clear, bool* stopEffect)
{ 
  if(clear)
    strip->clear();
  
  uint16_t i,j;

  const uint8_t amount = pgm_read_byte(drawing);
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=1; i < amount; i++) {
      if(*stopEffect) return; 
      strip->setPixelColor(pgm_read_byte(drawing + i), Wheel(strip, ((i * 256 / strip->numPixels()) + j) & 255));
    }
    strip->show();
    delay(50);
    }
}

void drawMemOffset(Adafruit_NeoPixel* strip, const uint8_t* drawing, uint8_t offset, bool clear)
{
  drawMemOffset(strip, drawing, offset, clear, 0xabab);
}

void drawMemOffset(Adafruit_NeoPixel* strip, const uint8_t* drawing, uint8_t cols, bool clear, uint32_t color)
{
  if(clear)
  {
    strip->clear();
  }
  uint8_t offset = 8*cols;
  if(cols % 2)
  {
    // need to do some bitshifting

  }
  else
  {
    const uint8_t amount = pgm_read_byte(drawing);
    for(int i = 1; i<amount; i++)
    {
      strip->setPixelColor((uint8_t)(pgm_read_byte(drawing + i) + offset), color);
    }
  }
  // strip->show();
}

void drawMemOffset(Adafruit_NeoPixel* strip, const uint8_t* drawing, uint8_t cols, bool clear, const uint8_t* colorMatrix)
{
  if(clear)
  {
    strip->clear();
  }
  uint8_t offset = 8*cols;
  if(cols % 2)
  {
    // need to do some bitshifting

  }
  else
  {
    const uint8_t amount = pgm_read_byte(drawing);
    for(int i = 1; i<amount; i++)
    {
      strip->setPixelColor((uint8_t)(pgm_read_byte(drawing + i) + offset), colorMatrix[i-1]);
    }
  }
  // strip->show();
}

// provided by adafruit
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(Adafruit_NeoPixel* strip, byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


// takes 8178 microseconds
void moveMatrixPixel(Adafruit_NeoPixel* strip, uint8_t* currentMatrix, size_t nLeds, uint8_t wait, uint8_t moveAmount)
  {
    // save end of array
    // maybe not recommended!
    uint8_t* end = (uint8_t*)malloc(sizeof(uint8_t)*moveAmount);
    memcpy(end, currentMatrix+nLeds-moveAmount-1, moveAmount);

    for(int i = nLeds-1-moveAmount, j = nLeds - 1; -1 < j; i--, j--)
    {
      if(i < 0)
      {
        // i is negative
        strip->setPixelColor(j, end[moveAmount+i]);
        currentMatrix[j] = end[moveAmount+i];       
      } else {
        currentMatrix[j] = currentMatrix[i];
        strip->setPixelColor(j, currentMatrix[i]);
      }
    }
    strip->show();
    delay(wait);
    // memcpy(currentMatrix, strip.getPixels(), nLEDS);
    free(end);
  }

  void moveMatrixCol(Adafruit_NeoPixel* strip, uint8_t* currentMatrix, size_t nLeds, uint8_t wait, uint8_t moveAmount)
  {
    // strip.clear();

    for(int i = nLeds-1-moveAmount, j = nLeds - 1; -1 < j; i--, j--)
    {
      if(i < 0)
      {
        strip->setPixelColor(j, 0);
        currentMatrix[j] = 0;        
      } else {
        strip->setPixelColor(j, currentMatrix[i]);
        currentMatrix[j] = currentMatrix[i];
      }
    }
    strip->show();

    delay(wait);
    // memcpy(currentMatrix, strip.getPixels(), nLEDS);
  }
