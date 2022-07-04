void AttemptConnection() {
  Serial.println("Attempting connection");
  Serial.println("SSID: " + flash_ssid);
  Serial.println("Password: " + flash_pass);
  Serial.println("---------------------");

  char ssidChar[flash_ssid.length()];
  char passwordChar[flash_pass.length()];
  flash_ssid.toCharArray(ssidChar, flash_ssid.length() + 1);
  flash_pass.toCharArray(passwordChar, flash_pass.length() + 1);
  WiFi.begin(ssidChar, passwordChar);
  WiFi.setHostname("WARELAN-VM");
  for (int i = 0; i < 30; i++) {
    Serial.print(".");
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nConnected to " + flash_ssid);
      break;
    }
    delay(1000);
  }
}

void SetSession(String ssid, String pass) {
  Serial.println("Writing WiFi configuration to EEPROM");
  EEPROM.begin(96);
  
  for (int i = 0; i < 32; i++) {
    if (i < pass.length()) {
      EEPROM.write(i, pass[i]);
    } else {
      EEPROM.write(i, '|');
    }
  }

  for (int i = 32; i < 96; i++) {
    if (i < ssid.length() + 32) {
      EEPROM.write(i, ssid[i-32]);
    } else {
      EEPROM.write(i, '|');
    }
  }
  EEPROM.commit();
  EEPROM.end();
}

void GetSession(String *ssid, String *pass){
  EEPROM.begin(96);
  char current;

  for (int i = 0; i < 32; i++) {
    current = EEPROM.read(i);
    if (current != '|' && current != '\t' && current != '\n' && current != '\r') {
      *pass += char(EEPROM.read(i));
      flash_pass = *pass;
    }
  }

  for (int i = 32; i < 96; i++) {
    current = EEPROM.read(i);
    if (current != '|' && current != '\t' && current != '\n' && current != '\r') {
      *ssid += char(EEPROM.read(i));
      flash_ssid = *ssid;
    }
  }

  EEPROM.end();
}
