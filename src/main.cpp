#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#include "patterns.h"
#include "stripUtils.h"
#include "stripClock.h"
#include "net.h"


#define STATES       (uint8_t) 11
#define nLEDS        (uint16_t) 256

#if (ESP32)

#define PIN           26
#define STATEBUTTON   27
#define WIFIBUTTON    14
#define PIN3V3        25

#elif (ESP8266)
#define PIN           D2
#define STATEBUTTON   D1
// #define WIFIBUTTON    D1
// #define PIN3V3        D2

#endif

Adafruit_NeoPixel strip = Adafruit_NeoPixel(nLEDS, PIN, NEO_GRB + NEO_KHZ800);
static uint8_t state = 0;
bool stopEffect = 0;


uint8_t currentMatrix[nLEDS] = {0};
uint8_t colOffset = 0;

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void rainbow(uint8_t wait);
void rainbowCycle(uint8_t wait);
void colorWipe(uint32_t c, uint8_t wait);
void theaterChase(uint32_t c, uint8_t wait);

StripClock* sClock;

IRAM_ATTR void changeState()
{
  if(!stopEffect)
  {
  state = ++state % STATES;
  stopEffect = true;
  Serial.println(state);
  }
}

void setup() { 
  Serial.begin(115200);
  delay(1000);
  Serial.println("hello world");

  // pinMode(PIN3V3, OUTPUT);
  pinMode(STATEBUTTON, INPUT); // INPUT_PULLUP
  // pinMode(WIFIBUTTON, INPUT);

  // digitalWrite(PIN3V3, HIGH);

  strip.begin();
  strip.setBrightness(10);
  strip.show(); // Initialize all pixels to 'off'

  attachInterrupt(digitalPinToInterrupt(STATEBUTTON), changeState, FALLING);

  strip.setPixelColor(0, strip.Color(0xff, 0,0));
  const uint8_t* addr = strip.getPixels();
  while(true)
  {
    Serial.print(">"); Serial.print(addr[0], HEX); Serial.print(addr[1], HEX); Serial.print(addr[2], HEX);
    delay(500);
    strip.show();
  }


  sClock = new StripClock(&strip);
  sClock->sync();

  // move matrix
  currentMatrix[0] = 0x77;

  setupSoftAP();
  // monitor();
}

void loop() {
  // Some example procedures showing how to display to the pixels
  // Clock c = Clock();
  switch (state)
  {
    case 0:
      sClock->update();
      delay(200);

      // drawMemOffset(&strip, pattern::num2, 4, true);
      // drawMemOffset(&strip, pattern::num0,10, false);
      // drawMemOffset(&strip, pattern::dots,14, false);
      // drawMemOffset(&strip, pattern::num4,18, false);
      // drawMemOffset(&strip, pattern::num7,24, false);
      break;
    case 1:
      // drawName();
      drawMem(&strip, pattern::name, true);
      strip.show();
      break;
    case 2:
      drawMemRB(&strip, pattern::name, true, &stopEffect);
      strip.show();
      break;
    case 3:
      // TODO combine
      colorWipe(strip.Color(255, 0, 0), 25); // Red
      colorWipe(strip.Color(0, 255, 0), 25); // Green
      colorWipe(strip.Color(0, 0, 255), 25); // Blue
      break;
    case 4:
      rainbowCycle(50);
      break;

    // RANDOM MOVING LINES
    case 5:
      // theaterChase(strip.Color(0,0,255), 200);
      break;
    // TIME MODE

    case 7:
      // drawMem(&strip, pattern::dots, true);
      drawMem(&strip, currentMatrix, true);
      break;
    case 8:
      moveMatrixPixel(&strip, currentMatrix, nLEDS, 100, 1);
      break;
    case 9:
      drawMemOffset(&strip, pattern::car, colOffset, true);
      drawMemOffset(&strip, pattern::carWheel, colOffset, false, strip.Color(128,15,25));
      drawMemOffset(&strip, pattern::carInternal, colOffset, false, strip.Color(55, 40, 175));
      strip.show();

      colOffset += 2;

      if(colOffset >= 32)
      {
        colOffset = 0;
      }
      delay(280);
      break;
    case 10:
      drawMemOffset(&strip, pattern::car, colOffset, true, strip.Color(65, 255, 45));
      drawMemOffset(&strip, pattern::carWheel, colOffset, false, strip.Color(180,140,25));
      drawMemOffset(&strip, pattern::carInternal, colOffset, false, strip.Color(110, 205, 105));
      strip.show();

      colOffset += 2;

      if(colOffset >= 32)
      {
        colOffset = 0;
      }
      delay(280);
      break;

    default:
      colorWipe(strip.Color(255,255,0), 50);
      break;
  }     
  stopEffect = false;
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    if(stopEffect)
      break;
    strip.setPixelColor(i, c);
    strip.show();

    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      if(stopEffect) return;
      strip.setPixelColor(i, Wheel(&strip, (i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      if(stopEffect) return;
      strip.setPixelColor(i, Wheel(&strip, ((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel(&strip, (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

