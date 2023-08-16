#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#include "patterns.h"
#include "stripUtils.h"
#include "stripClock.h"
#include "net.h"
#include "effects.h"


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
static uint8_t effectState = 0;
static uint8_t stateAmount = 0;
bool stopEffect = 0;

uint8_t currentMatrix[nLEDS] = {0};

void clockUpdate(Adafruit_NeoPixel* strip, bool* stopEffect);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

StripClock* sClock;

// Add new effects to this array
EffectFunc effects[] = {
  &clockUpdate,
  &drawName,
  &drawNameRB,
  &colorStrips,
  &drawRainbow,
  &drawCarBlue,
  &drawCarGreen,
};

IRAM_ATTR void changeState()
{
  if(!stopEffect)
  {
  effectState = ++effectState % stateAmount;//(uint8_t)STATES;
  stopEffect = true;
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

  stateAmount = sizeof(effects)/sizeof(effects[0]);

  attachInterrupt(digitalPinToInterrupt(STATEBUTTON), changeState, FALLING);

  strip.setPixelColor(0, strip.Color(0xff, 0,0));
  const uint8_t* addr = strip.getPixels();

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

  if(effectState == 0)
  {
    sClock->update();
    delay(200);
  }

  if(effects[effectState] != nullptr)
  {
  effects[effectState](&strip, &stopEffect);
  }
  // switch (effectState)
  // {
  //   case 0:
  //     sClock->update();
  //     delay(200);

  //     // drawMemOffset(&strip, pattern::num2, 4, true);
  //     // drawMemOffset(&strip, pattern::num0,10, false);
  //     // drawMemOffset(&strip, pattern::dots,14, false);
  //     // drawMemOffset(&strip, pattern::num4,18, false);
  //     // drawMemOffset(&strip, pattern::num7,24, false);
  //     break;
  //   case 1:
  //     // drawName();
  //     drawMem(&strip, pattern::name, true);
  //     strip.show();
  //     break;
  //   case 2:
  //     drawMemRB(&strip, pattern::name, true, &stopEffect);
  //     strip.show();
  //     break;
  //   case 3:
  //     colorStrips(&strip, &stopEffect);     
  //     break;
  //   case 4:
  //     drawRainbow(&strip, &stopEffect);
  //     break;

  //   // RANDOM MOVING LINES
  //   case 5:
  //     // theaterChase(strip.Color(0,0,255), 200);
  //     break;
  //   // TIME MODE

  //   case 7:
  //     // drawMem(&strip, pattern::dots, true);
  //     drawMem(&strip, currentMatrix, true);
  //     break;
  //   case 8:
  //     moveMatrixPixel(&strip, currentMatrix, nLEDS, 100, 1);
  //     break;
  //   case 9:
  //     drawCarBlue(&strip, &stopEffect);
  //     break;
  //   case 10:
  //     drawCarGreen(&strip, &stopEffect);
  //     break;

  //   default:
  //     // colorWipe(strip.Color(255,255,0), 50);
  //     break;
  // }     
  stopEffect = false;
}

void clockUpdate(Adafruit_NeoPixel* strip, bool* stopEffect)
{
  if(sClock)
  {
    sClock->update();
  }
  delay(200);
}
