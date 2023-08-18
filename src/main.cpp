#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#include "patterns.h"
#include "stripUtils.h"
#include "stripClock.h"
#include "net.h"
#include "effects.h"
#include "constants.h"


#define nLEDS        (uint16_t) 256

#if (ESP32)

#define DATAPIN           26
#define STATEBUTTON   27
#define WIFIBUTTON    14
#define PIN3V3        25

#elif (ESP8266)
#define DATAPIN       D2
#define STATEBUTTON   D1  // D1
#define WIFIBUTTON    D6

#define LOWLINE       D7
#define HIGHLINE      D3

// #define PIN3V3        D2

#endif

Adafruit_NeoPixel strip = Adafruit_NeoPixel(nLEDS, DATAPIN, NEO_GRB + NEO_KHZ800);
static uint8_t effectState = 0;
static uint8_t stateAmount = 0;
bool stopEffect = false;

bool netConnected = false;

uint8_t currentMatrix[nLEDS] = {0};

// constant
unsigned long switchPeriod = 500UL;

unsigned long lastSwitchTime = 0UL;
unsigned long lastModeTime   = 0UL;

// WIFI_AP STATE
displayMode_t displayMode = DISP_NORMAL; // NORMAL

void clockUpdate(Adafruit_NeoPixel* strip, bool* stopEffect);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

StripClock* sClock;

// Add new effects to this array
// NORMAL EFFECTS
EffectFunc effects[] = {
  &clockUpdate,
  &drawName,
  &drawNameRB,
  &colorStrips,
  &drawRainbow,
  &drawCarBlue,
  &drawCarGreen,
  &theaterChase,
  &noImage,
};

IRAM_ATTR void changeState()
{
  if(displayMode == displayMode_t::DISP_NORMAL && (millis() - lastSwitchTime > switchPeriod))
  {
  Serial.println("triggered");
  effectState = ++effectState % stateAmount;//(uint8_t)STATES;
  stopEffect = true;
  lastSwitchTime = millis();
  }
}

// changes the displayMODE
// MODE 0: display off / NORMAL mode
// MODE 1: WEBSERVER MODE 

IRAM_ATTR void changeAP()
{
  // turn on/off the WiFiAccessPoint
  if(millis() - lastModeTime < switchPeriod)
  {
    // debouncing TOO SOON
    return;
  }

  Serial.println("triggered ap");
  
  // so only double press will activate it!
  if(displayMode == displayMode_t::DISP_NORMAL && effectState == stateAmount - 1)
  {
    displayMode = displayMode_t::DISP_SERVER;
  } 
  else 
  {
    displayMode = displayMode_t::DISP_NORMAL;
    effectState = stateAmount - 1;
  }

  stopEffect = true;
}


void setup() { 
  Serial.begin(115200);
  delay(1000);
  Serial.println("hello world");

  // pinMode(PIN3V3, OUTPUT);
  pinMode(STATEBUTTON, INPUT);   // INPUT_PULLUP
  pinMode(WIFIBUTTON, INPUT); // INPUT_PULLUP
  pinMode(LOWLINE, OUTPUT);
  pinMode(HIGHLINE, OUTPUT);

  digitalWrite(HIGHLINE, HIGH);
  digitalWrite(LOWLINE, LOW);

  // digitalWrite(PIN3V3, HIGH);

  strip.begin();
  strip.setBrightness(10);
  strip.show(); // Initialize all pixels to 'off'

  stateAmount = sizeof(effects)/sizeof(effects[0]);

  // setup buttons
  attachInterrupt(digitalPinToInterrupt(STATEBUTTON), changeState, FALLING);
  attachInterrupt(digitalPinToInterrupt(WIFIBUTTON) , changeAP, FALLING);


  // hard print setup!
  strip.setPixelColor(0, strip.Color(0xff, 0,0));
  const uint8_t* addr = strip.getPixels();

  sClock = new StripClock(&strip);
  sClock->sync();

  // move matrix
  currentMatrix[0] = 0x77;

  // setupSoftAP();
  // monitor();
}

void loop() {
  // Some example procedures showing how to display to the pixels
  // Clock c = Clock();
  if(displayMode == displayMode_t::DISP_NORMAL)
  {
    if(netConnected)
    {
      netDisconnect();
    }

    if(effects[effectState] != nullptr)
    {
    effects[effectState](&strip, &stopEffect);
    }
    delay(50);
    stopEffect = false;
  } 
  else
  {
    // WEBSERVER MODE - NO DELAYS!
    // make sure there is a connection
    if(!netConnected)
    {
      // connect to net
      if(netConnect(&strip) < 0)
      {
        // failed to connect to the web :(
        displayMode = displayMode_t::DISP_NORMAL;
        effectState = 0;
        stopEffect = true;
      } else {
        netConnected = true;
        strip.setPixelColor(255, strip.Color(0,0,127));
        strip.show();
      }
    }
    updateServers();
  }

}

void clockUpdate(Adafruit_NeoPixel* strip, bool* stopEffect)
{
  if(sClock)
  {
    sClock->update(stopEffect);
  }
  // delay(200);
}
