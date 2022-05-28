/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-27 https://www.robotway.com/
  -----------------------------------------------------------
  实验功能：
          实现双节履带小车加速前进、加速后退、停止、加速自转、
          加速大半径转向、前摆臂向上抬起、前摆臂水平、前摆臂向下.
          【注意】：当我们给定圆周舵机一个速度时，例如50，如果我们
          不给该圆周舵机停止（即90），那么该舵机会以50的速度一直转动
  -----------------------------------------------------------
  实验接线：
         左轮圆周舵机：D3
             |  |
          .----------------------.
          |                      |
          |                      |----------------
          |                      |  车头舵机接：D7
          |                      |----------------
          |                      |
          *----------------------*
             |  |
         右轮圆周舵机：D4
 ------------------------------------------------------------------------------------*/
#include <Servo.h>  //调用舵机库函数
#define Servo_Num 3 //定义舵机数量
Servo Car_Servo[Servo_Num]; //声明舵机对象,表示声明了3个舵机对象
const int servo_pin[Servo_Num] = { 3, 4, 7 };//定义舵机引脚号.
const int angle_init[Servo_Num] = { 90, 90, 135 };//定义舵机初始化角度

/*枚举类型.当第一个参数为1时，后面的每一个参数一次增1【如：Backward=2,ArmDown=8】
  Forward(前进)、Backward(后退）、TurnInPlace(原地旋转)、BigTurn(大转向)、
  Stop(小车停止)、ArmLevel(前摆臂水平)、ArmUp(前摆臂向上)、ArmDown(前摆臂向下)*/
enum{Forward=1,Backward,TurnInPlace,BigTurn,Stop,ArmLevel,ArmUp,ArmDown};

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
  Car_State( ArmUp, 1000 );    //小车前摆臂向上抬起,等待1秒
  Car_State( Forward, 2000 );  //小车前进,等待2秒
  Car_State( Stop, 2000 );     //小车停止,并等待2秒
  Car_State( ArmLevel, 1000 ); //小车前摆臂水平
  Car_State( ArmDown, 1000 );  //小车前摆臂向下
  Car_State( Backward, 2000 ); //小车后退,等待2秒
  Car_State( ArmUp, 1000 );    //前摆臂向上【注意这里没写Stop,
 //             故此时的小车会一直以程序前一行的后退状态继续后退】
  Car_State( Forward, 5000 );  //以此类推
  Car_State( Backward, 5000 );
  Car_State( TurnInPlace, 5000 );
  Car_State( BigTurn, 5000 );
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
    case ArmLevel:  Car_Servo[2].write( 135 );
                    delay( time_delay);
                    break;
    case ArmUp:     Car_Servo[2].write( 180 );
                    delay( time_delay);
                    break;
    case ArmDown:   Car_Servo[2].write( 90 );
                    delay( time_delay);
                    break;
    case BigTurn:   Car_Servo[0].write( 10 );
                    Car_Servo[1].write( 110 );
                    delay( time_delay); 
                    break;
    case Backward:  Car_Servo[0].write( 170 );
                    Car_Servo[1].write( 10 );
                    delay( time_delay);
                    break;
    case Stop:      Car_Servo[0].write( 90 );
                    Car_Servo[1].write( 90 );
                    delay( time_delay); 
                    break;
    case Forward:   Car_Servo[0].write( 10 );
                    Car_Servo[1].write( 170 );
                    delay( time_delay);
                    break;
    case TurnInPlace: Car_Servo[0].write( 10 );
                      Car_Servo[1].write( 10 );
                      delay( time_delay);
                      break;                     
    default: break;  //否则, 程序跳出该循环.
  }
}
