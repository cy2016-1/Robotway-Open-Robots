/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-9-8 https://www.robotway.com/
  ------------------------------
  实验功能：
          实现机器螳螂前进的同时点头攻击.
  -----------------------------------------------------
  实验接线：螳螂的左腿接D5，D6；右腿接D9,D10；颈部关节模组的舵机接D4。                                     
 ------------------------------------------------------------------------------------*/
#include<Servo.h>     //调用舵机库
#define Servo_Pin 4   //定义舵机引脚号
#define Angle_Zero 90  //设置舵机转动的角度为90度
#define Angle_One 45 //设置舵机转动的角度为45度

void Mantisup(); // 前进并抬头
void Mantisdown();// 前进并低头
Servo myservo;  //声明舵机对象

//程序初始化部分：设置电机引脚为输出模式
void setup() {
  Serial.begin(9600);//开启串口，并设置波特率为9600
  myservo.attach(Servo_Pin);//设置舵机引脚
  pinMode( 5 , OUTPUT); //将引脚5设置为输出模式
  pinMode( 6 , OUTPUT); //将引脚6设置为输出模式
  pinMode( 9 , OUTPUT); //将引脚9设置为输出模式
  pinMode( 10 , OUTPUT); //将引脚10设置为输出模式
}

//主程序部分：螳螂前进的同时点头攻击
void loop() {
  Mantisup();
  delay(500); //保持0.5秒
  Mantisdown();
  delay(500); //保持0.5秒
}

//封装螳螂前进并抬头动作子程序
void Mantisup() {  
  myservo.write(Angle_Zero); //4号引脚舵机直接转到90度
  digitalWrite( 5 , LOW );  //前进
  digitalWrite( 6 , HIGH );
  digitalWrite( 9 , LOW );  
  digitalWrite( 10 , HIGH );
}

//封装螳螂前进并低头动作子程序
void Mantisdown() {
  myservo.write(Angle_One); //4号引脚舵机直接转到45度
  digitalWrite( 5 , LOW );  //前进
  digitalWrite( 6 , HIGH );
  digitalWrite( 9 , LOW );  
  digitalWrite( 10 , HIGH );
}
