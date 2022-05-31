/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-31 https://www.robotway.com/
  ---------------------------------------------
  实验功能：
          实现舵机夹爪张开、闭合（直接动作）.
          具体现象为：舵机夹爪直接张开,再直接闭合.
  ---------------------------------------------
  实验接线：
          舵机夹爪模组中的舵机接：D3引脚
 ------------------------------------------------------------------------------------*/
#include<Servo.h>            //调用舵机库
#define Servo_Pin 3          //定义舵机引脚号
#define Claw_Open_Angle 120  //设置舵机夹爪张开角度
#define Claw_Close_Angle 60  //设置舵机夹爪闭合角度
Servo myservo;               //声明舵机对象

//程序初始化部分：使能舵机引脚
void setup() {
   myservo.attach(Servo_Pin);       //设置舵机引脚
}

/*主程序部分：依次循环执行：
  舵机夹爪张开-->等待1秒-->舵机夹爪闭合-->等待1秒*/
void loop() {
   myservo.write(Claw_Open_Angle);  //舵机夹爪张开
   delay(1000); //等待1秒
   myservo.write(Claw_Close_Angle); //舵机夹爪闭合
   delay(1000); //等待1秒  
}
