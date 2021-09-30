#include <PS4Controller.h>

void setup() {
  Serial.begin(115200);

  // Replace the "03:03:03:03:03:03" with the MAC address
  // the controller wants to pair to
  PS4.begin("50:e0:85:c5:9a:ee");
  Serial.println("Ready.");
}

void loop() {
  if (PS4.isConnected()) {
    
    if (PS4.LStickX()) {
      Serial.printf("Left Stick x at %d\n", PS4.LStickX());
    }
    if (PS4.LStickY()) {
      Serial.printf("Left Stick y at %d\n", PS4.LStickY());
    }
    /*
    if (PS4.RStickX()) {
      Serial.printf("Right Stick x at %d\n", PS4.RStickX());
    }
    if (PS4.RStickY()) {
      Serial.printf("Right Stick y at %d\n", PS4.RStickY());
    }
    */
    delay(5000);
  }
}
