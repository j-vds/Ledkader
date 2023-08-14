#include "stripClock.h"

#include <ESP8266WiFi.h>

#include "patterns.h"
#include "stripUtils.h"
#include "constants.h"



void StripClock::sync(void)
{
    // https://github.com/scanlime/esp8266-Arduino/blob/master/tests/Time/Time.ino
    // CONNECT TO WIFI


    int current_attempt = 0;
    WiFi.begin(WC::WIFI_SSID, WC::WIFI_PWD);
    showStatus((int) WiFi.status());

    Serial.print("Connecting...");
    while (WiFi.status() != WL_CONNECTED)
    {
        // WiFi.disconnect();
        delay(250);
        Serial.print(".");
        WiFi.reconnect();
        // WiFi.begin(WC::WIFI_SSID, WIFI_PWD);
        WiFi.waitForConnectResult();
        Serial.println("WIFI status: ");
        Serial.println(WiFi.status());

        showStatus((int) WiFi.status());
        
        if(++current_attempt > attempts)
        {
            return;
        }
    }

    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());

    // configTime("CEST", "pool.ntp.org");

    configTime(3600 * 2, 0, "pool.ntp.org", "time.nist.gov");
      Serial.println("\nWaiting for time");
    while (!time(nullptr)) {
        Serial.print(".");
        delay(100);
    }
    Serial.println("\nWaiting for time");

    while(true)
    {
        time_t now = time(nullptr);
        tm* current  = localtime(&now);
        m_hour = current->tm_hour;
        m_minute = current->tm_min;

        delay(50);
        if(m_minute)
        {
            break;
        }
    }

    // update time
    // update();

    
    // disconnect from WiFi
    WiFi.disconnect();

    // start HW timer -> auto update
    // not really supported :/


}   

bool StripClock::update()
{
    time_t now = time(nullptr);
    tm* current = localtime(&now);

    if(current->tm_sec % 5 == 0)
    {
        m_minute = current->tm_min;
        m_hour = current->tm_hour;

        // update screen
        draw();

        return true;
    } else {
        return false;
    }
}

// {
    
//     m_minute = ++m_minute % 60;
//     if(m_minute == 0)
//     {
//         m_hour == ++m_hour % 24;
//     }
//     m_needsUpdate = true;
// }


void StripClock::showStatus(uint8_t status)
{
    m_syncStatus = status;
    showStatus();
}

void StripClock::showStatus()
{
    // 4 leds in bottom corner indicate the sync status
    uint32_t color;

    switch(m_syncStatus)
    {
        case WL_NO_SSID_AVAIL:
            color = m_strip->Color(255,0,0);
            break;
        case WL_CONNECTED:
            color = m_strip->Color(0,255,0);
            break;
        default:
            color = m_strip->Color(0,0,255);
    };

    m_strip->setPixelColor(246, color);
    m_strip->show();
}

/*
*/

void StripClock::draw()
{
    m_strip->clear();

    uint32_t c = m_strip->Color(255,50,20);
    
    drawMemOffset(m_strip, numHelper( (uint8_t) (m_hour / 10)), 4, true, c);
    drawMemOffset(m_strip, numHelper( m_hour % 10),10, false, c);
    drawMemOffset(m_strip, pattern::dots,14, false, c);
    drawMemOffset(m_strip, numHelper( (uint8_t) (m_minute / 10)),18, false, c);
    drawMemOffset(m_strip, numHelper( m_minute % 10),24, false, c);

    // show happens in showStatus
    showStatus();
}  

inline const uint8_t* numHelper(uint8_t value)
{
    switch(value)
    {
        case 0:
            return pattern::num0;
        case 1:
            return pattern::num1;
        case 2:
            return pattern::num2;
        case 3:
            return pattern::num3;
        case 4:
            return pattern::num4;
        case 5:
            return pattern::num5;
        case 6:
            return pattern::num6;
        case 7:
            return pattern::num7;
        case 8:
            return pattern::num8;
        case 9:
        default:
            return pattern::num9;

    }
};
