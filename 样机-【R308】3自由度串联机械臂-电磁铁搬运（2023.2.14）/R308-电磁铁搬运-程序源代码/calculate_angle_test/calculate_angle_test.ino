/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-01-31 https://www.robotway.com/
  ------------------------------*/
#include <math.h>
#include <Servo.h>

#define SERVO_SPEED 3460                                        //定义舵机转动快慢的时间
#define ACTION_DELAY 200                                        //定义所有舵机每个状态时间间隔

#define L1 172
#define L2 160
#define L3 135

Servo myServo[6];

int f = 200;                                                    //定义舵机每个状态间转动的次数，以此来确定每个舵机每次转动的角度
int servo_port[6] = {4,7,11,3,8,12};                            //定义舵机引脚
int servo_num = sizeof(servo_port) / sizeof(servo_port[0]);     //定义舵机数量
float value_init[6] = {1500, 1500, 1500, 0, 0, 0};              //定义舵机初始角度

double theta[3] = {};
float value_pwm[6] = {};
float coordinate[3] = {};
int data_num;

boolean dataComplete = false;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  for(int i=0;i<servo_num;i++){
    ServoGo(i,value_init[i]);
  }
  
  get_coordinate(160, 0, 45);
  delay(1000);
}

void loop() {
  get_coordinate(125, 100, 45);
  get_coordinate(125, 100, 20);
  delay(1000);
  put();
  get_coordinate(125, 100, 45);
  get_coordinate(125, 100, 20);
  delay(500);
  get();
  get_coordinate(125, 100, 45);
  
  
  get_coordinate(158, 5, 80);
  get_coordinate(158, 5, 51);
  delay(1000);
  put();
  get_coordinate(158, 5, 80);
  get_coordinate(158, 5, 51);
  delay(500);
  get();
  get_coordinate(110, 0, 158);
  
  get_coordinate(100, -80, 116);
  delay(1000);
  put();
  get_coordinate(100, -80, 140);
  get_coordinate(100, -80, 116);
  delay(500);
  get();
  get_coordinate(100, -80, 140);
  
  get_coordinate(110, 0, 160);
  get_coordinate(158, 5, 51);
  delay(1000);
  put();
  get_coordinate(158, 5, 80);
  get_coordinate(158, 5, 51);
  delay(500);
  get();
  get_coordinate(160, 5, 80);
  delay(200);
}

void get_coordinate(float x, float y, float z){
  coordinate[0] = x;
  coordinate[1] = y;
  coordinate[2] = z;
  
  angle();
}

void angle(){
  calculate_position(coordinate);
  
  for(byte i=0;i<3;i++){  
    value_pwm[i] = map(theta[i], 0, 180, 500, 2500);
  }
  
  servo_move(value_pwm[0], value_pwm[1], value_pwm[2], 0, 0, 0);
  dataComplete = false;

}

void calculate_position(float coordinate[3]){
  float a, b, c, posX, posY, posZ;
  double theta0, theta1, theta2;

  a = L2; 
  b = L3;
  
  posX = coordinate[0] == 0 ? 1 : coordinate[0];
  posY = coordinate[1];
  posZ = coordinate[2];

  theta0 = atan(posX / posY);
  c = sqrt(posX * posX / sq(sin(theta0)) + sq(posZ - L1));

  theta2 = acos((a * a + b * b - c * c) / (2 * a * b));
  theta1 = asin((posZ - L1) / c) + acos((a * a + c * c - b * b) / (2 * a * c));

  if(theta0 >= 0){
    theta[0] = theta0 * 180 / PI;
  }
  else
  {
    theta[0] = 180 + theta0 * 180 / PI;
  }

  theta[1] = 90 - theta1 * 180 / PI;
  theta[2] = theta2 * 180 / PI;
 
//  Serial.print("theta0 = ");
//  Serial.println(theta[0]);
//  Serial.print("theta1 = ");
//  Serial.println(theta[1]);
//  Serial.print("theta2 = ");
//  Serial.println(theta[2]);
//  Serial.println("-------------------------------------");

}

void ServoStart(int which)
{
  if(!myServo[which].attached())myServo[which].attach(servo_port[which]);
  pinMode(servo_port[which], OUTPUT);
}



void ServoStop(int which)
{
  myServo[which].detach();
  digitalWrite(servo_port[which],LOW);
}

void ServoGo(int which , int where)
{
  if(where!=200)
  {
    if(where==201) ServoStop(which);
    else
    {
      ServoStart(which);
      myServo[which].writeMicroseconds(where);
    }
  }
}

void servo_move(float value0, float value1, float value2, float value3, float value4, float value5)
{
  
  float value_arguments[] = {value0, value1, value2, value3, value4, value5};
  float value_delta[servo_num];
  
  for(int i=0;i<servo_num;i++)
  {
    value_delta[i] = (value_arguments[i] - value_init[i]) / f;
  }
  
  for(int i=0;i<f;i++)
  {
    for(int k=0;k<servo_num;k++)
    {
      value_init[k] = value_delta[k] == 0 ? value_arguments[k] : value_init[k] + value_delta[k];
    }
    
    for(int j=0;j<servo_num;j++)
    {
      ServoGo(j,value_init[j]);
    }
    delayMicroseconds(SERVO_SPEED);
  }
  
  
}

void get(){
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  delay(1000);
}

void put(){
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  delay(1000);
}
