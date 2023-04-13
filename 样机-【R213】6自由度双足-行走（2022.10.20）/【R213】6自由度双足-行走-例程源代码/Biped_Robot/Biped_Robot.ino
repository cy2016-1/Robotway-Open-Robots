/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-10-20 https://www.robotway.com/
  ------------------------------
  实验功能： 6自由度双足行走
  -----------------------------------------------------
  实验接线（从行走时朝前的方向看）：
左侧髋：D4；右侧髋：D3；
左侧膝：D7；右侧膝：D5；
左侧踝：D11；右侧踝：D6
 ------------------------------------------------------------------------------------*/
#include <Servo.h>

int SERVO_SPEED=20;                                          //定义舵机转动快慢的时间
int ACTION_DELAY=200;                                      //定义所有舵机每个状态时间间隔

Servo myServo[6];

int f = 15;                                                     //定义舵机每个状态间转动的次数，以此来确定每个舵机每次转动的角度
int servo_port[6] = {4,7,11,3,8,12};                            //定义舵机引脚
int servo_num = sizeof(servo_port) / sizeof(servo_port[0]);     //定义舵机数量
float value_init[6] = {1657,1074,1412,1455,1807,1342};                //定义舵机初始角度

void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  for(int i=0;i<servo_num;i++){
    ServoGo(i,value_init[i]);
  }
}

void loop() {
  delay(2000);
  while(true){
  servo_move(1657,1074,1412,1455,1807,1342);
  servo_move(1657,1434,1322,1455,2032,1432);
  servo_move(1657,1323,1322,1770,2032,1432);
  servo_move(1657,1323,1322,1770,2257,1319);
  servo_move(1657,1323,1322,2120,2257,1319);
  servo_move(1657,1323,1322,2120,1763,1580);
  servo_move(1815,1351,1390,1559,1449,1626);
  servo_move(1814,1074,1502,1525,1447,1478);
  delay(500);
  servo_move(1814,1074,1502,1525,1447,1478);
  servo_move(1814,650,1791,1435,1524,1478);
  servo_move(1814,650,1637,1435,1591,1478);
  servo_move(1207,650,1255,1435,1591,1478);
  servo_move(1432,1211,1255,1435,1591,1478);
  servo_move(1657,1074,1412,1455,1807,1342);
  delay(500);
  }
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

    /**************************串口查看输出*****************************/
//    Serial.print(value_init[i]);
//    Serial.print(" ");
//    Serial.print(value_arguments[i]);
//    Serial.print(" ");
//    Serial.println(value_delta[i]);
    /**************************串口查看输出*****************************/
  }
  
  for(int i=0;i<f;i++)
  {
    for(int k=0;k<servo_num;k++)
    {
      value_init[k] = value_delta[k] == 0 ? value_arguments[k] : value_init[k] + value_delta[k];

      /**************************串口查看输出*****************************/
//      Serial.print(value_init[k]);
//      Serial.print(" ");
    }
//    Serial.println();
      /**************************串口查看输出*****************************/
    
    for(int j=0;j<servo_num;j++)
    {
      ServoGo(j,value_init[j]);
    }
    delay(SERVO_SPEED);
  }
  delay(ACTION_DELAY);
  
  /**************************串口查看输出*****************************/
//  for(int i=0;i<6;i++)
//  {
//    Serial.println(value_init[i]);
//  }
  /**************************串口查看输出*****************************/
  
}
