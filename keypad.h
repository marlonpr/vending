void InitRelays() {
  for (int i = 0; i < 12; i++) {
    pinMode(relays[i], OUTPUT);
  }
}

void Dispatch(String position, int amount) {
  HttpSerial(position);
  HttpSerial(String(amount));

  int digitCount = position.length();

  // String out = String(amount);
  // HttpSerial(String("Digit amount: " + out));

  char digits[digitCount];
  
  for (int i = 0; i < sizeof(digits); i++) {
    digits[i] = position[i];
  }

  // out = String(digits[0]);
  // HttpSerial(out);
  // out = String(digits[1]);
  // HttpSerial(out);

  for (int i = 0; i < amount; i++) {
    for (int j = 0; j < digitCount; j++) {
      // out = String(relays[5]);
      // HttpSerial(String("Prueba: " + out));

      // out = String(digits[j]);
      // HttpSerial(String("Digit j: " + out));

      // out = String(relays[digits[j]]);
      // HttpSerial(String("Digit press: " + out));
      int digit = int(digits[j]) - '0';
      digitalWrite(relays[digit], HIGH);
      delay(800);
      digitalWrite(relays[digit], LOW);
      delay(8000);      
    }
  }
}
