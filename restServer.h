WebServer server(80);

void getNetworks() {
  Serial.println("Scanning networks...");
  byte ssidCount = WiFi.scanNetworks();
  DynamicJsonDocument response(512);
  JsonArray networks = response.createNestedArray("networks");

  for (int i=0; i<ssidCount; i++) {
    DynamicJsonDocument network(128);
    network["ssid"] = WiFi.SSID(i);
    network["signal_strength"] = WiFi.RSSI(i);
    networks.add(network);
  }
  
  String buf;
  serializeJsonPretty(response, buf);
  Serial.println("Networks found:");
  Serial.println(buf);
  server.send(200, F("application/json"), buf);
}

void setConnection() {
  flash_ssid = server.arg(String("ssid"));
  flash_pass = server.arg(String("password"));
  AttemptConnection();

  int attemptCount = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");    
    if (attemptCount >= 30) {
      Serial.println("\nIncorrect password or no IP assigned, try again");
      break;
    }
    attemptCount++;
  }  

  if (WiFi.status() == WL_CONNECTED) { 
    Serial.println(WiFi.localIP());   
    SetSession(flash_ssid, flash_pass);
    Serial.println("Connected...");
  }
}

void InitServer() {   
  server.on("/networks", HTTP_GET, getNetworks);
  server.on("/connect", HTTP_POST, setConnection);
}
