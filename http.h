String path = "http://petrum.warelan.com/api/v1/giveaway_claims";

DynamicJsonDocument ValidateBarcode(String barcode) {
  HTTPClient http;
  http.begin(path.c_str());
  http.addHeader("Content-Type", "application/json");
  
  DynamicJsonDocument body(512);
  body["barcode"] = barcode;
  body["serial_number"] =  GetMacAddress();
  String requestBody;
  serializeJson(body, requestBody);
  
  int httpCode = http.POST(requestBody);
  
  DynamicJsonDocument jsonResponse(512);
  
  if(httpCode > 0) {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    String response = http.getString();
    deserializeJson(jsonResponse, response);
    http.end();
    return jsonResponse;
  } else {
    jsonResponse["success"] = false;
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    http.end();
    return jsonResponse;
  }
}

void HttpSerial(String message) {
  String hook = "https://webhook.site/b705639f-3b8c-427d-9d25-4969596883b1";
  HTTPClient http;
  http.begin(hook.c_str());
  http.addHeader("Content-Type", "application/json");
  
  DynamicJsonDocument body(512);
  body["message"] = message;
  String requestBody;
  serializeJson(body, requestBody);
  
  int httpCode = http.POST(requestBody);
  
  // DynamicJsonDocument jsonResponse(512);
  
  // if(httpCode > 0) {
  //   Serial.printf("[HTTP] GET... code: %d\n", httpCode);
  //   String response = http.getString();
  //   deserializeJson(jsonResponse, response);
  //   http.end();
  //   return jsonResponse;
  // } else {
  //   jsonResponse["success"] = false;
  //   Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  //   http.end();
  //   return jsonResponse;
  // }
}
