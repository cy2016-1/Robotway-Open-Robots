/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-9-28 https://www.robotway.com/
  ------------------------------
  实功能： 从串口（蓝牙）接收字符，根据不同字符分别做出前进、后退、原地左转、原地右转、夹爪打开、夹爪闭合的动作。
  -----------------------------------------------------
  实验接线：
机械爪：D3
左轮：D9，D10
右轮：D5，D6。                                     
 ------------------------------------------------------------------------------------*/

#include <Servo.h>

int a = 0 ;
Servo servo_pin_3;

void Open();
void Close();
void Spot_turn_Right();
void Spot_turn_Left();
void Stop();
void Backwards();
void Forward();

void setup()
{
  pinMode( 10, OUTPUT);
  pinMode( 6, OUTPUT);
  pinMode( 5, OUTPUT);
  pinMode( 9, OUTPUT);
  Serial.begin(9600);
  servo_pin_3.attach(3);
}

void loop()
{
  a = Serial.parseInt() ;
  if (( ( a ) > ( 0 ) ))
  {
    if (( ( a ) == ( 1 ) ))
    {
      Forward();
    }
    if (( ( a ) == ( 2 ) ))
    {
      Backwards();
    }
    if (( ( a ) == ( 3 ) ))
    {
      Spot_turn_Left();
    }
    if (( ( a ) == ( 4 ) ))
    {
      Spot_turn_Right();
    }
    if (( ( a ) == ( 5 ) ))
    {
      Stop();
    }
    if (( ( a ) == ( 6 ) ))
    {
      Open();
    }
    if (( ( a ) == ( 7 ) ))
    {
      Close();
    }
  }
}

void Spot_turn_Right()
{
  analogWrite(5 , 255);
  analogWrite(6 , 0);
  analogWrite(9 , 0);
  analogWrite(10 , 255);
}

void Stop()
{
  analogWrite(5 , 255);
  analogWrite(6 , 255);
  analogWrite(9 , 255);
  analogWrite(10 , 255);
}

void Backwards()
{
  analogWrite(5 , 255);
  analogWrite(6 , 0);
  analogWrite(9 , 255);
  analogWrite(10 , 0);
}

void Forward()
{
  analogWrite(5 , 0);
  analogWrite(6 , 255);
  analogWrite(9 , 0);
  analogWrite(10 , 255);
}

void Spot_turn_Left()
{
  analogWrite(5 , 0);
  analogWrite(6 , 255);
  analogWrite(9 , 255);
  analogWrite(10 , 0);
}

void Close()
{
  servo_pin_3.write( 70 );
}

void Open()
{
  servo_pin_3.write( 110 );
}


