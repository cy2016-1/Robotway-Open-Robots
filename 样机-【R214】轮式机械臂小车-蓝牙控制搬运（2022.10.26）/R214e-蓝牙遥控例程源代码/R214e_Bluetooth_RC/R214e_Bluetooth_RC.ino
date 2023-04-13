/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-10-26 https://www.robotway.com/
  ------------------------------
  实现功能： 从串口（蓝牙）接收字符，根据不同字符分别做出前进、原地左转、原地右转、夹爪打开、夹爪闭合、关节抬起、关节放下的动作。
  -----------------------------------------------------
  实验接线：

关节：D12
机械爪：D11
左轮：D5，D9
右轮：D10，D6。                                     
 ------------------------------------------------------------------------------------*/
#include <Servo.h>

int _ABVAR_1_data = 0 ;
Servo servo_pin_11;
Servo servo_pin_12;

void tai();
void zhua();
void stop();
void fang();
void jiang();
void turnright();
void turnleft();
void go();

void setup()
{
  pinMode( 10, OUTPUT);
  pinMode( 6, OUTPUT);
  pinMode( 5, OUTPUT);
  pinMode( 9, OUTPUT);
  Serial.begin(9600);
  servo_pin_11.attach(11);
  servo_pin_12.attach(12);
}

void loop()
{
  _ABVAR_1_data = Serial.parseInt() ;
  if (( ( _ABVAR_1_data ) == ( 1 ) ))
  {
    go();
  }
  if (( ( _ABVAR_1_data ) == ( 3 ) ))
  {
    turnright();
  }
  if (( ( _ABVAR_1_data ) == ( 4 ) ))
  {
    turnleft();
  }
  if (( ( _ABVAR_1_data ) == ( 5 ) ))
  {
    stop();
  }
  if (( ( _ABVAR_1_data ) == ( 6 ) ))
  {
    zhua();
  }
  if (( ( _ABVAR_1_data ) == ( 7 ) ))
  {
    fang();
  }
  if (( ( _ABVAR_1_data ) == ( 8 ) ))
  {
    tai();
  }
  if (( ( _ABVAR_1_data ) == ( 9 ) ))
  {
    jiang();
  }
}

void zhua()
{
  servo_pin_11.write( 63 );
}

void fang()
{
  servo_pin_11.write( 80 );
}

void go()
{
  analogWrite(5 , 80);
  analogWrite(9 , 0);
  analogWrite(6 , 80);
  analogWrite(10 , 0);
}

void jiang()
{
  servo_pin_12.write( 75 );
}

void turnleft()
{
  analogWrite(5 , 0);
  analogWrite(9 , 0);
  analogWrite(6 , 80);
  analogWrite(10 , 0);
}

void turnright()
{
  analogWrite(5 , 80);
  analogWrite(9 , 0);
  analogWrite(6 , 0);
  analogWrite(10 , 0);
}

void tai()
{
  servo_pin_12.write( 30 );
}

void stop()
{
  analogWrite(5 , 255);
  analogWrite(9 , 255);
  analogWrite(6 , 255);
  analogWrite(10 , 255);
}


