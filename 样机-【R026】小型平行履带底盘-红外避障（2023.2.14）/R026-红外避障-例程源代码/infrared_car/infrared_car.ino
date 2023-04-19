/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-02-10 https://www.robotway.com/
  ------------------------------
  实验接线：两个直流电机接口的针脚号分别为D5,D6以及D9,D10;近红外传感器连在A4接口上                                     
------------------------------------------------------------------------------------*/
void setup()
{
  pinMode( 18, INPUT);
  pinMode( 5 , OUTPUT);
  pinMode( 6 , OUTPUT);
  pinMode( 9 , OUTPUT);
  pinMode( 10 , OUTPUT);
}

void loop()
{
  //如果传感器遇到障碍，后退，否则前进
  if (!( digitalRead(18) ))
  {
    digitalWrite( 5 , HIGH );
    digitalWrite( 6 , LOW );
    digitalWrite( 9 , HIGH );
    digitalWrite( 10 , LOW );
  }
  else
  {
    digitalWrite( 5 , LOW );
    digitalWrite( 6 , HIGH );
    digitalWrite( 9 , LOW );
    digitalWrite( 10 , HIGH );
  }
}
