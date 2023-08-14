#ifndef PATTERNS_H
#define PATTERNS_H

#include <Arduino.h>

#if defined(ESP8266) || defined(ESP32)
#include <pgmspace.h>
#endif


namespace pattern
{
    const uint8_t name[] PROGMEM = 
        {78, 0xd,0xc,0xb,0xa,0x9,0x11,0x14,0x1e,0x1b,0x22,0x23,0x24,0x25,0x26,0x32,0x33,
        0x34,0x35,0x36,0x3c,0x44,0x4d,0x4c,0x4b,0x4a,0x49,0x5d,0x62,0x63,0x64,0x65,0x66,
        0x6d,0x7d,0x7c,0x7b,0x7a,0x79,0x84,0x8d,0x8c,0x8b,0x8a,0x89,0x9d,0x9c,0x9b,0x9a,
        0x99,0xa2,0xa6,0xad,0xac,0xab,0xaa,0xa9,0xbd,0xbc,0xbb,0xba,0xb9,0xc3,0xcb,0xd2,
        0xd3,0xd4,0xd5,0xd6,0xe2,0xe3,0xe4,0xeb,0xea,0xe9,0xf2,0xf3,0xf4, };

    const uint8_t car[] PROGMEM = 
        {30, 0x5,0xb,0xa,0x9,0x11,0x12,0x13,0x16,0x1e,0x19,0x20,0x21,0x2f,0x30,0x3f,0x39,
         0x40,0x41,0x46,0x4e,0x4d,0x52,0x53,0x5c,0x63,0x66,0x6b,0x6a,0x69 };

    const uint8_t carWheel[] PROGMEM =
        {9, 0x26,0x2a,0x28,0x36,0x49,0x55,0x57,0x59};

    
    const uint8_t carInternal[] PROGMEM = 
        {31, 0x14,0x15,0x1d,0x1c,0x1b,0x1a,0x22,0x24,0x25,0x2e,0x2b,0x31,0x32,0x33,0x34,
         0x35,0x3e,0x3b,0x3a,0x42,0x44,0x45,0x4c,0x4b,0x4a,0x54,0x5b,0x5a,0x64,0x65};


    const uint8_t wave[] PROGMEM =
        {88, 0x0,0x3,0x6,0xd,0xa,0x10,0x13,0x16,0x1e,0x1b,0x18,0x20,0x23,0x26,0x2d,0x2a,0x30,
        0x33,0x36,0x3e,0x3b,0x38,0x40,0x43,0x46,0x4d,0x4a,0x50,0x53,0x56,0x5e,0x5b,0x58,0x60,
        0x63,0x66,0x6d,0x6a,0x70,0x73,0x76,0x7e,0x7b,0x78,0x80,0x83,0x86,0x8d,0x8a,0x90,0x93,
        0x96,0x9e,0x9b,0x98,0xa0,0xa3,0xa6,0xad,0xaa,0xb0,0xb3,0xb6,0xbe,0xbb,0xb8,0xc0,0xc3,
        0xc6,0xcd,0xca,0xd0,0xd3,0xd6,0xde,0xdb,0xd8,0xe0,0xe3,0xe6,0xed,0xea,0xf0,0xf3,0xf6,
        0xfe,0xfb,0xf8};

    // ******** NUMBERS ********* //

    const uint8_t num0[] PROGMEM =
        {19, 0x1,0x2,0x3,0x4,0x5,0x6,0x7,0xe,0x8,0x11,0x17,0x1e,0x1d,0x1c,0x1b,0x1a,0x19,0x18};

    const uint8_t num1[] PROGMEM = 
        {8, 0x1e,0x1d,0x1c,0x1b,0x1a,0x19,0x18};

    const uint8_t num2[] PROGMEM = 
        {17, 0x1,0x4,0x5,0x6,0x7,0xe,0xb,0x8,0x11,0x14,0x17,0x1e,0x1d,0x1c,0x1b,0x18};

    const uint8_t num3[] PROGMEM =
        {17, 0x1,0x4,0x7,0xe,0xb,0x8,0x11,0x14,0x17,0x1e,0x1d,0x1c,0x1b,0x1a,0x19,0x18};
    
    const uint8_t num4[] PROGMEM = 
        {14, 0x1,0x2,0x3,0x4,0xb,0x14,0x1e,0x1d,0x1c,0x1b,0x1a,0x19,0x18};
    
    const uint8_t num5[] PROGMEM = 
        {17, 0x1,0x2,0x3,0x4,0x7,0xe,0xb,0x8,0x11,0x14,0x17,0x1e,0x1b,0x1a,0x19,0x18};

    const uint8_t num6[] PROGMEM = 
        {19, 0x1,0x2,0x3,0x4,0x5,0x6,0x7,0xe,0xb,0x8,0x11,0x14,0x17,0x1e,0x1b,0x1a,0x19,0x18};

    const uint8_t num7[] PROGMEM = 
        {13, 0x1,0x2,0x3,0xe,0x11,0x1e,0x1d,0x1c,0x1b,0x1a,0x19,0x18};

    const uint8_t num8[] PROGMEM = 
        {21, 0x1,0x2,0x3,0x4,0x5,0x6,0x7,0xe,0xb,0x8,0x11,0x14,0x17,0x1e,0x1d,0x1c,0x1b,0x1a,0x19,0x18};

    const uint8_t num9[] PROGMEM = 
        {19, 0x1,0x2,0x3,0x4,0x7,0xe,0xb,0x8,0x11,0x14,0x17,0x1e,0x1d,0x1c,0x1b,0x1a,0x19,0x18};
    
    const uint8_t dots[] PROGMEM = 
        {3, 0xc,0xa};
    

    // const uint8_t name[][]
} // namespace pattern



#endif