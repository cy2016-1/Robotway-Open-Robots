/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-9-28 https://www.robotway.com/
  ------------------------------
  实现功能： 从串口（蓝牙）接收字符，根据不同字符分别做出前进、后退、停止、原地左转、原地右转的动作。
  -----------------------------------------------------
  实验接线：
左轮：D9，D10
右轮：D5，D6。                                     
 ------------------------------------------------------------------------------------*/
int _ABVAR_1_Bluetooth_data = 0 ;

void Left();
void Stop();
void Right();
void Back();
void Forward();

void setup()
{
  Serial.begin(9600);
  pinMode( 5 , OUTPUT);
  pinMode( 6 , OUTPUT);
  pinMode( 9 , OUTPUT);
  pinMode( 10 , OUTPUT);
}

void loop()
{
  _ABVAR_1_Bluetooth_data = Serial.parseInt() ;
  if (( ( _ABVAR_1_Bluetooth_data ) > ( 0 ) ))
  {
    if (( ( _ABVAR_1_Bluetooth_data ) == ( 1 ) ))
    {
      Forward();
    }
    if (( ( _ABVAR_1_Bluetooth_data ) == ( 2 ) ))
    {
      Back();
    }
    if (( ( _ABVAR_1_Bluetooth_data ) == ( 3 ) ))
    {
      Left();
    }
    if (( ( _ABVAR_1_Bluetooth_data ) == ( 4 ) ))
    {
      Right();
    }
    if (( ( _ABVAR_1_Bluetooth_data ) == ( 5 ) ))
    {
      Stop();
    }
  }
}

void Right()
{
  digitalWrite( 5 , HIGH );
  digitalWrite( 6 , LOW );
  digitalWrite( 9 , LOW );
  digitalWrite( 10 , HIGH );
}

void Back()
{
  digitalWrite( 5 , HIGH );
  digitalWrite( 6 , LOW );
  digitalWrite( 9 , HIGH );
  digitalWrite( 10 , LOW );
}

void Left()
{
  digitalWrite( 5 , LOW );
  digitalWrite( 6 , HIGH );
  digitalWrite( 9 , HIGH );
  digitalWrite( 10 , LOW );
}

void Forward()
{
  digitalWrite( 5 , LOW );
  digitalWrite( 6 , HIGH );
  digitalWrite( 9 , LOW );
  digitalWrite( 10 , HIGH );
}

void Stop()
{
  digitalWrite( 5 , HIGH );
  digitalWrite( 6 , HIGH );
  digitalWrite( 9 , HIGH );
  digitalWrite( 10 , HIGH );
}
