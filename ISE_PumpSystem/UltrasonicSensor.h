#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

class UltrasonicSensor {

  private:
      
    int trigPin = 7;     // Trigger - brown wire
    int echoPin = 6;    // Echo - gray wire
    float duration, cm, inches,inchesLAST;
    float inchesSUM = 0; 
    float inchesAVG = 0; 
    float offSet;
  

  public:

    int SensorTest(){
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
        Serial.println("in, ");
        delay(45);
      }
      inchesSUM = 0;
     
    };


    int MIX_WaterLevel(){
      
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
        delay(100);
      }
      
      inchesAVG = inchesSUM / 10 + offSet;
      inchesSUM = 0;
      
      return(inchesAVG);

 
      
    };

    int calibration(){
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
      
      return(offSet); 
  };


};
#endif
