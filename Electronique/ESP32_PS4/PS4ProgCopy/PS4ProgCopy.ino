#include <PS4Controller.h>

// Valeur de la Frequence
int freq = 5000;

//Configuration PWM: channels, pins associes aux sorties
int Channel[4] = {0,1,2,3};

// Pont en H1 pour les moteurs: ****** (a remplir)
int M1Pin1 = 19 ; // Moteur G/D Av/Ar
int M1Pin2 = 21 ;
int M2Pin3 = 22 ;
int M2Pin4 = 23 ;

//La resolution
int resolution = 8;

// Val precedant de R2 de la manette PS4
uint8_t previousVal = 0;

// Val precedant de L2 de la manette PS4
uint8_t previousValL2 = 0;

// Calcul de la puissance de PWM en %
float puissanceX;
float puissanceY;

int valLx;
int valLy;

// Mode de la voiture
int carMode;

void setup()
{
  Serial.begin(115200);

  /* 
   *  Association des channels aux freq et resolution, association des pins
   */
   
  // Moteur 1: G/D Av/Ar
  ledcSetup(Channel[0], freq, resolution);
  ledcAttachPin(M1Pin1, Channel[0]);
  ledcSetup(Channel[1], freq, resolution);
  ledcAttachPin(M1Pin2, Channel[1]);

  // Moteur 2: G/D Av/Ar
  ledcSetup(Channel[2], freq, resolution);
  ledcAttachPin(M2Pin3, Channel[2]);
  ledcSetup(Channel[3], freq, resolution);
  ledcAttachPin(M2Pin4, Channel[3]);


  // Connect PS4
  PS4.begin("50:e0:85:c5:9a:ee");
}
 
void loop()
{
   

   if (PS4.isConnected()) {
   
     if (PS4.Cross()){
      carMode = 3; // Les 4 moteurs active en meme temps
      PS4.setLed(0, 255, 0);
      PS4.sendToController();
      Serial.println("carMode 3 ");
     }
  
     if (PS4.Triangle()){
      carMode = 4; // Arret total
      PS4.setLed(0, 0, 0);
      PS4.sendToController();
      Serial.println("carMode 4 ");
     }

     // Valeur Analogique de button L2 de manette PS4
        float valLx = PS4.LStickX();
        float valLy = PS4.LStickY();

        puissanceY = abs((abs(valLy)-10.0)/117.0);
        puissanceX = abs((abs(valLx)-10.0)/117.0);

        if (puissanceX >= 1.0) {
          puissanceX = 1.0;
        }

         if (puissanceY >= 1.0) {
          puissanceY = 1.0;
        }

        if (valLx <= 10 && valLx >= -10 && valLy <= 10 && valLy >= -10) {
          
          ledcWrite(Channel[0], 0);
          ledcWrite(Channel[1], 0);
          ledcWrite(Channel[2], 0);
          ledcWrite(Channel[3], 0);
          
          Serial.println("Stop");
          Serial.println(valLx);
          Serial.println(valLy);          
        }
        
        // Avancer
        if (valLx >= -96 && valLx <= 121 && valLy-valLx >= 0 && abs(valLy) >= abs(valLx) && (valLx >10 || valLx <-10 || valLy >10 || valLy <-10) ) {
          
          ledcWrite(Channel[0], 255*puissanceY);
          ledcWrite(Channel[1], 0);          
          ledcWrite(Channel[2], 255*puissanceY);
          ledcWrite(Channel[3], 0);
          
          PS4.setLed(0, 255, 0);
          PS4.sendToController();
          
          Serial.println("Avancer");
          Serial.println(puissanceY);
          Serial.println(puissanceX);
        }
        
        // Reculer
        if (valLx >= -97 && valLx <= 127 && valLy-valLx <= 0 && abs(valLy) >= abs(valLx) && (valLx >10 || valLx <-10 || valLy >10 || valLy <-10) ) {
          
          ledcWrite(Channel[0], 0);
          ledcWrite(Channel[1], 255*puissanceY);
          ledcWrite(Channel[2], 0);
          ledcWrite(Channel[3], 255*puissanceY);
              
          PS4.setLed(255, 0, 0);
          PS4.sendToController();
          
          Serial.println("Reculer");
          Serial.println(puissanceY);
          Serial.println(puissanceX);
        }
        
        // Tourner a droite
        if (valLy >= -77 && valLy <= 100 && valLy-valLx < 0 && abs(valLy)<abs(valLx) && (valLx >10 || valLx <-10 || valLy >10 || valLy <-10) ) {
          
          ledcWrite(Channel[0], 255*puissanceY);
          ledcWrite(Channel[1], 0);
          ledcWrite(Channel[2], 0);
          ledcWrite(Channel[3], 255*puissanceX);
          
          Serial.println("Droite");
          Serial.println(puissanceY);
          Serial.println(puissanceX);
        }
        
        // Tourner a gauche
        if (valLy >= -97 && valLy <= 103 && valLy-valLx > 0 && abs(valLy)<abs(valLx) && (valLx >10 || valLx <-10 || valLy >10 || valLy <-10) ) {
          
          ledcWrite(Channel[0], 0);
          ledcWrite(Channel[1], 255*puissanceX);
          ledcWrite(Channel[2], 255*puissanceY);
          ledcWrite(Channel[3], 0);
          
          Serial.println("Gauche");
          Serial.println(puissanceY);
          Serial.println(puissanceX);
        }
        
      /*  
     if (PS4.LStickX()) {
//      carMode = 5; // Arret total
//      PS4.setLed(0, 0, 0);
//      PS4.sendToController();
//      Serial.println("carMode 4 ");
        Serial.printf("Left Stick x at %d\n", PS4.LStickX() );
        
        
        delay(2000);
     }

     if (PS4.LStickY()) {
//      carMode = 4; // Arret total
//      PS4.setLed(0, 0, 0);
//      PS4.sendToController();
//      Serial.println("carMode 4 ");      
        Serial.printf("Left Stick y at %d\n", PS4.LStickY());
        delay(2000);
     }

     if (PS4.RStickX()) {
//      carMode = 5; // Arret total
//      PS4.setLed(0, 0, 0);
//      PS4.sendToController();
//      Serial.println("carMode 4 ");
        Serial.printf("Right Stick x at %d\n", PS4.RStickX());
        delay(2000);
     }

     if (PS4.RStickY()) {
//      carMode = 4; // Arret total
//      PS4.setLed(0, 0, 0);
//      PS4.sendToController();
//      Serial.println("carMode 4 ");      
        Serial.printf("Right Stick y at %d\n", PS4.RStickY());
        delay(2000);
     }*/


     // Valeur Analogique de button L2 de manette PS4
     uint8_t analogValL2 = PS4.data.analog.button.l2;
     
     if (PS4.L1()) {
      Serial.println("Arme active ");
      if(previousValL2 != analogValL2) {    
//          ledcWrite(Channel[0], analogValL2);
//          ledcWrite(Channel[1], 0);
        }
        previousValL2 = analogValL2;
        PS4.setRumble(PS4.L2Value(), PS4.R2Value());
        PS4.sendToController();
        Serial.println("analog value L2:");
        Serial.println(analogValL2);
     }

     
     // Valeur Analogique de button R2 de manette PS4
     uint8_t analogVal = PS4.data.analog.button.r2;
     
     switch (carMode){
      case 1: // Avancer
        if(previousVal != analogVal) {    
          ledcWrite(Channel[0], analogVal);
          ledcWrite(Channel[1], 0);
        }
        previousVal = analogVal;
        Serial.println("case 1 analog value:");
        Serial.println(analogVal);
        
        break;
  
      case 2: // Reculer
        if(previousVal != analogVal) {    
          ledcWrite(Channel[2], analogVal);
           ledcWrite(Channel[3], 0);
        }
        previousVal = analogVal;
        Serial.println("case 2 analog value:");
        Serial.println(analogVal);
    
        break;
        
      case 3: // Les 4 moteurs active en meme temps
         if(previousVal != analogVal) {    
          ledcWrite(Channel[0], 0);
          ledcWrite(Channel[1], analogVal);
      
          ledcWrite(Channel[2], 0);
          ledcWrite(Channel[3], analogVal);
        }
        previousVal = analogVal;
        Serial.println("case 3 analog value:");
        Serial.println(analogVal);
        
        break;
        
      case 4: // Arret total
        ledcWrite(Channel[0], 0);
        ledcWrite(Channel[1], 0);
        ledcWrite(Channel[2], 0);
        ledcWrite(Channel[3], 0);
        break;
        
      default:
        break;
     }
   }
   else {
    Serial.println("Not Connected");
   }
}
