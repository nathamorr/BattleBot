#include <Servo.h>

static const int servoArmePin = 27;

const int freqServo = 50; // Valeur de la Frequence pour servomoteur
const int resolution = 10;
const int MAX_DUTY_CYCLE = (int)(pow(2, resolution) - 1);

Servo servo1;

void setup() {
    Serial.begin(115200);
    //servo1.attach(servoPin);
  ledcSetup(0, freqServo, resolution);
  ledcAttachPin(servoArmePin, 0);
}

void loop() {
  
//    servo1.write(110);
//    delay(2000);
//    Serial.println("done 110");   
//     
//    servo1.write(20);
//    delay(2000);
//    Serial.println("done 20"); 

      ledcWrite(0,51); 
      Serial.println("done 102"); 
      delay(500);
      
      ledcWrite(0,25);
      Serial.println("done 25");   
      delay(500);


    /*
    for(int posDegrees = 10; posDegrees <= 100; posDegrees++) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(20);
    }

    for(int posDegrees = 100; posDegrees >= 10; posDegrees--) {
        servo1.write(posDegrees);
        Serial.println(posDegrees);
        delay(20);
    }
    */
}
