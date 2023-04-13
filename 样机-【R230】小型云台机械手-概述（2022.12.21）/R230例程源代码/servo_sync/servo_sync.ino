/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-12-21 https://www.robotway.com/
  ----------------------------------
  实验功能：
          实现小型云台机械手云台基本运动，夹爪抓、放基本动作.
  -----------------------------------------------
  实验接线：

              .---.    
              |   |    控制夹爪的舵机接：D4
             .-----.
             |     |   控制云台上下的舵机接：D7
           .---------.
           |         | 控制云台左右转动的舵机接：D11
           |         |
        -----------------
 ------------------------------------------------------------------------------------*/
#include <Servo.h>

int SERVO_SPEED=20;                                          //定义舵机转动快慢的时间
int ACTION_DELAY=200;                                      //定义所有舵机每个状态时间间隔

Servo myServo[6];

int f = 50;                                                     //定义舵机每个状态间转动的次数，以此来确定每个舵机每次转动的角度
int servo_port[6] = {4,7,11,3,8,12};                            //定义舵机引脚
int servo_num = sizeof(servo_port) / sizeof(servo_port[0]);     //定义舵机数量
float value_init[6] = {125, 130, 160, 30, 60, 120};                //定义舵机初始角度

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
  //实现了机械手爪的多角度运动
  servo_move(90, 130, 15, 70, 10, 150);
  servo_move(90, 90, 90, 36, 110, 75);
  servo_move(90, 130, 140, 132, 44, 16);
  servo_move(90, 90, 90, 36, 110, 75);
  while(1){
    f = 20;
    SERVO_SPEED = 20;
    servo_move(120, 90, 90, 70, 10, 150);
    servo_move(90, 90, 90, 70, 10, 150);
  };
  
  /*
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  delay(1000);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  delay(1000);
  servo_move(125, 70, 70, 30, 60, 120);
  delay(500);
  servo_move(98, 70, 70, 30, 60, 120);
  delay(500);
  servo_move(98, 160, 160, 30, 60, 120);
  delay(500);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  delay(1000);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  delay(1000);
  servo_move(125, 160, 160, 30, 60, 120);
  delay(500);
  while(true);
  */
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
