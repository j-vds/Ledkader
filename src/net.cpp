#include "net.h"

#include "constants.h"

IPAddress local_IP(4,3,2,1);
IPAddress gateway(4,3,2,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);       // Create a webserver object that listens for HTTP request on port 80
WebSocketsServer webSocket(81);

bool firstSetup = true;

void startmDNS()
{
    MDNS.begin(mDNSname);                        // start the multicast domain name server
}


void startWebSocket() { // Start a WebSocket server
  webSocket.begin();                          // start the websocket server
  webSocket.onEvent(webSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
  Serial.println("WebSocket server started.");
}

void startServer() { // Start a HTTP server with a file read handler and an upload handler
  server.on("/",  HTTP_POST, []() {  // If a POST request is sent to the /edit.html address,
    server.send(200, "text/plain", "Hello world"); 
  });                       

  server.onNotFound([]() {
    server.send(404, "text/plain", "404: Not found");
    });   

  server.begin();     // start the HTTP server
  Serial.println("HTTP server started.");
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) 
{ // When a WebSocket message is received
  switch (type) {
    case WStype_DISCONNECTED:             // if the websocket is disconnected
        Serial.printf("[%u] Disconnected!\n", num);
        break;
    case WStype_CONNECTED: {              // if a new websocket connection is established
            IPAddress ip = webSocket.remoteIP(num);
            Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        }
        break;
    case WStype_TEXT:                     // if new text data is received
        Serial.printf("[%u] get Text: %s\n", num, payload);
        break;

    case WStype_BIN:
        break;
  }
}


void updateServers()
{
    MDNS.update();
    webSocket.loop();
    server.handleClient();
}

void netDisconnect()
{
    // stop server and websockets - maybe not needed 
    // server.close();
    // webSocket.close();
    WiFi.disconnect();
}

int netConnect(Adafruit_NeoPixel* strip)
{
    // COPIED FROM STRIPCLOCK
    // first try connecting to WiFi
    int current_attempt = 0;
    WiFi.begin(WC::WIFI_SSID, WC::WIFI_PWD);
    // showStatus((int) WiFi.status());

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

        showConnectAttempt(strip, current_attempt);
        strip->show();
        // showStatus((int) WiFi.status());
        
        if(++current_attempt > attempts)
        {
            return -1;
        }
    }

    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());

    // no backup if start fails for now :(
    if(firstSetup)
    {
        startmDNS();
        startServer();
        startWebSocket();

        firstSetup = false;
    }
    return 0;
}

void showConnectAttempt(Adafruit_NeoPixel* strip, uint8_t currentAttempt)
{
    for(uint8_t i = 239 ; i > 239 - currentAttempt ; i--)
    {
        strip->setPixelColor(i, strip->Color(127,127,10));
    }
}
