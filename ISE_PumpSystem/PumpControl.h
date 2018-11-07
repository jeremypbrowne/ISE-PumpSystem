#ifndef PUMPSYSTEM_H
#define PUMPSYSTEM_H

#include "FloatSensor.h"

FloatSensor Float;
SystemPrints Output;
UltrasonicSensor pumpSensor;

class PumpControl {


  private:


  public:

    int AEP = 12;       // in2 - AEP Water Peristaltic
    int DI_Water = 11;  // in3 -DI Water Pump
    int DI_Peri = 10;   // in4 - DI Peristaltic
    int Drain = 9;      // in5 -Diaprham Pump - Drain
    int ISE = 8;        // in6 -ISE Persitaltic
    float t;

    int RunPump(int pump, float duration, int Switch){

        digitalWrite(pump,LOW);
        Output.printHeaders();
        delay(10);
        if(Switch == 1){
          t = millis();
          delay(100);
          Serial.println(t/60000);
          while((millis() - t) < duration){
            Output.SystemState();
          }
        }
        else if(Switch == 2){
          t = millis();
          while((millis() - t) < duration && Float.checkMIX(Float.MIX_HIGH) != 0  ){
            Output.SystemState();           
          }
        }
        else if(Switch == 3){
          t = millis();
          while((millis() - t) < duration && Float.checkMIX(Float.MIX_FULL) == 1){
            Output.SystemState();           
          }
        }        
        else if(Switch == 4){
          t = millis();
          while((millis() - t) < duration && Float.checkMIX(Float.MIX_LOW) != 1){
            Output.SystemState();           
          }     
        }        
        digitalWrite(pump,HIGH);    
      }

    int primePUMPS() {

      Serial.println("Prime Pumps");
      if( Float.checkDI() == !LOW){
        Serial.println("DI RESERVE TOO LOW - System End - PLEASE REFIL");
        while(1);
      }
      else{
        Serial.print("DI Sensor State: "); Serial.println(Float.checkDI());
      }

      // So that all conecting tubes have fluid in the - no lag time to fill
      // Fills tant drains the mixing chamber
      Serial.println("Pump - Test & Prime");
      digitalWrite(AEP, LOW); // DI Water Pump
      delay(5000);
      digitalWrite(AEP, HIGH);
      delay(1000);
      digitalWrite(DI_Water, LOW); // DI Water Peristaltic Pump
      delay(5000);
      digitalWrite(DI_Water, HIGH);
      delay(1000);
      digitalWrite(DI_Peri, LOW); // AEP Peristaltic Pump
      delay(5000);
      digitalWrite(DI_Peri, HIGH);
      delay(1000);
      digitalWrite(Drain, LOW); // Diaphram Drain Pump
      delay(5000);
      digitalWrite(Drain, HIGH);
      Serial.println("Test End");
      delay(500);
    }

    int primeSystem(){

        Serial.println("Drain the Mix");
        Output.printHeaders();
        while(Float.checkMIX(Float.MIX_LOW) != 1) { 
          digitalWrite(Drain, LOW);
          Output.SystemState();
        }
  
        digitalWrite(Drain, HIGH);
        delay(500);
        digitalWrite(Drain, LOW);
        delay(5000);
        digitalWrite(Drain, HIGH);
  
        Serial.println("Calibration Fill");   

        Output.printHeaders();
        while(Float.checkMIX(Float.MIX_FULL) != 0){
        digitalWrite(DI_Water, LOW);
        Output.SystemState();
        }
        digitalWrite(DI_Water, HIGH);
        Serial.print("Pump OFF");
        delay(500);

        float calib = pumpSensor.calibration(); // ultrasonic sensor adjustment
 

        Serial.println("Drain the Mix");
        Output.printHeaders();
        while(Float.checkMIX(Float.MIX_LOW) != 1){ 
          digitalWrite(Drain, LOW);
          Output.SystemState();
        }
  
        digitalWrite(Drain, HIGH);
        delay(500);
        digitalWrite(Drain, LOW);
        float t  = millis();
        while((millis() - t) < 75000 && Float.checkMIX(Float.MIX_LOW) != 0){
          Output.SystemState();
        }
 
        digitalWrite(Drain, HIGH);


  
    }

 
  
};

#endif
