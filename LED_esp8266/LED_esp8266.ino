
#include "effects.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

ESP8266WebServer webServer(80);
ESP8266HTTPUpdateServer webUpdater;


effect ledStrip = effect(100, D8);

void setup() {
  Serial.begin(115200);
  pinMode(D8, OUTPUT);

  pinMode(BUTTON,INPUT_PULLUP);  // internal pull-up resistor
  //attachInterrupt (digitalPinToInterrupt (BUTTON), ledStrip.changeEffect, CHANGE); // pressed



  //The SSID must be >8 characters and <64 characters
  //I'm adding the chip ID onto the end to get a unique (ish) name
  //String ssid = "ESP8266 " + String(ESP.getChipId(), HEX);
  String ssid = "LED AP";
 
  //The password must be <64 characters and can be left blank for no password
  String pass = "password";
 
  Serial.printf("WiFiSSID: '%s'\n", ssid.c_str());
  Serial.printf("Password: '%s'\n", pass.c_str());
 
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid.c_str(), pass.c_str());
  
//  http://192.168.4.1/update
//  http://192.168.4.1/LED
//  http://192.168.4.1/
  

  /*
  webServer.on("/", [](){
    webServer.send(200, "text/plain", "Successfullly wifi updated");
  });
  */

  webServer.on("/LED_button", HTTP_GET, handleLED_button);     // Call the 'handleLED_button' function when a client requests URI "/LED_button"
  webServer.on("/LED_push", HTTP_POST, handleLED_push);       // Call the 'handleLED_push' function when a POST request is made to URI "/LED_push"
  webServer.onNotFound(handleNotFound);
  
  webUpdater.setup(&webServer);
  webServer.begin();
  
  ledStrip.setEffect(0);
}


void loop() { 
/*
  for(int i = 0; i < 10; i ++){
    webServer.handleClient();
    delay(1);
  }    
  ledStrip.setEffect(ledStrip.getEffect());
  ledStrip.setAll(0,0,0);
  */
  webServer.handleClient();
}

void handleLED_button() {                         // When URI / is requested, send a web page with a button to toggle the LED
  webServer.send(200, "text/html", "<form action=\"/LED_push\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");
}

void handleLED_push() {                          // If a POST request is made to URI /LED_push

  ledStrip.setEffect(ledStrip.getEffect + 1);           // Change the state of the LED
  webServer.sendHeader("Location","/LED_button");       // Add a header to respond with a new location for the browser to go to the home page again
  webServer.send(303);                                  // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleNotFound(){
  webServer.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
