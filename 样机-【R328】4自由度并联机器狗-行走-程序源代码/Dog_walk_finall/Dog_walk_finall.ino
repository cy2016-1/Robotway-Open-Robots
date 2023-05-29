/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-05-26 https://www.robotway.com/
  ------------------------------*/
/*
本例程实现机器小狗行走
调试小狗行走的注意事项：
  3、8对应着小狗左侧的上下舵机；
  4、7对应着小狗右侧的上下舵机；
  连接好舵机后，将调试好的小狗初始直立状态写入float value_init[4] =  {   };中即可；
*/


#include<Servo.h>
#define SERVO_SPEED 20                             //定义舵机转动快慢的时间
#define ACTION_DELAY 0                             //定义所有舵机每个状态时间间隔

Servo myServo[4];
int f = 15;//定义舵机每个状态间转动的次数，以此来确定每个舵机每次转动的角度
int servo_port[4] = {3,4,7,8};//定义舵机引脚
int servo_num = sizeof(servo_port) / sizeof(servo_port[0]);//定义舵机数量
float value_init[4] = {1478,1500,1545,1478};//定义舵机初始角度
int leg_range = 180;                        //小狗左右两条腿摆动的幅度
float reset_init[4]={0,0,0,0};

void setup() {
  Serial.begin(9600);
  for(int i=0;i<servo_num;i++)
  ServoGo(i,value_init[i]);
  for(int i=0;i<servo_num;i++){
    reset_init[i] = value_init[i];
  }
  delay(2000);
}

void loop() {
  Dog_walk();
}

void Dog_walk()
{
  servo_move(value_init[0],value_init[1],reset_init[2]+leg_range,reset_init[3]);
  servo_move(value_init[0],value_init[1],reset_init[2],reset_init[3]-leg_range);
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
      myServo[which].write(where);
    }
  }
}

void servo_move(float value0, float value1, float value2, float value3) //舵机转动
{
  
  float value_arguments[] = {value0, value1, value2, value3};
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
    delay(SERVO_SPEED);
  }
  delay(ACTION_DELAY);
}
