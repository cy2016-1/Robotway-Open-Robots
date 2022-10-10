/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-9-8 https://www.robotway.com/
  ------------------------------
  实验功能：
          实现阿克曼底盘前进3秒，左转前进3秒，右转运动3秒.
  -----------------------------------------------------
  实验接线：
             
               |  |                   |  |
          .-----------------------------------.
          |                                   |
          |                                   |-------.
          | 后轮电机接:D5,D6                            |【车头】|阿克曼机构舵机接:D4
          |                                   |-------*
          |                                   |
          *-----------------------------------*
               |  |                   |  |
                                          
 ------------------------------------------------------------------------------------*/
#include<Servo.h>     //调用舵机库
#define Servo_Pin 4   //定义舵机引脚号
#define Angle_Zero 90  //设置舵机转动的角度为90度
#define Angle_One 120 //设置舵机转动的角度为120度
#define Angle_Two 60 //设置舵机转动的角度为120度

void Forward(); // 前进
void Turnleft();// 左转
void Turnright();// 右转
Servo myservo;  //声明舵机对象

//程序初始化部分：设置电机引脚为输出模式
void setup() {
  Serial.begin(9600);//开启串口，并设置波特率为9600
  myservo.attach(Servo_Pin);//设置舵机引脚
  pinMode( 5 , OUTPUT); //将引脚5设置为输出模式
  pinMode( 6 , OUTPUT); //将引脚6设置为输出模式
}

//主程序部分：阿克曼底盘运动
void loop() {
  Forward();
  delay(3000); //等待3秒
  Turnleft();
  delay(3000); //等待3秒
  Turnright();
  delay(3000); //等待3秒
}

//封装小车前进动作子程序
void Forward() {  
  myservo.write(Angle_Zero); //4号引脚舵机直接转到90度
  digitalWrite( 5 , LOW );  //后轮前进
  digitalWrite( 6 , HIGH );
}

//封装小车左转动作子程序
void Turnleft() {
  myservo.write(Angle_One); //4号引脚舵机直接转到120度
  digitalWrite( 5 , LOW );  //后轮前进
  digitalWrite( 6 , HIGH );
}

//封装小车右转动作子程序
void Turnright() {
  myservo.write(Angle_Two); //4号引脚舵机直接转到60度
  digitalWrite( 5 , LOW );  //后轮前进
  digitalWrite( 6 , HIGH );
}
