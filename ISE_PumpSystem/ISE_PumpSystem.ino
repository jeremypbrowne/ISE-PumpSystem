#include "SystemPrints.h"
#include "UltrasonicSensor.h"
#include "FloatSensor.h"
#include "PumpControl.h"

SystemPrints mainOutput;
UltrasonicSensor sensor;
FloatSensor Switch;
PumpControl mainPumps;

void setup() {
  // put your setup code here, to run once:
 
  Serial.begin(115200);
  Serial.println("ISE PUMP SYSTEM");
//
   pinMode(mainPumps.AEP, OUTPUT);
//  pinMode(in3, OUTPUT);
//  pinMode(in4, OUTPUT);
//  pinMode(in5, OUTPUT);
//
//
//// Set the Relay to all pumps off
//  digitalWrite(in2, HIGH); // DI Water Pump
//  digitalWrite(in3, HIGH); // DI Water Peristaltic Pump
//  digitalWrite(in4, HIGH); // AEP Peristaltic Pump
//  digitalWrite(in5, HIGH); // Diaphram Drain Pump
//
////Define inputs and outputs
//  pinMode(trigPin, OUTPUT);
//  pinMode(echoPin, INPUT);
//
//  // Float Switches
//  pinMode(DI_floatSensor, INPUT_PULLUP);
//  pinMode(MIX_floatSensor1, INPUT_PULLUP);
//  pinMode(MIX_floatSensor2, INPUT_PULLUP);
//  pinMode(MIX_floatSensor3, INPUT_PULLUP);

//  primePUMPS;
//  primeSystem;
}

void loop() {
  // put your main code here, to run repeatedly:

}
