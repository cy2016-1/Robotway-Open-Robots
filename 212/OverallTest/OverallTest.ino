/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-31 https://www.robotway.com/
  ---------------------------------------------------------------
  实验功能：
          实现三节履带小车前进、后退、停止、自转、大半径转向、前摆臂向上
          抬起、前摆臂水平、前摆臂向下、后摆臂向上、后摆臂水平、后摆臂向下.
          【注意】：当我们给定圆周舵机一个速度时，例如50，如果我们
          不给该圆周舵机停止（即90），那么该舵机会以50的速度一直转动.
  --------------------------------------------------------------
  实验接线：
                      左轮圆周舵机：D4
                          |  |
                .----------------------.
                |                      |
   -------------|                      |--------------
   后摆臂舵机：D8 |                      | 前摆臂舵机：D7
   -------------|                      |--------------
                |                      |
                *----------------------*
                          |  |
                      右轮圆周舵机：D3
 ------------------------------------------------------------------------------------*/
#include <Servo.h>  //调用舵机库函数
#define Servo_Num 4 //定义舵机数量
Servo Car_Servo[Servo_Num]; //声明舵机对象,表示声明了3个舵机对象
const int servo_pin[Servo_Num] = { 4, 3, 7 ,8 };//定义舵机引脚号.
const int angle_init[Servo_Num] = { 90, 90, 90, 90 };//定义舵机初始化角度
/*枚举类型.当第一个参数为1时，后面的每一个参数一次增1【如：Backward=2,Taillevel=11】Forward(前进)、Backward(后退）、
  TurnInPlace(原地旋转)、BigTurn(大转向)、Stop(小车停止)、Headlevel(前摆臂水平)、Headup(前摆臂向上)、
  Headdown(前摆臂向下)、Taillevel(后摆臂水平)、Tailup(后摆臂向上)、Taildown(后摆臂向下)*/
enum{Forward=1,Backward,TurnInPlace,BigTurn,Stop,Headup,Headdown,Headlevel,Tailup,Taildown,Taillevel};

//程序初始化部分:分别使能舵机对象，并设置各个舵机初始角度
void setup() {
  for( int i=0;i<Servo_Num;i++ ){
    Car_Servo[i].attach( servo_pin[i] ); //使能舵机对象
    Car_Servo[i].write( angle_init[i] ); //设置舵机初始角度
  }//即设定履带小车初始为停止状态
}

//主程序部分：执行小车各个状态
void loop()
{
  Car_State( Headup, 1000 );    //小车前摆臂向上抬起,等待1秒
  Car_State( Forward, 2000 );   //小车前进,等待2秒
  Car_State( Stop, 2000 );      //小车停止,并等待2秒
  Car_State( Headlevel, 1000 ); //小车前摆臂水平
  Car_State( Headdown, 1000 );  //小车前摆臂向下
  Car_State( Backward, 2000 );  //小车后退,等待2秒
  Car_State( Tailup, 1000 );    //后摆臂向上【注意这里没写Stop,故此时的小车会一直以程序前一行的后退状态继续后退】
  Car_State( Taillevel, 1000 ); //后摆臂水平
  Car_State( Taildown, 1000 );  //后摆臂向下
  //........后续可自行添加自己需要的小车状态........
}

/*--------------------------------------------------------------
  该函数封装了小车各个状态.
      参数car_state表示小车执行状态. 参数time_delay表示程序等待时间
  程序使用示例：
      Car_State( Forward, 1000 );表示小车执行前进动作，等待1000毫秒
      Car_State( ArmUp, 1500 );表示小车执行前摆臂向上动作，等待1500毫秒
 */
void Car_State( int car_state, unsigned long time_delay ) {
  switch( car_state ) {
    case Headlevel:   Car_Servo[2].write( 90 );  delay( time_delay); break;
    case Headup:      Car_Servo[2].write( 130 ); delay( time_delay); break;
    case Headdown:    Car_Servo[2].write( 40 );  delay( time_delay); break;
    case Taillevel:   Car_Servo[3].write( 90 );  delay( time_delay); break;
    case Tailup:      Car_Servo[3].write( 130 ); delay( time_delay); break;
    case Taildown:    Car_Servo[3].write( 40 );  delay( time_delay); break;
    case BigTurn:     Car_Servo[0].write( 60 );  Car_Servo[1].write( 104 ); delay( time_delay); break;
    case Backward:    Car_Servo[0].write( 120 ); Car_Servo[1].write( 60 );  delay( time_delay); break;
    case Stop:        Car_Servo[0].write( 90 );  Car_Servo[1].write( 90 );  delay( time_delay); break;
    case Forward:     Car_Servo[0].write( 70 );  Car_Servo[1].write( 110 ); delay( time_delay); break;
    case TurnInPlace: Car_Servo[0].write( 60 );  Car_Servo[1].write( 60 );  delay( time_delay); break;                     
    default: break;  //否则, 程序跳出该循环.
  }
}
