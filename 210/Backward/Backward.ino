/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-31 https://www.robotway.com/
  --------------------------
  实验功能：
          实现正三角履带底盘后退.
  ----------------------------------------------------
  实验接线：
          左侧车轮接:D9,D10
               |  |
          .-----------------------------------.
          |                                   |
          |                                   |-------.
          |                                   |【车头】|
          |                                   |-------*
          |                                   |
          *-----------------------------------*
               |  | 
          右侧车轮接:D5,D6             
 ------------------------------------------------------------------------------------*/

void Backward();// 后退

//程序初始化部分：设置电机引脚为输出模式
void setup() {
  pinMode( 5 , OUTPUT); //将引脚5设置为输出模式
  pinMode( 6 , OUTPUT); //将引脚6设置为输出模式
  pinMode( 9 , OUTPUT); //将引脚9设置为输出模式
  pinMode( 10 , OUTPUT);//将引脚10设置为输出模式
}

//主程序部分：小车后退
void loop(){
  Backward();
}

//封装小车后退动作子程序
void Backward() {
  digitalWrite( 5 , HIGH );  //右轮后退
  digitalWrite( 6 , LOW );
  
  digitalWrite( 9 , HIGH );  //左轮后退
  digitalWrite( 10 , LOW);
}
