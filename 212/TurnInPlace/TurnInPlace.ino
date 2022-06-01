/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-31 https://www.robotway.com/
  --------------------------------------------------
  实验功能：
          实现三节履带小车原地自转（本示例为原地右转）.
          注意事项：圆周舵机90度表示停止.
  --------------------------------------------------
  实验接线：
                      左轮圆周舵机：D3
                          |  |
                .----------------------.
                |                      |
    ------------|                      |------------
                |                      |     车头 
    ------------|                      |------------
                |                      |
                *----------------------*
                          |  |
                      右轮圆周舵机：D4
 ------------------------------------------------------------------------------------*/
#include <Servo.h>                //调用舵机库函数
#define Servo_Num 2               //定义舵机数量2
#define Left_Servo_Turnright 60   //定义右转时小车左轮速度
#define Right_Servo_Turnright 60  //定义右转时小车右轮速度
Servo Car_Servo[Servo_Num];       //声明舵机对象,表示声明了2个舵机对象

void Turninplace(); //原地自转
const int servo_pin[Servo_Num] = { 4, 3 };//定义舵机引脚号.
const int angle_init[Servo_Num] = { 90, 90 };//定义舵机初始化角度

//程序初始化部分:分别使能舵机对象，并设置各个舵机初始角度
void setup() {
  for( int i=0;i<Servo_Num;i++ ){
    Car_Servo[i].attach( servo_pin[i] ); //使能舵机对象
    Car_Servo[i].write( angle_init[i] ); //设置舵机初始角度
  }//即设定履带小车初始为停止状态
}

//主程序部分：三节履带车原地自转
void loop() {
  Turninplace();
}

//原地自转子程序
void Turninplace() {
  Car_Servo[0].write( Left_Servo_Turnright );
  Car_Servo[1].write( Right_Servo_Turnright );
}
