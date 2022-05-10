#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>

// Gobals
String flash_ssid;
String flash_pass;
byte resetButtonPin = 21;
int relays[12] = {27, 4, 22, 32, 2, 33, 15, 26, 25, 14, 13, 12};

#include "functions.h"
#include "http.h"
#include "keypad.h"
#include "barcode.h"
#include "wifi.h"
#include "restServer.h"
#include "AP.h"


void setup() {
  Serial.begin(115200); 
  
  IniUsb(); 
  pinMode(resetButtonPin, INPUT);

  InitRelays();
  
  Serial.println("WARELAN VENDING MACHINE");
  
  if (digitalRead(resetButtonPin) == HIGH) {
    Serial.println("Reseting stored SSID");
    SetSession("No ssid", "No pass");
  }

  GetSession(&flash_ssid, &flash_pass);

  if (flash_ssid != "No ssid" && flash_pass != "No pass") {
    Serial.println("Attempting to connect with stored SSID");
    // AttemptConnection();
  } else {
    Serial.println("No stored session found...");
    WiFi_AP();
    InitServer();
  }
}

void loop() {
  if (!ConnectedToWifi() && HasStoredWifi()) {
    AttemptConnection();
    delay(2000);
  } else if (!ConnectedToWifi()) {
    server.handleClient();
  } else if (ConnectedToWifi()) {
    ReadBardcode();
  }
}