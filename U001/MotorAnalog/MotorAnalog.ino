/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-27 https://www.robotway.com/
  ------------------------------------
  实验功能：
          实现模拟量直接驱动直流电机正反转.
  ------------------------------------
  实验接线：
          直流电机引脚接D9,D10
 ------------------------------------------------------------------------------------*/

//程序初始化部分：初始化直流电机引脚.
void setup() {
  pinMode( 10, OUTPUT); //将引脚10设置为输出模式
  pinMode( 9, OUTPUT);  //将引脚9设置为输出模式
}

//主程序部分：实现直流电机持续执行【反转2秒，正转2秒】动作组.
//注意：直流电机模拟量速度范围为：【0~255】
void loop() {
  analogWrite(9 , 0);        //------------------.
  analogWrite(10 , 255);     //电机以255速度反转2秒|
  delay( 2000 );             //------------------*
  
  analogWrite(9 , 150);      //------------------.
  analogWrite(10 , 0);       //电机以150速度正转2秒|
  delay( 2000 );             //------------------*
}
