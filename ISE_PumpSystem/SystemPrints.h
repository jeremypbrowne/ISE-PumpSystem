#ifndef SYSTEMPRINTS_H
#define SYSTEMPRINTS_H
#include <TimeLib.h>

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
      Serial.print("Time (sec)");
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

      //digitalClockDisplay();

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
        Serial.println("TRIPPED");
      }
      else{
        Serial.print("\t\t");
        Serial.println("OFF");        
      }




    };

    void digitalClockDisplay(){
      // digital clock display of the time
      Serial.print(hour());
      printDigits(minute());
      printDigits(second());
      Serial.print(" ");
      Serial.print(day());
      Serial.print(" ");
      Serial.print(month());
    };

    void printDigits(int digits){
      // utility function for digital clock display: prints preceding colon and leading 0
      Serial.print(":");
      if(digits < 10)
        Serial.print('0');
      Serial.print(digits);
}

    

};
#endif
