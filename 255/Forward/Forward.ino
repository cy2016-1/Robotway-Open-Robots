/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-30 https://www.robotway.com/
  -----------------------
  实验功能：
          实现月球小车前进.
  -----------------------------------------------------
  实验接线：
              一拖三直流电机线:左侧车轮接:D9,D10
             |  |         |  |          |  |
          .-----------------------------------.
          |                                   |
          |                                   |-------.
          |                                   |【车头】|
          |                                   |-------*
          |                                   |
          *-----------------------------------*
             |  |         |  |          |  |
              一拖三直流电机线:右侧车轮接:D9,D10             
 ------------------------------------------------------------------------------------*/
void Forward(); // 前进

//程序初始化部分：设置电机引脚为输出模式
void setup() {
  pinMode( 5 , OUTPUT); //将引脚5设置为输出模式
  pinMode( 6 , OUTPUT); //将引脚6设置为输出模式
  pinMode( 9 , OUTPUT); //将引脚9设置为输出模式
  pinMode( 10 , OUTPUT);//将引脚10设置为输出模式
}

//主程序部分：小车前进
void loop() {
  Forward();
}

//封装小车前进动作子程序
void Forward() {
  digitalWrite( 5 , LOW );  //右轮前进
  digitalWrite( 6 , HIGH );
  
  digitalWrite( 9 , LOW );  //左轮前进
  digitalWrite( 10 , HIGH );
}
