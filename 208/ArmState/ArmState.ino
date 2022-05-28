/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-26 https://www.robotway.com/
  ------------------------------------------
  实验功能：
          实现双节履带小车前摆臂下、上、正常运动。
  ------------------------------------------
  实验接线：

          .----------------------.
          |                      |
          |                      |--------------
          |                      |  车头舵机接D7
          |                      |--------------
          |                      |
          *----------------------*

 ------------------------------------------------------------------------------------*/
#include <Servo.h>      //调用舵机库
#define Servo_Pin 7     //定义舵机引脚号
#define Servo_Up 180    //定义前摆臂向上时角度值
#define Servo_Down 90   //定义前摆臂向下时角度值
#define Servo_Level 135 //定义前摆臂保持水平时角度值
Servo ServoArm;         //声明舵机对象

void down();            //前摆臂向下
void up();              //前摆臂向上
void normal();          //前摆臂与地面保持平行

//程序初始化部分:使能舵机对象
void setup() {
  ServoArm.attach(Servo_Pin);
}

//主程序部分：前摆臂循环执行【向上1.5秒、水平1秒、向下1.5秒、水平1秒】动作组
void loop() {
  arm_up();     //前摆臂向上
  delay(1500);
  arm_level();  //前摆臂水平
  delay(1000);
  arm_down();   //前摆臂向下
  delay(1500);
  arm_level();  //前摆臂水平
  delay(1000);
}

//前摆臂与地面保持平行
void arm_level(){
  ServoArm.write( Servo_Level );
}

//前摆臂向上
void arm_up(){
  ServoArm.write( Servo_Up );
}

//前摆臂向下
void arm_down(){
  ServoArm.write( Servo_Down );
}
