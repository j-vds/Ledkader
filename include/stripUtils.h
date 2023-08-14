#ifndef STRIPUTILS_H
#define STRIPUTILS_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

void drawMem(Adafruit_NeoPixel* strip, const uint8_t* drawing, bool clear);
void drawMem(Adafruit_NeoPixel* strip, const uint8_t* drawing, bool clear, uint32_t color);

void drawMemOffset(Adafruit_NeoPixel* strip, const uint8_t* drawing, uint8_t cols, bool clear);
void drawMemOffset(Adafruit_NeoPixel* strip, const uint8_t* drawing, uint8_t cols, bool clear, uint32_t color);
void drawMemOffset(Adafruit_NeoPixel* strip, const uint8_t* drawing, uint8_t cols, bool clear, const uint8_t* colorMatrix);


void drawMemRB(Adafruit_NeoPixel* strip, const uint8_t* drawing, bool clear, bool* stopEffect);

uint32_t Wheel(Adafruit_NeoPixel* strip, byte WheelPos);

void moveMatrixPixel(Adafruit_NeoPixel* strip, uint8_t* currentMatrix, size_t nLeds, uint8_t wait, uint8_t moveAmount);
void moveMatrixCol(Adafruit_NeoPixel* strip, uint8_t* currentMatrix, size_t nLeds, uint8_t wait, uint8_t moveAmount);


#endif