#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class StripClock
{
    public:
        StripClock(Adafruit_NeoPixel* strip) : 
            m_strip(strip),
            m_minute(0), 
            m_hour(0), 
            m_needsUpdate(true),
            m_syncStatus(0)
        {};

        void sync();
        bool update(bool forceUpdate = false);
        void updateStrip(Adafruit_NeoPixel* strip, bool* stopEffect);
        void showStatus();
        void showStatus(uint8_t status);
        void showCurrentAttempt(uint8_t currentAttempt);
        void draw();

    private:
        Adafruit_NeoPixel*  m_strip;
        uint8_t             m_minute;
        uint8_t             m_hour;
        bool                m_needsUpdate;
        uint8_t             m_syncStatus;
    // clock is current time?

};

inline const uint8_t* numHelper(uint8_t value);

#endif // TIMER_H 