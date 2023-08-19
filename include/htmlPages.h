#ifndef HTMLPAGES_H
#define HTMLPAGES_H

#if defined(ESP8266) || defined(ESP32)
#include <pgmspace.h>
#endif


const char snakePage[] PROGMEM = R"rawliteral(
    <!Doctype html>
<html>
<style>

.btn-group {
  display: grid;
  grid-template-columns: 1fr 1fr 1fr;
  grid-auto-rows: 200px;
}

</style>
<body>

<div class="btn-group">
  <button onClick="sendRaw();">RESET</button>
  <button>UP</button>
  <button  onclick="sendRGB();">TEST</button>
  <button>LEFT</button>
  <button>DOWN</button>
  <button>RIGHT</button>
</div>

</body>
<script>
var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);
connection.onopen = function () {
  connection.send('Connect ' + new Date());
};
connection.onerror = function (error) {
  console.log('WebSocket Error ', error);
};
connection.onmessage = function (e) {
  console.log('Server: ', e.data);
};
connection.onclose = function () {
  console.log('WebSocket connection closed');
};

function sendRGB () {
  console.log("button pressed" );
  connection.send("test");
}

function sendRaw(){
  console.log("raw ");
  blob = new Blob([0x1d,0x1a,0x22,0x25,0x2d,0x2a,0x32,0x35,0x3d,0x3a,0x42,0x45,0x4d,0x4a,0x52,0x55]);
  connection.send(blob);
  
}

function testJson(){
  console.log("json");
  const msg = {
    "br": 10,
    "leds": [0x1d,0x1a,0x22,0x25,0x2d,0x2a,0x32,0x35,0x3d,0x3a,0x42,0x45,0x4d,0x4a,0x52,0x55]
  };
  connection.send(msg);
}
</script>
</html>)rawliteral";

const char testPage[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Ledkader home</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    p { font-size: 1.2rem;}
    body {  margin: 0;}
    .topnav { overflow: hidden; background-color: #50B8B4; color: white; font-size: 1rem; }
    .content { padding: 20px; }
    .card { background-color: white; box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5); }
    .cards { max-width: 800px; margin: 0 auto; display: grid; grid-gap: 2rem; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); }
    .reading { font-size: 1.4rem; }
  </style>
</head>
<body>
  <div class="topnav">
    <h1>BME280 WEB SERVER (SSE)</h1>
  </div>
  <div class="content">
    <div class="cards">
      <div class="card">
        <p><i class="fas fa-thermometer-half" style="color:#059e8a;"></i> TEMPERATURE</p><p><span class="reading"><span id="temp">%TEMPERATURE%</span> &deg;C</span></p>
      </div>
      <div class="card">
        <p><i class="fas fa-tint" style="color:#00add6;"></i> HUMIDITY</p><p><span class="reading"><span id="hum">%HUMIDITY%</span> &percnt;</span></p>
      </div>
      <div class="card">
        <p><i class="fas fa-angle-double-down" style="color:#e1e437;"></i> PRESSURE</p><p><span class="reading"><span id="pres">%PRESSURE%</span> hPa</span></p>
      </div>
    </div>
  </div>
<script>
/*
if (!!window.EventSource) {
 var source = new EventSource('/events');
 
 source.addEventListener('open', function(e) {
  console.log("Events Connected");
 }, false);
 source.addEventListener('error', function(e) {
  if (e.target.readyState != EventSource.OPEN) {
    console.log("Events Disconnected");
  }
 }, false);
 
 source.addEventListener('message', function(e) {
  console.log("message", e.data);
 }, false);
 
 source.addEventListener('temperature', function(e) {
  console.log("temperature", e.data);
  document.getElementById("temp").innerHTML = e.data;
 }, false);
 
 source.addEventListener('humidity', function(e) {
  console.log("humidity", e.data);
  document.getElementById("hum").innerHTML = e.data;
 }, false);
 
 source.addEventListener('pressure', function(e) {
  console.log("pressure", e.data);
  document.getElementById("pres").innerHTML = e.data;
 }, false);
}
*/
</script>
</body>
</html>)rawliteral";


#endif