/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-31 https://www.robotway.com/
  ---------------------------------------------
  实验功能：
          实现舵机夹爪张开、闭合（缓慢动作）.
          具体现象为：舵机夹爪缓慢张开,再缓慢闭合.
  ---------------------------------------------
  实验接线：
          舵机夹爪模组中的舵机接：D3引脚
 ------------------------------------------------------------------------------------*/
#include<Servo.h>            //调用舵机库
Servo myservo;               //声明舵机对象
#define Servo_Pin 3          //定义舵机引脚号
#define Claw_Open_Angle 135  //设置舵机夹爪张开角度
#define Claw_Close_Angle 45  //设置舵机夹爪闭合角度
#define Servo_Move_Delay 25  //舵机没动一次延时时间（单位：毫秒）

//程序初始化部分：使能舵机引脚
void setup() {
   myservo.attach(Servo_Pin);//设置舵机引脚
   myservo.write(Claw_Close_Angle); //先让舵机夹爪闭合
}

//主程序部分：舵机夹爪缓慢张开，再缓慢闭合
void loop() {
  Servo_Move( Claw_Close_Angle, Claw_Open_Angle ); //舵机夹爪缓慢张开
  Servo_Move( Claw_Open_Angle, Claw_Close_Angle ); //舵机夹爪缓慢闭合
}

/*舵机缓慢运动函数.n计算该舵机从角度A转到角度B花费的总时间为：
  1.计算角度A与角度B的差值的绝对值，例如本示例中的：delta_angle
  2.总时间为： All_Time = delta_angle * Servo_Move_Delay.单位为：毫秒。*/
void Servo_Move(int start_angle, int end_angle){
  int delta_angle = abs(start_angle - end_angle); //计算两角度差的绝对值
  if( delta_angle == 0 ){ delta_angle = 1; } //避免输入角度与输出角度一致
  int servo_flags = 0; //定义舵机标志位
  servo_flags = (start_angle - end_angle)>0 ? -1 : 1;
  for( int i=0;i<delta_angle;i++){
    myservo.write(start_angle + i*servo_flags);
    delay(Servo_Move_Delay);
  }
}
