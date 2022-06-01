/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-31 https://www.robotway.com/
  ------------------------------------------
  实验功能：
          实现三节履带小车前摆臂下、上、水平动作。
          三节履带车后摆臂下、上、水平动作
  ------------------------------------------
  实验接线：

                .----------------------.
                |                      |
   -------------|                      |--------------
   后摆臂舵机：D8 |                      | 前摆臂舵机：D7
   -------------|                      |--------------
                |                      |
                *----------------------*

 ------------------------------------------------------------------------------------*/
#include <Servo.h>           //调用舵机库
Servo ServoArmHead;          //声明前摆臂舵机对象
Servo ServoArmTail;          //声明后摆臂舵机对象
#define Servo_Head_Pin 7     //定义前摆臂舵机引脚号7
#define Servo_Tail_Pin 8     //定义后摆臂舵机引脚号8
#define Servo_Head_Up 130    //定义前摆臂向上时角度值
#define Servo_Head_Down 40   //定义前摆臂向下时角度值
#define Servo_Head_Level 90  //定义前摆臂保持水平时角度值
#define Servo_Tail_Up 130    //定义后摆臂向上时角度值
#define Servo_Tail_Down 40   //定义后摆臂向下时角度值
#define Servo_Tail_Level 90  //定义前摆臂保持水平时角度值
/*枚举类型.当第一个参数为1时，后面的每一个参数一次增1【如：Headdown=2,Taillevel=7】Headlevel(前摆臂水平)、
  Headup(前摆臂向上)、Headdown(前摆臂向下)Taillevel(后摆臂水平)、Tailup(后摆臂向上)、Taildown(后摆臂向下)*/
enum{Headup=1,Headdown,Headlevel,Tailup,Taildown,Taillevel};

//程序初始化部分:使能舵机对象
void setup() {
  ServoArmHead.attach(Servo_Head_Pin);
  ServoArmTail.attach(Servo_Tail_Pin);
}

//主程序部分：前摆臂、后摆臂分别执行向上、水平、向下动作.
void loop() {
  arm_state( Headup );   delay(1000);  //前摆臂向上,程序等待1秒
  arm_state( Headlevel); delay(1000);  //前摆臂水平,程序等待1秒
  arm_state( Headdown ); delay(1000);  //前摆臂向下,程序等待1秒
  arm_state( Tailup );   delay(1000);  //后摆臂向上,程序等待1秒
  arm_state( Taillevel); delay(1000);  //后摆臂水平,程序等待1秒
  arm_state( Taildown);  delay(1000);  //后摆臂向下,程序等待1秒
}

//前摆臂、后摆臂上、下、水平子函数
void arm_state(int arm_state){
  switch( arm_state )
  {
    case Headup:   ServoArmHead.write( Servo_Head_Up ); break;
    case Headdown :ServoArmHead.write( Servo_Head_Down ); break;
    case Headlevel:ServoArmHead.write( Servo_Head_Level); break;
    case Tailup:   ServoArmTail.write( Servo_Tail_Up ); break;
    case Taildown :ServoArmTail.write( Servo_Tail_Down ); break;
    case Taillevel:ServoArmTail.write( Servo_Tail_Level); break;
    default: break;
  }
}
