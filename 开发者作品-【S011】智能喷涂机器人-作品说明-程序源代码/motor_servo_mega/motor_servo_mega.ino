/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-06-30 https://www.robotway.com/
  ------------------------------*/
#include<Servo.h>  //调用舵机库函数
#define servo_num 8   //定义舵机数量
#define servo_delay 10 //设置舵机速度
#define motor_pin_count 8 //定义电机引脚数
#define MOTOR_SPEEDS 100  //定义电机速度
#define Motor_ACCELERATION 0.2 //设置电机加速度大小
#define SERIAL_CONNECT Serial2 //蓝牙串口
Servo myservo[8]; //声明舵机对象
float f = 30.0;   //设置舵机速度（参数2）
int servo_pin[servo_num]={27,28,23,24,2,3,4,5}; //定义舵机引脚
float value_init[servo_num]={90,90,75,90,60,90,90,160}; //设置各个舵机初始化角度
const int motor_pin[motor_pin_count] = {6,7,8,9,10,11,12,13}; //定义各个电机引脚
enum{FORWARD=1,BACK,LEFT_TRANSLATION,RIGHT_TRANSLATION,TURN_LEFT,TURN_RIGHT,STOP};//定义小车各个状态

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(9600);
  Serial2.begin(9600);
  motor_pin_init(); // motor pin init
  Servo_reset();  //servo pin init
}
  
void loop() {
  if( SERIAL_CONNECT.available() ){
    char inchar = SERIAL_CONNECT.read();
    if( inchar == '1' ){ Motor_Go( FORWARD ); }     //前进
    else if( inchar == '2' ) { Motor_Go( BACK ); }     //后退
    else if( inchar == '3' ) { Motor_Go( TURN_LEFT ); }   //左转
    else if( inchar == '4' ) { Motor_Go( TURN_RIGHT ); }    //右转
    else if( inchar == '5' ) { Motor_Go( STOP ); }             //停止
    else if( inchar == '6' ) { Motor_Go( LEFT_TRANSLATION ); }  //左平移
    else if( inchar == '7' ) { Motor_Go( RIGHT_TRANSLATION ); } //右平移
    else if( inchar == 'a' ) { servo_move(90,90,75,90,90,90,90,90); }  //底盘向左
    else if( inchar == 'b' ) { servo_move(90,90,75,90,90,90,90,160); } //底盘向右
    else if( inchar == 'c' ) { single_servo_move(2,123);delay(1000);
    for(int i=0;i<3;i++){ single_servo_move(1,75);delay(100); single_servo_move(1,90);delay(100); } } //刷漆动作
    else if( inchar == 'd' ) { single_servo_move(0,30); }  //转头向左
    else if( inchar == 'e' ) { single_servo_move(0,150);}  //转头向右
    else if( inchar == 'f' ) { single_servo_move(0,90); }  //转头复位
    else if( inchar == 'g' ) { single_servo_move(4,55); }  //手臂上抬
    else if( inchar == 'h' ) { single_servo_move(4,75); }  //手臂下降
    else if( inchar == 'i' ) { single_servo_move(4,60);single_servo_move(2,75);delay(1000); }  //手臂复位
    else {delay(2);}
  }
}
