#include "SystemPrints.h"
#include "UltrasonicSensor.h"
#include "FloatSensor.h"
#include "PumpControl.h"

SystemPrints mainOutput;
UltrasonicSensor mainSensor;
FloatSensor mainFloat;
PumpControl mainPumps;

// duration of the each pump for system in miliseconds
#define AEP_Time 315000 //300000     
#define DI_Water_Time   23500
#define DI_Peri_Time 1000 //120000
#define ISE_Time  1200000 // 20 minutes of sampleing
#define Drain_Time  90000

int Run = 1;
int Stage = 0;

void setup() {
 
  Serial.begin(115200);
  Serial.println("ISE PUMP SYSTEM");

   pinMode(mainPumps.AEP, OUTPUT);
   pinMode(mainPumps.DI_Water, OUTPUT);
   pinMode(mainPumps.DI_Peri, OUTPUT);
   pinMode(mainPumps.ISE, OUTPUT);
   pinMode(mainPumps.Drain, OUTPUT);

// Set the Relay to all pumps off
  digitalWrite(mainPumps.AEP, HIGH); // DI Water Pump
  digitalWrite(mainPumps.DI_Water, HIGH); // DI Water Peristaltic Pump
  digitalWrite(mainPumps.DI_Peri, HIGH); // AEP Peristaltic Pump
  digitalWrite(mainPumps.ISE, HIGH); // AEP Peristaltic Pump
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
// mainPumps.primeSystem();
  Serial.println(" 1 - Start System ");
//  Serial.println(" 2 - End System ");
}

void loop() 
{

}

void serialEvent(){

  static char serial_buf[128];
  static int serial_count = 0;
      
  byte incomingByte = Serial.read();  //Serial.print(incomingByte); Serial.print("\t");
  serial_buf[serial_count++]=incomingByte; //Serial.print(serial_count); Serial.println("\t");
  int pos = 0;

  if(incomingByte == '\n')
  {
    serial_buf[serial_count]=0;   // terminate the string
    pos =atoi(serial_buf);        // convert string to #
//    Serial.println("\t\t"); Serial.println(pos);
    
    if(pos ==  1 && mainFloat.checkDI() == LOW)
    {
      Serial.println("ISE PUMP SYSTEM BEGIN");
      memset(serial_buf, 0, sizeof(serial_buf));
      serial_count = 0; 
      mainOutput.printHeaders();
      ISE_system(pos);
    }
    else if(pos ==  1 && mainFloat.checkDI() == HIGH)
    {
      Serial.println("DI RESERVE TOO LOW - System End - PLEASE REFIL");
      delay(250);
    }
    else if(pos == 2)
    {
      Serial.println("ISE PUMP SYSTEM END");
    }
        
    memset(serial_buf, 0, sizeof(serial_buf));
    serial_count = 0;    
  }
  
  if(serial_count>sizeof(serial_buf)){
    serial_count = 0;
    //Serial.println("Reset");
  }
  delay(250);  
}

double ISE_system(int pos){

    if(pos == 1 && mainFloat.checkDI() == HIGH ){
 
      Stage = 1;    
      mainPumps.RunPump(Run, Stage, mainPumps.AEP, AEP_Time, 1); // 300000
      delay(1000);
      
      Stage = 2; 
      mainPumps.RunPump(Run, Stage, mainPumps.DI_Water, DI_Water_Time, 3);
      delay(1000);
    
      Stage = 3; 
      mainPumps.RunPump(Run, Stage, mainPumps.DI_Peri, DI_Peri_Time,3);;
      delay(1000);

      Stage = 4; 
      mainPumps.RunPump(Run, Stage, mainPumps.ISE, ISE_Time, 1);
      delay(1000);
    
      Stage = 5; 
      mainPumps.RunPump(Run, Stage, mainPumps.Drain, Drain_Time, 4);
      delay(1000);

      mainPumps.RunPump(Run, Stage, mainPumps.Drain, 90000, 1);

      // Wash Cycle

      Stage = 6; 
      mainPumps.RunPump(Run, Stage, mainPumps.DI_Water, 12000, 3);
      delay(1000);
    
      Stage = 7; 
      mainPumps.RunPump(Run, Stage, mainPumps.ISE, 300000 , 1);
      delay(1000);

      Stage = 8; 
      mainPumps.RunPump(Run, Stage, mainPumps.Drain, Drain_Time, 4);
      delay(1000);

      mainPumps.RunPump(Run, Stage, mainPumps.Drain, 30000, 1);

      Run = Run+1;
      serialEvent();
    
    }



  
}
