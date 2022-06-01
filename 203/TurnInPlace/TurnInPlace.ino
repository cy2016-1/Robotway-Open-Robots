/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-31 https://www.robotway.com/
  ------------------------------------
  实验功能：
          实现斜三角履带底盘原地旋转(差速方式）.
          本实验现象为四轮四驱底盘原地左转.
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
void turn_Left(); // 原地转向（本示例为原地左转）

//程序初始化部分：设置电机引脚为输出模式
void setup() {
  pinMode( 5 , OUTPUT); //将引脚5设置为输出模式
  pinMode( 6 , OUTPUT); //将引脚6设置为输出模式
  pinMode( 9 , OUTPUT); //将引脚9设置为输出模式
  pinMode( 10 , OUTPUT);//将引脚10设置为输出模式
}

//主程序部分：小车差速自转[本示例为小车左转]
void loop() {
  turn_Left();
}

//封装小车自转动作子程序（本示例为左转）
void turn_Left(){
  digitalWrite( 5 , LOW );  //右轮前进
  digitalWrite( 6 , HIGH ); 
  
  digitalWrite( 9 , HIGH ); //左轮后退
  digitalWrite( 10 , LOW);
}
