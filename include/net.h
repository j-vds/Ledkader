#ifndef NET_H
#define NET_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

IPAddress local_IP(4,3,2,1);
IPAddress gateway(4,3,2,1);
IPAddress subnet(255,255,255,0);

AsyncWebServer server(80);

void setupSoftAP()
{
    WiFi.softAPConfig(local_IP, gateway, subnet);
    bool result = WiFi.softAP("ledkader", "");
    Serial.println(WiFi.softAPIP());
    if(result)
    {
        Serial.println("SUCCES!");
    } else {
        Serial.println("SOFTAP FAILED");
    }

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "hello world");
    });

    // Start server
    server.begin();
    
}

void monitor()
{
    while(true)
    {
        Serial.print("connected: "); Serial.println(WiFi.softAPgetStationNum());
        delay(500);
    }
}

#endif