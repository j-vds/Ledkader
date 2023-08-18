#ifndef CONSTANTS_H
#define CONSTANTS_H

// char WIFI_SSID[] = "View5";
// char WIFI_PWD [] = "41690475";

namespace WC
{
    char WIFI_SSID[] = "PC_asus";
    char WIFI_PWD [] = "wachtwoordvanjeroen";
    // char WIFI_SSID[] = "View5";
    // char WIFI_PWD [] = "41690475";
}

int attempts = 8;

const char* mDNSname = "ledkader";

enum displayMode_t {
    DISP_NORMAL = false,
    DISP_SERVER = true,
};

#endif /*CONSTANTS*/
