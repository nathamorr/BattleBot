#include <PS4Controller.h>
#include <Servo.h>

 /********************************************************
  *****************  Parametres PWM **********************
  ********************************************************/
  
const int freq = 5000; // Valeur de la Frequence
const int freqServo = 50; // Valeur de la Frequence pour servomoteur
const int resolution = 10; //La resolution
const int Channel[7] = {0,1,2,3,4,5,6}; //,4,5,6,7 //Configuration PWM: channels, pins associes aux sorties
const int MAX_DUTY_CYCLE = (int)(pow(2, resolution) - 1);

float puissanceX, puissanceY; // Calcul de la puissance de PWM en %

 /*------------------------------------------------------*/

 /********************************************************
  ********************** Moteurs *************************
  ********************************************************/

// Moteur G Av
const int M1Pin1 = 19 ; 
const int M1Pin2 = 21 ;

// Moteur D Av
const int M2Pin3 = 22 ;
const int M2Pin4 = 23 ;

// Moteur G Ar
const int M3Pin1 = 18 ;
const int M3Pin2 = 5 ;

const int servoArmePin = 27; // Pin servomoteur pour l'arme

/*------------------------------------------------------*/

 /********************************************************
  ****************** Parametres PS4 **********************
  ********************************************************/
  
// Valeur de Stick gauche: L
float valLx, valLy;

// PS4 Led
int r = 0, g = 0, b = 0;

// PS4 Flash
int flash_1 = 0, flash_2 = 0; 

// PS4 Rumble
int rumble_low = 0, rumble_high =0;

/*------------------------------------------------------*/

int carMode; // Choix de mode
bool valChanged; // Valeur de des param: led, flash, rumble a change 

/*------------------------------------------------------*/

void setup()
{
  Serial.begin(115200);

  /******************************************************
   *  Association des channels aux freq et resolution, association des pins
   ******************************************************/
   
  // Moteur 1: G Av
  ledcSetup(Channel[0], freq, resolution);
  ledcAttachPin(M1Pin1, Channel[0]);
  ledcSetup(Channel[1], freq, resolution);
  ledcAttachPin(M1Pin2, Channel[1]);

  // Moteur 2: D Av
  ledcSetup(Channel[2], freq, resolution);
  ledcAttachPin(M2Pin3, Channel[2]);
  ledcSetup(Channel[3], freq, resolution);
  ledcAttachPin(M2Pin4, Channel[3]);

  // Moteur 3 et 4: G/D Ar
  ledcSetup(Channel[4], freq, resolution);
  ledcAttachPin(M3Pin1, Channel[4]);
  ledcSetup(Channel[5], freq, resolution);
  ledcAttachPin(M3Pin2, Channel[5]);

  // Servomoteur pour l'arme
  ledcSetup(Channel[6], freqServo, resolution);
  ledcAttachPin(servoArmePin, Channel[6]);
/*------------------------------------------------------*/

  // Connexion avec la manette PS4
  PS4.begin("50:e0:85:c5:9a:ee");
  
}
 
void loop()
{
  if (PS4.isConnected()) {

    /****************************************
     ************ Choix de Mode *************
     ****************************************/
     
    if (PS4.Cross()) {
      carMode = 0; // Mode normal avec 2 roues avant en marche
    }

    if (PS4.Square()) {
      carMode = 1; // Mode normal avec 2 roues arriere en marche
    }
    
    if (PS4.Circle()) {
      carMode = 2; // Mode 4X4 avec 2 moteurs d'avant et 2 moteurs d'arriere
    }

    if (PS4.Triangle()){
      carMode = 3; // Mode arret
    }
    
    /*------------------------------------------------------*/

    /******************************************************
     * Reception des donnees, calcul de puissance, action *
     ******************************************************/
   // Valeur Analogique de button L2 de manette PS4
      valLx = PS4.LStickX();
      valLy = PS4.LStickY();

      puissanceY = abs((abs(valLy)-10.0)/117.0);
      puissanceX = abs((abs(valLx)-10.0)/117.0);

      if (puissanceX >= 1.0) {
        puissanceX = 1.0;
      }

      if (puissanceY >= 1.0) {
        puissanceY = 1.0;
      }

      if ((valLx <= 10 && valLx >= -10 && valLy <= 10 && valLy >= -10) || carMode == 3) {

        ledcWrite(Channel[0], 0);
        ledcWrite(Channel[1], 0);
        ledcWrite(Channel[2], 0);
        ledcWrite(Channel[3], 0);
        ledcWrite(Channel[4], 0);
        ledcWrite(Channel[5], 0);

        if( r!=255 || g!=255 || b!=255 ) {
          r = 255;
          g = 255;
          b = 255;
          
          flash_1 = 0;
          flash_2 = 0;
          rumble_low = 0;
          rumble_high = 0;

          valChanged = true;
        }
        
        Serial.println("Stop");         
      }
      
      // Avancer
      if (valLx >= -96 && valLx <= 121 && valLy-valLx >= 0 && abs(valLy) >= abs(valLx) && (valLx >10 || valLx <-10 || valLy >10 || valLy <-10) ) {

        if (carMode == 1){
          Serial.println("Mode 4X4 avance"); 
            
          ledcWrite(Channel[0], MAX_DUTY_CYCLE*puissanceY);
          ledcWrite(Channel[1], 0);          
          ledcWrite(Channel[2], MAX_DUTY_CYCLE*puissanceY);
          ledcWrite(Channel[3], 0);

          ledcWrite(Channel[4], MAX_DUTY_CYCLE*puissanceY);
          ledcWrite(Channel[5], 0); 
        }
        else if (carMode == 2){
          Serial.println("Mode 2 roues arriere avance"); 
          ledcWrite(Channel[4], MAX_DUTY_CYCLE*puissanceY);
          ledcWrite(Channel[5], 0); 
        }
        else{
          Serial.println("Mode 2 roues avant avance"); 
          ledcWrite(Channel[0], MAX_DUTY_CYCLE*puissanceY);
          ledcWrite(Channel[1], 0);          
          ledcWrite(Channel[2], MAX_DUTY_CYCLE*puissanceY);
          ledcWrite(Channel[3], 0);
        }
      
        if( r!=0 || g!=255 || b!=0) {
          r = 0;
          g = 255;
          b = 0;

          flash_1 = 0;
          flash_2 = 0;
          rumble_low = 0;
          rumble_high = 0;

          valChanged = true;
        }
        
        Serial.println("Avancer");
        Serial.println(puissanceY);
        Serial.println(puissanceX);
      }
      
      // Reculer
      if (valLx >= -97 && valLx <= 127 && valLy-valLx <= 0 && abs(valLy) >= abs(valLx) && (valLx >10 || valLx <-10 || valLy >10 || valLy <-10) ) {
        
        if (carMode == 1){
          Serial.println("Mode 4X4 recule"); 
          ledcWrite(Channel[0], 0);
          ledcWrite(Channel[1], MAX_DUTY_CYCLE*puissanceY);
          ledcWrite(Channel[2], 0);
          ledcWrite(Channel[3], MAX_DUTY_CYCLE*puissanceY);
          
          ledcWrite(Channel[4], 0);
          ledcWrite(Channel[5], MAX_DUTY_CYCLE*puissanceY);    
        }
        else if (carMode == 2){
          Serial.println("Mode 2 roues arriere recule"); 
          ledcWrite(Channel[4], 0);
          ledcWrite(Channel[5], MAX_DUTY_CYCLE*puissanceY);   
        }
        else{
          Serial.println("Mode 2 roues avant recule"); 
          ledcWrite(Channel[0], 0);
          ledcWrite(Channel[1], MAX_DUTY_CYCLE*puissanceY);
          ledcWrite(Channel[2], 0);
          ledcWrite(Channel[3], MAX_DUTY_CYCLE*puissanceY);
        }

        if( r!=255 || g!=0 || b!=0) {
          r = 255;
          g = 0;
          b = 0;

          flash_1 = 0;
          flash_2 = 0;
          rumble_low = 0;
          rumble_high = 0;

          valChanged = true;
        }
        
        Serial.println("Reculer");
        Serial.println(puissanceY);
        Serial.println(puissanceX);
      }
      
      // Tourner a droite
      if (valLy >= -77 && valLy <= 100 && valLy-valLx < 0 && abs(valLy)<abs(valLx) && (valLx >10 || valLx <-10 || valLy >10 || valLy <-10) ) {
        
        Serial.println("Mode 2 roues avant tourne a droite"); 
        ledcWrite(Channel[0], MAX_DUTY_CYCLE*puissanceX);
        ledcWrite(Channel[1],  MAX_DUTY_CYCLE*puissanceX);
        ledcWrite(Channel[2], 0);
        ledcWrite(Channel[3], 0);
      
        if( r!=0 || g!=200 || b!=170) {
          r = 0;
          g = 200;
          b = 170;

          flash_1 = 500;
          flash_2 = 500;
          rumble_low = 0;
          rumble_high = 0;

          valChanged = true;
        }
        
        Serial.println("Droite");
        Serial.println(puissanceY);
        Serial.println(puissanceX);
      }
      
      // Tourner a gauche
      if (valLy >= -97 && valLy <= 103 && valLy-valLx > 0 && abs(valLy)<abs(valLx) && (valLx >10 || valLx <-10 || valLy >10 || valLy <-10) ) {
        
        Serial.println("Mode 2 roues avant tourne a droite"); 
        ledcWrite(Channel[0], 0);
        ledcWrite(Channel[1], 0);
        ledcWrite(Channel[2], MAX_DUTY_CYCLE*puissanceX);
        ledcWrite(Channel[3],  MAX_DUTY_CYCLE*puissanceX);

        if( r!=0 || g!=200 || b!=170) {
          r = 0;
          g = 200;
          b = 170;

          flash_1 = 500;
          flash_2 = 500;
          rumble_low = 0;
          rumble_high = 0;

          valChanged = true;
        }
        
        Serial.println("Gauche");
        Serial.println(puissanceY);
        Serial.println(puissanceX);
      }

      
      
    /*------------------------------------------------------*/
    
    /*******************************************************
     ****************** Gestion de l'arme ******************
     *******************************************************/
     
      if ((PS4.L1() || PS4.R1())) {
        Serial.println("Arme active ");
        
        ledcWrite(Channel[6],25);//25
        Serial.println("done 110");   
        delay(500);
         
        ledcWrite(Channel[6],51); //102
        Serial.println("done 20"); 

        if (r != 255 || g != 80 || b != 115){
          r = 255;
          g = 80;
          b = 115;
          
          flash_1 = 500;
          flash_2 = 500;
          rumble_low = 50;
          rumble_high = 100;
  
          valChanged = true;
        }
        
      }
     
    /*------------------------------------------------------*/

    /******************************************************
     *********** Envoie des donnes a la manette ***********
     ******************************************************/

     if (valChanged == true){
      PS4.setLed(r, g, b);
      PS4.setFlashRate(flash_1, flash_2);
      PS4.setRumble(rumble_low, rumble_high);
      PS4.sendToController();

      valChanged = false;
     }
     
    /*------------------------------------------------------*/
    
   }
   else {
    Serial.println("Not Connected");
   }
}
