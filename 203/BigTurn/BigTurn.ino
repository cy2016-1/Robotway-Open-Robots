/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-31 https://www.robotway.com/
  --------------------------------------------------------
  实验功能：
          实现斜三角履带底盘大半径转向（原理为小车车轮同向不同速）
  --------------------------------------------------------
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

void big_Turn();// 大半径转向

//程序初始化部分：设置电机引脚为输出模式
void setup() {
  pinMode( 5 , OUTPUT); //将引脚5设置为输出模式
  pinMode( 6 , OUTPUT); //将引脚6设置为输出模式
  pinMode( 9 , OUTPUT); //将引脚9设置为输出模式
  pinMode( 10 , OUTPUT);//将引脚10设置为输出模式
}

//主程序部分：小车走弧形路径
void loop() {
  big_Turn();
}

//封装小车走大半径(弧线)动作子程序（同向不同速）
void big_Turn() {
  analogWrite( 5 , 0 );  //右轮以255速度前进
  analogWrite( 6 , 255);
  analogWrite( 9 , 0 );  //左轮以150速度前进
  analogWrite( 10 , 150 );
}
