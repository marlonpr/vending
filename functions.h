String GetMacAddress() {
  String mac_address_string = WiFi.macAddress();
  String mac = String(mac_address_string[0]) + String(mac_address_string[1]) +
      String(mac_address_string[3]) + String(mac_address_string[4]) + String(mac_address_string[6])
      + String(mac_address_string[7]) + String(mac_address_string[9]) + String(mac_address_string[10])
      + String(mac_address_string[12]) + String(mac_address_string[13]) + String(mac_address_string[15])
      + String(mac_address_string[16]);
  return mac;
}

bool HasStoredWifi() {
  return (flash_ssid != "No ssid" && flash_pass != "No pass");
}

bool ConnectedToWifi() {
  return WiFi.status() == WL_CONNECTED;
}