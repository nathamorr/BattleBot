#include <PS4Controller.h>

void setup() {
  Serial.begin(115200);
  PS4.begin("50:e0:85:c5:9a:ee");
  Serial.println("Ready.");
}

void loop() {
  // Below has all accessible outputs from the controller
  if (PS4.isConnected()) {
    PS4.setLed(255, 255, 102);

    /*
     * LEFT SIDE panel: Green main
     */
    if (PS4.Right()) {
      Serial.println("Right Button");
      PS4.setLed(0, 255, 0);
      //PS4.sendToController();
    }
    if (PS4.Down()) {
      Serial.println("Down Button");
      PS4.setLed(0, 200, 0);
      //PS4.sendToController();
    }
    if (PS4.Up()) {
      Serial.println("Up Button");
      PS4.setLed(0, 150, 0);
      //PS4.sendToController();
    }
    if (PS4.Left()) {
      Serial.println("Left Button");
      PS4.setLed(0, 100, 0);
      //PS4.sendToController();
    }

    /*
     * RIGHT SIDE panel: Blue main
     */
    if (PS4.Square()) {
      Serial.println("Square Button");
      PS4.setLed(0, 0, 255);
    }
    if (PS4.Cross()) {
      Serial.println("Cross Button");
      PS4.setLed(0, 0, 200);
    }
    if (PS4.Circle()) {
      Serial.println("Circle Button");
      PS4.setLed(0, 0, 150);
    }
    if (PS4.Triangle()) {
      Serial.println("Triangle Button");
      PS4.setLed(0, 0, 100);
    }

    if (PS4.UpRight()) Serial.println("Up Right");
    if (PS4.DownRight()) Serial.println("Down Right");
    if (PS4.UpLeft()) Serial.println("Up Left");
    if (PS4.DownLeft()) Serial.println("Down Left");

    if (PS4.L1()) Serial.println("L1 Button");
    if (PS4.R1()) Serial.println("R1 Button");

    if (PS4.Share()) Serial.println("Share Button");
    if (PS4.Options()) Serial.println("Options Button");
    if (PS4.L3()) Serial.println("L3 Button");
    if (PS4.R3()) Serial.println("R3 Button");

    if (PS4.PSButton()) Serial.println("PS Button");
    if (PS4.Touchpad()) Serial.println("Touch Pad Button");

    if (PS4.L2()) {
      Serial.printf("L2 button at %d\n", PS4.L2Value());
    }
    if (PS4.R2()) {
      Serial.printf("R2 button at %d\n", PS4.R2Value());
    }
  /*
    if (PS4.LStickX()) {
      Serial.printf("Left Stick x at %d\n", PS4.LStickX());
    }
    if (PS4.LStickY()) {
      Serial.printf("Left Stick y at %d\n", PS4.LStickY());
    }
    if (PS4.RStickX()) {
      Serial.printf("Right Stick x at %d\n", PS4.RStickX());
    }
    if (PS4.RStickY()) {
      Serial.printf("Right Stick y at %d\n", PS4.RStickY());
    }
*/
    if (PS4.Charging()) {
      Serial.println("The controller is charging");
      PS4.setFlashRate(50, 50);
    }
    else{
      PS4.setFlashRate(0, 0);
    }
    if (PS4.Audio()) Serial.println("The controller has headphones attached");
    if (PS4.Mic()) Serial.println("The controller has a mic attached");

    Serial.printf("Battery Level : %d\n", PS4.Battery());
    Serial.println();
    
    PS4.sendToController();
    
    // This delay is to make the output more human readable
    // Remove it when you're not trying to see the output
    delay(1000);
  }
}
