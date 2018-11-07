#include "SystemPrints.h"
#include "UltrasonicSensor.h"
#include "FloatSensor.h"
#include "PumpControl.h"

SystemPrints mainOutput;
UltrasonicSensor mainSensor;
FloatSensor mainFloat;
PumpControl mainPumps;

// duration of the each pump for system in miliseconds
#define AEP_Time 300000     
#define DI_Water_Time 23500
#define DI_Peri_Time 120000
#define ISE_Time 300000
#define Drain_Time 90000

void setup() {
 
  Serial.begin(115200);
  Serial.println("ISE PUMP SYSTEM");

   pinMode(mainPumps.AEP, OUTPUT);
   pinMode(mainPumps.DI_Water, OUTPUT);
   pinMode(mainPumps.DI_Peri, OUTPUT);
   pinMode(mainPumps.Drain, OUTPUT);

// Set the Relay to all pumps off
  digitalWrite(mainPumps.AEP, HIGH); // DI Water Pump
  digitalWrite(mainPumps.DI_Water, HIGH); // DI Water Peristaltic Pump
  digitalWrite(mainPumps.DI_Peri, HIGH); // AEP Peristaltic Pump
  digitalWrite(mainPumps.Drain, HIGH); // Diaphram Drain Pump

// Define inputs and outputs
  pinMode(mainSensor.trigPin, OUTPUT);
  pinMode(mainSensor.echoPin, INPUT);

// Float Switches
  pinMode(mainFloat.DI_floatSensor, INPUT_PULLUP);
  pinMode(mainFloat.MIX_HIGH, INPUT_PULLUP);
  pinMode(mainFloat.MIX_FULL, INPUT_PULLUP);
  pinMode(mainFloat.MIX_LOW, INPUT_PULLUP);

 // mainPumps.primePUMPS();
  //mainPumps.primeSystem();
}

void loop() {
 //Water Level Sensors

  if(mainFloat.checkDI() == LOW){
    delay(10);
    Serial.println("AEP ON");    
    mainPumps.RunPump(mainPumps.AEP, AEP_Time, 1); // 300000
    Serial.println("AEP OFF");
    delay(1000);
    
    Serial.println("DI Water Pump ON");
    mainPumps.RunPump(mainPumps.DI_Water, DI_Water_Time, 3);
    Serial.println("DI Water Pump ON");
    delay(1000);
    
    Serial.println("DI Perisotalic ON");
    mainPumps.RunPump(mainPumps.DI_Peri, DI_Peri_Time,3);
    Serial.println("DI Perisotalic OFF");
    delay(1000);

    Serial.println("ISE SYSTEM ON");
    mainPumps.RunPump(mainPumps.ISE, ISE_Time, 1);
    Serial.println("ISE SYSTEM OFF");
    delay(1000);
    
    Serial.println("DRAIN ON");
    mainPumps.RunPump(mainPumps.Drain, Drain_Time, 4);
    Serial.println("DRAIN OFF");
    delay(1000);
    
  }
  else{
    Serial.println("DI RESERVE TOO LOW - System End - PLEASE REFIL");
    delay(250);
  }
}
