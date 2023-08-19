#ifndef NET_H
#define NET_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>


#include <Adafruit_NeoPixel.h>
//https://tttapa.github.io/ESP8266/Chap14%20-%20WebSocket.html


extern Adafruit_NeoPixel strip;

void startmDNS();
void startWebSocket();
void startServer();

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

void updateServers();

void netDisconnect();
int netConnect(Adafruit_NeoPixel* strip);

void showConnectAttempt(Adafruit_NeoPixel* strip, uint8_t currentAttempt);

void handleRoot();

// old
void setupSoftAP();

void disableSoftAP();

void monitor();

#endif