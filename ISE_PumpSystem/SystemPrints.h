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
      Serial.print("inchesAVG: ");
      Serial.print("\t");
      Serial.print("High Float: "); 
      Serial.print("\t");
      Serial.print("Full Float: "); 
      Serial.print("\t");
      Serial.println("Low Float: "); 
     }

    int SystemState() {

      float Level = WaterLevel.MIX_WaterLevel();
      MIX_High = MixFloat.checkMIX(MixFloat.MIX_HIGH);
      MIX_Full = MixFloat.checkMIX(MixFloat.MIX_FULL);
      MIX_Low = MixFloat.checkMIX(MixFloat.MIX_LOW);


      Serial.print(Level);
      Serial.print("\t\t");
      Serial.print(MIX_High);
      Serial.print("\t\t");
      Serial.print(MIX_Full);
      Serial.print("\t\t");
      Serial.println(MIX_Low);

    };

    

};
#endif
