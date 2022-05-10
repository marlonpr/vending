#include <hiduniversal.h>
#include <usbhid.h>
#include <Usb.h>
#include <usbhub.h>
#include <hidboot.h>
#include <SPI.h>

String scanCode = "";
int i = 0;
USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);

class KbdRptParser : public KeyboardReportParser {
 protected:  
  void OnKeyDown  (uint8_t mod, uint8_t key);
  void OnKeyPressed(uint8_t key);
};

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key) {
  uint8_t c = OemToAscii(mod, key);
  if (c)
    OnKeyPressed(c);
}

void KbdRptParser::OnKeyPressed(uint8_t key) {
  scanCode = scanCode + String((char)key);
}

KbdRptParser Prs;

void IniUsb() {
  #if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect boards with built-in USB CDC serial connection
#endif
  Serial.println("Start");
  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");
  delay( 200 );
  Hid.SetReportParser(0, &Prs);
}

void dispatch(String position, int amount) {              
  digitalWrite(4, HIGH);   
  delay(500);                      
  digitalWrite(4, LOW);    
  delay(500);                       
  digitalWrite(33, HIGH);   
  delay(500);                       
  digitalWrite(33, LOW);    
  delay(500);  
}

void HandleBarcode(String barcode) {
  DynamicJsonDocument response = ValidateBarcode(barcode);
  Serial.println("Server response:");
  serializeJsonPretty(response, Serial);
  Serial.println("--");
  if (response["success"]) {
    JsonArray products = response["products"].as<JsonArray>();
    for (JsonVariant product : products) {
      // Serial.println(product["position"].as<String>());
      // Serial.println(product["amount"].as<int>());
      // Serial.println("---");
      Dispatch(product["position"].as<String>(), product["amount"].as<int>());
      delay(10000);
    }
  } else {
    Serial.println("Products unavailable");
  }
  delay(2000);
}

void ReadBardcode() {
  delay(1);
  Usb.Task();
  i = i + 1;
  if(i == 2000) {
    if(scanCode != "") {
      Serial.println(scanCode);
      HandleBarcode(scanCode);
      // DynamicJsonDocument serverResponse[512];
      // serverResponse = ValidateBarcode(scanCode);
      // if (serverResponse["success"] == true) {
        // int productCount = sizeof(serverResponse["products"]/sizeof(serverResponse[]));
        // for (int j = 0; j < productCount; j++) {
          // dispatch(serverResponse["products"][j]["position"], serverResponse["products"][j]["amount"]);
        //}
      //}
      // dispatch();
      scanCode = "";
    }  
    i = 0;
  }
}
