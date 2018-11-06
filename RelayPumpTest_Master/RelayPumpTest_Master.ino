

int in2 = 12;    // AEP Water Peristaltic
int in3 = 11;   // DI Water Pump
int in4 = 10;  // DI Peristaltic
int in5 = 9;  // Diaprham Pump - Drain
int in6 = 8; // ISE Persitaltic

int DI_floatSensor = 5;

int MIX_floatSensor1 = 4;    // High
int MIX_floatSensor2 = 3;   // Full
int MIX_floatSensor3 = 2;  // Low

int trigPin = 7;     // Trigger - brown wire
int echoPin = 6;    // Echo - gray wire
float duration, cm, inches,inchesLAST;
float inchesSUM = 0; float inchesAVG = 0; float offSet;

#include <Servo.h>
Servo servo;


void setup() {
  Serial.begin(115200);
  Serial.println("ISE PUMP SYSTEM");

  // initialize the LED pin as an output:

  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in5, OUTPUT);

  digitalWrite(in2, HIGH); // DI Water Pump
  digitalWrite(in3, HIGH); // DI Water Peristaltic Pump
  digitalWrite(in4, HIGH); // AEP Peristaltic Pump
  digitalWrite(in5, HIGH); // Diaphram Drain Pump

  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Float Switches
  pinMode(DI_floatSensor, INPUT_PULLUP);
  pinMode(MIX_floatSensor1, INPUT_PULLUP);
  pinMode(MIX_floatSensor2, INPUT_PULLUP);
  pinMode(MIX_floatSensor3, INPUT_PULLUP);

  primePUMPS();
  primeSystem();
}


int primePUMPS() {

  Serial.println("Prime Pumps");
//  if(digitalRead(DI_floatSensor) == !LOW){
//    Serial.println("DI RESERVE TOO LOW - System End - PLEASE REFIL");
//   while(1);
// }
//  else{
//    Serial.print("DI Sensor State: "); Serial.println(digitalRead(DI_floatSensor));
//  }
  
Serial.print("Testing Ultrasonics Sensor");Serial.println("");
delay(10);
  for (int i = 0; i < 15; i++) {

    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);

    // Convert the time into a distance
    cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
    inches = ((duration / 2) / 74); // Divide by 74 or multiply by 0.0135
    Serial.print(inches);
    Serial.println(" in, ");
    delay(45);
  }
  inchesSUM = 0;

  // So that all conecting tubes have fluid in the - no lag time to fill
  // Fills thant drains the mixing chamber
  Serial.println("Pump - Test & Prime");
  digitalWrite(in2, LOW); // DI Water Pump
  delay(5000);
  digitalWrite(in2, HIGH);
  delay(1000);
  digitalWrite(in3, LOW); // DI Water Peristaltic Pump
  delay(5000);
  digitalWrite(in3, HIGH);
  delay(1000);
  digitalWrite(in4, LOW); // AEP Peristaltic Pump
  delay(5000);
  digitalWrite(in4, HIGH);
  delay(1000);
  digitalWrite(in5, LOW); // Diaphram Drain Pump
  delay(5000);
  digitalWrite(in5, HIGH);
  Serial.println("Test End");
  delay(500);

}

int primeSystem(){


 Serial.println("Drain the Mix");
  printHeaders();
 while(digitalRead(MIX_floatSensor3) != 1)
  { 
    digitalWrite(in5, LOW);
    sonicSensor();
  }
  
 digitalWrite(in5, HIGH);
 delay(500);
 digitalWrite(in5, LOW);
 delay(5000);
 digitalWrite(in5, HIGH);
  
Serial.println("Calibration Fill");

  printHeaders();
  while(digitalRead(MIX_floatSensor2) != 0)
  {
    digitalWrite(in3, LOW);
    sonicSensor();
  }
  digitalWrite(in3, HIGH);
  Serial.print("Pump OFF");
  delay(500);
  
  Serial.print("Ultrasonic Sensor Test");Serial.println("");
  delay(100);
  for (int i = 0; i < 50; i++) {

    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);

    // Convert the time into a distance
    cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
    inches = ((duration / 2) / 74); // Divide by 74 or multiply by 0.0135
    inchesSUM = inchesSUM + inches;
    Serial.print(inches);
    Serial.println(" in, ");
    delay(45);

  }

  offSet = (13.75-3.00)  - (inchesSUM / 50);
  Serial.print("OffSet: ");
  Serial.println(offSet);
  inchesAVG = 0; 
  inchesSUM = 0;

   Serial.println("Drain the Mix");
  printHeaders();
 while(digitalRead(MIX_floatSensor3) != 1)
  { 
    digitalWrite(in5, LOW);
    sonicSensor();
  }
  
 digitalWrite(in5, HIGH);
 delay(500);
 digitalWrite(in5, LOW);

      float t  = millis();
    while((millis() - t) < 75000 && digitalRead(MIX_floatSensor2) != 0){
      sonicSensor();
    }
 
 digitalWrite(in5, HIGH);


  
}

void loop() {

  //Water Level Sensors
  static int DI_level = digitalRead(DI_floatSensor);

  if(DI_level == LOW)   {

    digitalWrite(in2, LOW);
    Serial.println("2 AEP ON");
    printHeaders();
    float t  = millis();
    while((millis() - t) < 300000){
      sonicSensor();
    }
    digitalWrite(in2, HIGH);
    Serial.println("2 AEP OFF");   
    delay(1000);

    digitalWrite(in3, LOW);
    Serial.println("3 Water Pump ON ");
    printHeaders();
      t  = millis();
    while((millis() - t) < 23500 && digitalRead(MIX_floatSensor2) == 1){
      sonicSensor();
    }
    digitalWrite(in3, HIGH);  
    Serial.println("3 Water Pump Off ");Serial.println("");
    delay(1000);



    digitalWrite(in4, LOW);
    Serial.println("4 Peristaltic DI ON");
    printHeaders();
     t  = millis();
    while((millis() - t) <  120000 && digitalRead(MIX_floatSensor2) == 1){
      sonicSensor();
    }
    digitalWrite(in4, HIGH);
    Serial.println("4 Peristaltic DI OFF");
    delay(1000);

    digitalWrite(in5, LOW);
    Serial.println("5 Drain ON");
    printHeaders();
     t  = millis();
    while((millis() - t) < 80000 && digitalRead(MIX_floatSensor3) != 1){
      sonicSensor();
    }
    digitalWrite(in5, HIGH);
    Serial.println("5 Drain OFF ");
    delay(1000);
  }
  else{
    Serial.print("DI RESERVE TOO LOW - System End - PLEASE REFIL");
  }

}

float sonicSensor() {
  
  for (int i = 0; i < 10; i++) {

    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);

    // Convert the time into a distance
    cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
    inches = ((duration / 2) / 74); // Divide by 74 or multiply by 0.0135
    inchesSUM = inchesSUM + inches;

    //  Serial.print(inches);
    //  Serial.print(" in, ");
    //  Serial.print(inchesSUM);
    //  Serial.print(" in");
    //  Serial.println();
    delay(100);

  }
  inchesAVG = inchesSUM / 10 + offSet;

  Serial.print(inchesAVG);
  Serial.print("\t\t");
  Serial.print(inchesLAST);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(digitalRead(MIX_floatSensor1));
  Serial.print("\t\t");
  Serial.print(digitalRead(MIX_floatSensor2));
  Serial.print("\t\t");
  Serial.println(digitalRead(MIX_floatSensor3));

  inchesSUM = 0; 

}

int printHeaders(){
      
  Serial.print("inchesAVG: ");
  Serial.print("\t");
  Serial.print("inchesLAST: ");
  Serial.print("\t");
  Serial.print("High Float: "); 
  Serial.print("\t");
  Serial.print("Full Float: "); 
  Serial.print("\t");
  Serial.println("Low Float: "); 
  
}
