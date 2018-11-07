#ifndef FLOATSENSOR_H
#define FLOATSENSOR_H

class FloatSensor {

  private:

  public:
  
    int DI_floatSensor = 5;
    int MIX_HIGH = 4;    // High
    int MIX_FULL = 3;   // Full
    int MIX_LOW = 2;  // Low
            
    int checkDI(){
      int DI_Level = digitalRead(DI_floatSensor);

      return(DI_Level);    
    };

    int checkMIX(int sensor){
      int Mix_level = digitalRead(sensor);

      return(Mix_level);    
    };
    
//    int checkMIX_F(){
//      int Mix_F = digitalRead(MIX_FULL);
//
//      return(Mix_F);    
//    };
//
//    int checkMIX_L(){
//      int Mix_L = digitalRead(MIX_LOW);
//
//      return(Mix_L);    
//    };
    
};
#endif
