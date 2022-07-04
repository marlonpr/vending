String GetMacAddress() {
  // Oportunidad: Usar una función para splitear la MAC address
  String mac_address_string = WiFi.macAddress();
  // Split string by ':'
  String mac_address_split[6];
  int i = 0;
  for (int j = 0; j < mac_address_string.length(); j++) {
    if (mac_address_string[j] == ':') {
      i++;
    } else {
      mac_address_split[i] += mac_address_string[j];
    }
  }
  return mac_address_split;
}

bool HasStoredWifi() {
  return (flash_ssid != "No ssid" && flash_pass != "No pass");
}

bool ConnectedToWifi() {
  return WiFi.status() == WL_CONNECTED;
}