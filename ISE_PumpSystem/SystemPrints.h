#ifndef SYSTEMPRINTS_H
#define SYSTEMPRINTS_H

#include "FloatSensor.h"
#include "UltrasonicSensor.h"

FloatSensor MixFloat;
UltrasonicSensor WaterLevel;

class SystemPrints {

  private:
    int MIX_High;
    int MIX_Full;
    int MIX_Low;
   
  public:
  SystemPrints(){};

    
    int printHeaders(){  
      Serial.print("Time (min)");
      Serial.print("\t");         
      Serial.print("inchesAVG: ");
      Serial.print("\t");
      Serial.print("High Float: "); 
      Serial.print("\t");
      Serial.print("Full Float: "); 
      Serial.print("\t");
      Serial.println("Low Float: "); 
     }

    int SystemState() {
      float j = millis();
      Serial.print(j/60000);
      Serial.print("\t\t");
      delay(10);
      float Level = WaterLevel.MIX_WaterLevel();
      Serial.print(Level);
      MIX_High = MixFloat.checkMIX(MixFloat.MIX_HIGH);
      if(MIX_High == 1){
        Serial.print("\t\t");
        Serial.print("OFF");
      }
      else{
        Serial.print("\t\t");
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
        Serial.println("OFF");
      }
      else{
        Serial.print("\t\t");
        Serial.println("TRIPPED");        
      }




    };

    

};
#endif
