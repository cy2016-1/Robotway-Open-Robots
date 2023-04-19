/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-02-08 https://www.robotway.com/                                 
------------------------------------------------------------------------------------*/
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
float cartesian[NUM_AXIS] = {0.0, 0.0, 0.0};         //当前坐标
float destination[NUM_AXIS];                         //目标坐标
boolean dataComplete = false;

float down = -111;
float up = -105;

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

  Get_command(0, 0, down);
  Process_command(); 
  
  delay(1000);
}

void loop() {
  float r = 25;
  float x1 = 0.0;
  float y1 = 0.0;

  Get_command(25, 0, down);
  Process_command(); 
  delay(1000);
  
  for(int i=0;i<2;i++){
    for(float i=0.0;i<=360;i+=10){
      x1 = r * cos(i / 180 * 3.141592);
      y1 = r * sin(i / 180 * 3.141592);
      
      Get_command(x1, y1, down);
      Process_command();                                     
    }
  }
  delay(1000);

  for(int j=0;j<2;j++){
    for(float i=360.0;i>=0;i-=10){
      x1 = r * cos(i / 180 * 3.141592);
      y1 = r * sin(i / 180 * 3.141592);
      
      Get_command(x1, y1, down);
      Process_command();                                     
    }
  }
  delay(1000);



  Get_command(0, 0, down);
  Process_command();  
  
  test();
  delay(1000);
  
  stepperReset();
  delay(1000);
  
}

/***************************************Get_commond*******************************************/
void Get_command(float _dx, float _dy, float _dz){  
  destination[0] = _dx;
  destination[1] = _dy;
  destination[2] = _dz;
  
  if(destination[0] == 0 && destination[1] == 0 && destination[2] == 0){
      stepperReset();  
  }
  else
  {
      dataComplete = true;
  }
  
  if(serial_notes){
   Serial.print("destinationPosition: ");
   Serial.print(destination[0]);
   Serial.print(" ");
   Serial.print(destination[1]);
   Serial.print(" ");
   Serial.println(destination[2]);
  }

}

/***************************************Process_command***************************************/
void Process_command(){
  if(dataComplete){
    digitalWrite(EN, LOW);
    
    if(cartesian[0] == destination[0] && cartesian[1] == destination[1] && cartesian[2] == destination[2]){
      return;  
    }
    else
    {

      Line_DDA(destination[0], destination[1], destination[2]);
    }
    
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
  if(cartesian[0] == 0 && cartesian[1] == 0 && cartesian[2] == 0){
      delta[0] = 0; delta[1] =0; delta[2] = 0;
  }
  else
  {
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

     for(int i=0;i<3;i++){
        delta[i] = ((delta[i] - 111.96) * stepsPerRevolution / LEAD);
     }
  }

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
  
  if(cartesian[2] != 0){
    Get_command(0, 0, cartesian[2]);
    Process_command();
    digitalWrite(EN, LOW);
  }
  
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

/*************************************************** electromagnet *************************************************************/
void putUp(){
   digitalWrite(9, HIGH);
   digitalWrite(10, LOW);
}

void putDown(){
   digitalWrite(9, LOW);
   digitalWrite(10, LOW);
}

/**************************************************   test    ******************************************************************/
void test(){
    Get_command(0, 0, down);
    Process_command(); 
    delay(500);
    putUp();
  
    Get_command(0, 0, up);
    Process_command();  
    Get_command(25, 0, up);
    Process_command();

    Get_command(25, 0, down);
    Process_command();  
    putDown(); 
    delay(500);
    putDown();
    putUp();

    Get_command(25, 0, up);
    Process_command();   
    Get_command(0, 25, up);
    Process_command();   

    Get_command(0, 25, down);
    Process_command(); 
    putDown();  
    delay(500);
    putDown();
    putUp();

    Get_command(0, 25, up);
    Process_command();   
    Get_command(-25, 0, up);
    Process_command();   

    Get_command(-25, 0, down);
    Process_command();  
    putDown(); 
    delay(500);
    putUp();

    Get_command(-25, 0, up);
    Process_command();   
    Get_command(0, -25, up);
    Process_command();   

    Get_command(0, -25, down);
    Process_command();  
    putDown(); 
    delay(500);
    putUp();

    Get_command(0, -25, up);
    Process_command();   
    Get_command(25, 0, up);
    Process_command();   

    Get_command(25, 0, down);
    Process_command();   
    putDown();
    delay(500);
    putUp();

    Get_command(25, 0, up);
    Process_command();   
    Get_command(0, 0, up);
    Process_command();   

    Get_command(0, 0, down);
    Process_command();   
    delay(500);
    putDown();
}
