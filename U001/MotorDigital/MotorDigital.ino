/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-27 https://www.robotway.com/
  -------------------------------------------
  实验功能：
          实现数字量驱动直流电机正反转、停止、刹车.
  -------------------------------------------
  实验接线：
          直流电机引脚接D9,D10
 ------------------------------------------------------------------------------------*/

//程序初始化部分：初始化直流电机引脚.
void setup() {
  pinMode( 10, OUTPUT);  //将引脚10设置为输出模式
  pinMode( 9, OUTPUT);   //将引脚9设置为输出模式
}

//主程序部分：实现直流电机持续执行正转、停止、反转、刹车动作。
void loop() {
  digitalWrite( 9 , HIGH );  //--------------.
  digitalWrite( 10 , LOW );  //直流电机正转2秒 |
  delay( 2000 );             //--------------*

                             //----------------------.
  digitalWrite( 9 , LOW );   //直流电机停止2秒，电机由  |
  digitalWrite( 10 , LOW );  //于惯性，会保持之前的状态 |
  delay( 2000 );             //缓慢滑行一段距离再停止   |
                             //----------------------*
  
  digitalWrite( 9 , LOW );    //--------------.
  digitalWrite( 10 , HIGH );  //直流电机反转2秒 |
  delay( 2000 );              //--------------*

  digitalWrite( 9 , HIGH );   //------------------------.
  digitalWrite( 10 , HIGH );  //直流电机立即停止【刹车效果】|
  delay( 2000 );              //------------------------*
}
