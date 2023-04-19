/**************************+++++++++++程序使用 Arduino1.8.2 编写，编译错误请使用较新版本+++++++++++*************************/
#include "Arduino.h"
#include <AccelStepper.h>
#include <MultiStepper.h>
#include "Configuration.h"

AccelStepper stepper_x(1, 2, 5);      //tower1
AccelStepper stepper_y(1, 3, 6);      //tower2
AccelStepper stepper_z(1, 4, 7);      //tower3
//AccelStepper stepper_a(1, 12, 13);

MultiStepper steppers;

float delta[NUM_STEPPER];                         
float cartesian[NUM_AXIS] = {0.0, 0.0, 0.0};      //当前坐标
float destination[NUM_AXIS];                      //目标坐标
boolean dataComplete = false;

/*********************************************Main******************************************/
void setup() {
  Serial.begin(9600);
  pinMode(EN, OUTPUT);

  steppers.addStepper(stepper_x);
  steppers.addStepper(stepper_y);
  steppers.addStepper(stepper_z);

  stepperSet(1600, 400.0);
  stepperReset(); 
  delay(1000);
}

void loop() {
  Get_command() ;                                         //串口获取坐标数据
  Process_command();                                      //解析坐标，执行代码
}

/***************************************Get_commond*******************************************/
void Get_command(){  
  while(Serial.available()){
    int spacePosition;
    String command = Serial.readStringUntil('\n');

    if(serial_notes){
      Serial.print("currentPosition: ");
      for(int i=0;i<3;i++){
         Serial.print(cartesian[i]);
         Serial.print(" ");
      }   
      Serial.println();
    }
    if(serial_notes) Serial.print("seiralData: ");Serial.println(command);
    
    command.trim();
     
    do{
      spacePosition = command.indexOf(' ');
    
      if(spacePosition != -1)
      {
          switch(command[0]){
            case 'X':
              destination[0] = command.substring(1, spacePosition).toFloat();
              break;
            case 'Y':
              destination[1] = command.substring(1, spacePosition).toFloat();
              break;
            default:break;
          }
          command = command.substring(spacePosition+1, command.length());
      }
      else
      {
        destination[2] = command.substring(1, spacePosition).toFloat();  
      }
    }while(spacePosition > 0);

    if(destination[0] == 0 && destination[1] == 0 && destination[2] == 0){                 //
        stepperReset();                                                                    //
                                                                                           //
        for(int i=0;i<3;i++){                                                              //
           cartesian[i] = destination[i];                                                  //
        }                                                                                  //
    }                                                                                      //
    else                                                                                   //
    {                                                                                      //
        dataComplete = true;
    }                                                                                      //
    
    if(serial_notes){
     Serial.print("destinationPosition: ");
     Serial.print(destination[0]);
     Serial.print(" ");
     Serial.print(destination[1]);
     Serial.print(" ");
     Serial.println(destination[2]);
    }
  }

}

/***************************************Process_command***************************************/
void Process_command(){
  if(dataComplete){
    digitalWrite(EN, LOW);
    
    if(cartesian[0] == destination[0] && cartesian[1] == destination[1] && cartesian[2] == destination[2]){     //
      return;                                                                                                   //
    }                                                                                                           //
    else                                                                                                        //
    {                                                                                                           //

      Line_DDA(destination[0], destination[1], destination[2]);
    }                                                                                                           //  
    
  }
  dataComplete = false;
  digitalWrite(EN, HIGH);
}

/************************************************** DDA ************************************************/
void Line_DDA(float x1, float y1, float z1)
{
  float x0, y0, z0;         // 当前坐标点
  float cx, cy;             // x、y 方向上的增量
  
  x0 = cartesian[0];y0 = cartesian[1];z0 = cartesian[2];
   
  int steps = abs(x1 - x0) > abs(y1 - y0) ? abs(x1 - x0) : abs(y1 - y0);
  
  cx = (float)(x1 - x0) / steps;
  cy = (float)(y1 - y0) / steps;
  
  for(int i = 0; i <= steps; i++)
  { 
    
    cartesian[0] = x0 - cartesian[0];
    cartesian[1] = y0 - cartesian[1];
    cartesian[2] = z1 - cartesian[2];

    calculate_delta(cartesian);
    
    stepperSet(1350.0, 50.0);
    stepperMove(delta[0], delta[1], delta[2]);
  
    cartesian[0] = x0;
    cartesian[1] = y0;
    cartesian[2] = z1;
  
    x0 += cx;
    y0 += cy;
    
    if(serial_notes){
      Serial.print("currentPosition: ");
      for(int i=0;i<3;i++){
         Serial.print(cartesian[i]);
         Serial.print(" ");
      }   
      Serial.println();
      Serial.println("-------------------------------------------------");
    }

  }

}

/***************************************calculateDelta****************************************/
void calculate_delta(float cartesian[3])
{
  if(cartesian[0] == 0 && cartesian[1] == 0 && cartesian[2] == 0){       //
      delta[0] = 0; delta[1] =0; delta[2] = 0;                           //
  }                                                                      //
  else                                                                   //
  {                                                                      //
      delta[TOWER_1] = sqrt(delta_diagonal_rod_2
                       - sq(delta_tower1_x-cartesian[X_AXIS])
                       - sq(delta_tower1_y-cartesian[Y_AXIS])
                       ) + cartesian[Z_AXIS];
      delta[TOWER_2] = sqrt(delta_diagonal_rod_2
                       - sq(delta_tower2_x-cartesian[X_AXIS])
                       - sq(delta_tower2_y-cartesian[Y_AXIS])
                       ) + cartesian[Z_AXIS];
      delta[TOWER_3] = sqrt(delta_diagonal_rod_2
                       - sq(delta_tower3_x-cartesian[X_AXIS])
                       - sq(delta_tower3_y-cartesian[Y_AXIS])
                       ) + cartesian[Z_AXIS];

     for(int i=0;i<3;i++){                                                //
        delta[i] = ((delta[i] - 111.96) * stepsPerRevolution / LEAD);     //
     }                                                                    //
  }                                                                       //

  if(serial_notes){
      Serial.print("cartesian x="); Serial.print(cartesian[X_AXIS]);
      Serial.print(" y="); Serial.print(cartesian[Y_AXIS]);
      Serial.print(" z="); Serial.println(cartesian[Z_AXIS]);
    
      Serial.print("delta tower1="); Serial.print(delta[TOWER_1]);
      Serial.print(" tower2="); Serial.print(delta[TOWER_2]);
      Serial.print(" tower3="); Serial.println(delta[TOWER_3]);
  }

}

/****************************************stepperMove******************************************/
void stepperMove(long _x, long _y, long _z){             
    long positions[3];
    positions[0] = _x;                        //steps < 0, 向下运动 ; steps > 0, 向上运动
    positions[1] = _y;
    positions[2] = _z;

    steppers.moveTo(positions);
    steppers.runSpeedToPosition();

    stepper_x.setCurrentPosition(0);
    stepper_y.setCurrentPosition(0);
    stepper_z.setCurrentPosition(0);
}

/****************************************stepperSet******************************************/
void stepperSet(float _v, float _a){
  stepper_x.setMaxSpeed(_v);                  //MaxSpeed: 650
  stepper_x.setAcceleration(_a);  
  stepper_y.setMaxSpeed(_v);
  stepper_y.setAcceleration(_a);
  stepper_z.setMaxSpeed(_v);
  stepper_z.setAcceleration(_a);

}

/****************************************stepperReset******************************************/
void stepperReset(){
  digitalWrite(EN, LOW);
  
  while(digitalRead(SENSOR_TOWER1) && digitalRead(SENSOR_TOWER2) && digitalRead(SENSOR_TOWER3)){
    stepperMove(10, 10, 10);
  }

  stepperSet(1200.0, 100.0);
  stepperMove(-400, 0, 0);
  while(digitalRead(SENSOR_TOWER1)){
    stepperMove(10, 0, 0);
    
  }

  stepperMove(0, -400, 0);
  while(digitalRead(SENSOR_TOWER2)){
    stepperMove(0, 10, 0);
  }

  stepperMove(0, 0, -400);
  while(digitalRead(SENSOR_TOWER3)){
    stepperMove(0, 0, 10);
  }

  for(int i=0;i<3;i++){
     cartesian[i] = 0.0;
  }  

  if(serial_notes) Serial.println("resetComplete!");

  digitalWrite(EN, HIGH);
}
