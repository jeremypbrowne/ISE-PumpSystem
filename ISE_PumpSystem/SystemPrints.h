#ifndef SYSTEMPRINTS_H
#define SYSTEMPRINTS_H

#define TIME_HEADER  "T"   
#define TIME_REQUEST  7


#include "FloatSensor.h"
#include "UltrasonicSensor.h"

FloatSensor MixFloat;
UltrasonicSensor WaterLevel;

class SystemPrints {

  private:
    int MIX_High;
    int MIX_Full;
    int MIX_Low;
    unsigned long pctime = 1542303840;
   
  public:
  SystemPrints(){};
//  setTime(pctime); // Sync Arduino clock to the time received on the serial port

    
    int printHeaders(){ 
      Serial.print("Run");   
      Serial.print("\t"); 
      Serial.print("Time (min)");
      Serial.print("\t");
      Serial.print("Stage");   
      Serial.print("\t\t");         
//      Serial.print("inchesAVG: ");
//      Serial.print("\t");
      Serial.print("High Float: "); 
      Serial.print("\t");
      Serial.print("Full Float: "); 
      Serial.print("\t");
      Serial.println("Low Float: "); 
     }

    int SystemState(int Run, int Stage) {

      Serial.print(Run);
      Serial.print("\t");

      float j = millis();
      Serial.print(j/60000);
      Serial.print("\t\t");

      if(Stage == 1){
        Serial.print("AEP");
        Serial.print("\t");
      }
      else if(Stage == 2){
        Serial.print("DI Water");
        Serial.print(" ");
      }
      else if(Stage == 3){
        Serial.print("DI Peri");
        Serial.print("\t");
      }
      else if(Stage == 4){
        Serial.print("ISE");
        Serial.print("\t");
      }
      else if(Stage == 5){
        Serial.print("Drain");
        Serial.print("\t");
      }
      else if(Stage == 6){
        Serial.print("DI-Wash");
        Serial.print("\t");
      }
      else if(Stage == 7){
        Serial.print("ISE-Wash");
        Serial.print(" ");
      }
      else if(Stage == 8){
        Serial.print("Drain-Wash");
        Serial.print(" ");
      }
      
      //Serial.print("\t\t");
      //delay(10);
      //float Level = WaterLevel.MIX_WaterLevel();
      //Serial.print(Level);

      
      MIX_High = MixFloat.checkMIX(MixFloat.MIX_HIGH);
      if(MIX_High == 1){
        Serial.print("\t");
        Serial.print("OFF");
      }
      else{
        Serial.print("\t");
        Serial.print("TRIPPED");        
      }
      MIX_Full = MixFloat.checkMIX(MixFloat.MIX_FULL);
      if(MIX_Full == 1){
        Serial.print("\t\t");
        Serial.print("OFF");
      }
      else{
        Serial.print("\t\t");
        Serial.print("TRIPPED");   
      }
      MIX_Low = MixFloat.checkMIX(MixFloat.MIX_LOW);
      if(MIX_Low == 1){
        Serial.print("\t\t");
        Serial.println("TRIPPED");
      }
      else{
        Serial.print("\t\t");
        Serial.println("OFF");        
      }

     delay(2000);
    };

};
#endif
