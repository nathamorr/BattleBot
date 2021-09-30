#include <PS4Controller.h>

// Valeur de la Frequence
int freq = 5000;

//Configuration PWM: channels, pins associes aux sorties
int Channel[4] = {0,1,2,3};
int M1Pin1 = 22 ;
int M1Pin2 = 23 ;
int M2Pin3 = 21 ;
int M2Pin4 = 19 ;

//La resolution
int resolution = 8;

uint8_t previousVal = 0;

int carMode;

void setup()
{
  Serial.begin(115200);
  
  ledcSetup(Channel[0], freq, resolution);
  ledcAttachPin(M1Pin1, Channel[0]);
  ledcSetup(Channel[1], freq, resolution);
  ledcAttachPin(M1Pin2, Channel[1]);

  ledcSetup(Channel[2], freq, resolution);
  ledcAttachPin(M2Pin3, Channel[2]);
  ledcSetup(Channel[3], freq, resolution);
  ledcAttachPin(M2Pin4, Channel[3]);
  
  PS4.begin("50:e0:85:c5:9a:ee");
}
 
void loop()
{
  
   uint8_t analogVal = PS4.data.analog.button.r2;

   if (!PS4.isConnected()) {
    Serial.println("Not Connected");
   }
   
   if (PS4.Cross()){
    carMode = 1;
    Serial.println("carMode 1 ");
   }
   
   if (PS4.Circle()){
    carMode = 2;
    Serial.println("carMode 2 ");
   }

   if (PS4.Square()){
    carMode = 4;
    Serial.println("carMode 4 ");
   }

   if (PS4.Triangle()){
    carMode = 3;
    Serial.println("carMode 3 ");
   }
  
   switch (carMode){
    case 1:
      if(previousVal != analogVal) {    
        ledcWrite(Channel[0], analogVal);
        ledcWrite(Channel[1], 0);
      }
      previousVal = analogVal;
      Serial.println("case 1 analog value:");
      Serial.println(analogVal);
      
      break;

    case 2:
      if(previousVal != analogVal) {    
        ledcWrite(Channel[2], analogVal);
         ledcWrite(Channel[3], 0);
      }
      previousVal = analogVal;
      Serial.println("case 2 analog value:");
      Serial.println(analogVal);
  
      break;
      
    case 3:
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
      
    case 4:
      ledcWrite(Channel[0], 0);
      ledcWrite(Channel[1], 0);
      ledcWrite(Channel[2], 0);
      ledcWrite(Channel[3], 0);
      break;
      
    default:
      break;
   }
 
  

  
   /* 
  if (PS4.Square()){
//     ledcWrite(M1Pin1, 0);
//    ledcWrite(M1Pin2, 0);
    Serial.println("Stop");
  }//*/
}
