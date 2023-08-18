#ifndef NET_H
#define NET_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

//https://tttapa.github.io/ESP8266/Chap14%20-%20WebSocket.html

void startmDNS(const char* mDMSname);

void setupSoftAP();

void disableSoftAP();

void monitor();

#endif