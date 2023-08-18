#ifndef EFFECTS_H
#define EFFECTS_H

#include <Adafruit_NeoPixel.h>

#include "stripUtils.h"

typedef void (*EffectFunc)(Adafruit_NeoPixel*, bool*);

static uint8_t colOffset = 0;

/* effect helpers*/
void colorWipe(Adafruit_NeoPixel* strip, bool* stopEffect, uint32_t c, uint8_t wait);


/* effects */
void drawName(Adafruit_NeoPixel* strip, bool* stopEffect);
void drawNameRB(Adafruit_NeoPixel* strip, bool* stopEffect);
void colorStrips(Adafruit_NeoPixel* strip, bool* stopEffect);
void drawRainbow(Adafruit_NeoPixel* strip, bool* stopEffect);
void theaterChase(Adafruit_NeoPixel* strip, bool* stopEffect);

void drawCarBlue(Adafruit_NeoPixel* strip, bool* stopEffect);
void drawCarGreen(Adafruit_NeoPixel* strip, bool* stopEffect);


void noImage(Adafruit_NeoPixel* strip, bool* stopEffect);

/* Adafruit effects */
void AFrainbow(Adafruit_NeoPixel* strip, bool* stopEffect, uint8_t wait);
void AFrainbowCycle(Adafruit_NeoPixel* strip, bool* stopEffect, uint8_t wait);
void AFtheaterChase(Adafruit_NeoPixel* strip, bool* stopEffect, uint32_t c, uint8_t wait);
void AFtheaterChaseRainbow(Adafruit_NeoPixel* strip, bool* stopEffect, uint8_t wait);


#endif