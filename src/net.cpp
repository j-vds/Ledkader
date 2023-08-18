#include "net.h"

IPAddress local_IP(4,3,2,1);
IPAddress gateway(4,3,2,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);       // Create a webserver object that listens for HTTP request on port 80
// WebSocketsServer webSocket(81); 


void startmDNS(const char* mDNSname)
{
    MDNS.begin(mDNSname);                        // start the multicast domain name server
}

// bool setupNeeded = true;

// void setupSoftAP()
// {
//     if(!setupNeeded) return;

//     Serial.println("AP activated");

//     IPAddress local_IP(4,3,2,1);
//     IPAddress gateway(4,3,2,1);
//     IPAddress subnet(255,255,255,0);

//     bool configResult = WiFi.softAPConfig(local_IP, gateway, subnet);
//     if(!configResult)
//     {
//         Serial.println("configResult failed");
//     }
    
//     bool result = WiFi.softAP("ledkader", "");
//     Serial.println(WiFi.softAPIP());
//     if(result)
//     {
//         Serial.println("SUCCES!");
//     } else {
//         Serial.println("SOFTAP FAILED");
//         return;
//     }

//     // Route for root / web page
//     server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
//         request->send(200, "text/plain", "hello world");
//     });

//     // Start server
//     server.begin();

//     setupNeeded = false;
// }

// void disableSoftAP()
// {
//     if(setupNeeded) return;
    
//     Serial.println("AP deactivated");

//     server.reset();
//     server.end();
//     if(!WiFi.softAPdisconnect(true))
//     {
//         // error
//         Serial.println("SOFTAP disable failed");
//     }

//     setupNeeded = true;
// }


// void monitor()
// {
//     while(true)
//     {
//         Serial.print("connected: "); Serial.println(WiFi.softAPgetStationNum());
//         delay(500);
//     }
// }

