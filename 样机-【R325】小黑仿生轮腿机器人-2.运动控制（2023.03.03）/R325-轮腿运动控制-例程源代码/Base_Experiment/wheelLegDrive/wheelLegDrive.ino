/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-02-28 https://www.robotway.com/
  ------------------------------*/
/*
 *  功能：轮腿驱动
 *  
 *  车身位置及传感器\电机接线:
 *
 *  Y
 *  |
 *  |                                     
 *  |
 *  |                                        【车身左侧】
 *  |                             t:22                      t:47  
 *  |                             e:24                      e:45
 *  | 舵机[servoPin:26]  t:25   A - - - - - - - - - - - - - - - - - -Y: t:44  舵机[servoPin:43]
 *  |                    e:23   |                                    |  e:46
 *  |【车尾】                            |                                    |           【车头】
 *  |                    t:31   |                                    | t:40
 *  | 舵机[servoPin:27]  e:29   Z - - - - - - - - - - - - - - - - - -X: e:38  舵机[servoPin:42]
 *  |                             t:28                      t:39  
 *  |                             e:30                      e:41
 *  |                                        【车身右侧】
 *  |
 *  0----------------------------------------------------------------------------------------------------------X
 * //////////////////
 */
 
//#include <SoftwareSerial.h>
#include<Servo.h>
//#include<ServoTimer2.h>
#define StepTest 20
#define BaudRate 115200
#define StepTestMultiple 1
#define BriefDelayTimes 10
#define ActionDelayTimes 1500
#define CarActionDelayTime 600
#define mySerial Serial1
#define set_pwm_now 2500
#define set_pwm_nows 1500

bool Ultrasonic_flags[8]={};
long GetUltrasonicDatas[8]={};
double ActualSteps = StepTest*StepTestMultiple;
enum{FORWARD=1,BACK,LEFTROAD,RIGHTROAD,AUTO_MOVE};

float wheel_Speed[4]={0,0,0,0};
float current_vx = 0,current_vy = 0,current_va = 0;
//SoftwareSerial mySerial(51, 9);

void setup() {
  delay(1000);
  mySerial.begin(115200);
  Serial.begin(BaudRate);//set Baud rate
  init_Servo();delay(300);
  init_Ultrasonic();
  XYSetVel(0.0,0.0, 0.0);delay(300);
  moveTest();                                                          
}


void loop() {
   //moveTest();
   //Get_ultrasonic_sensor_data();
}

void control_single_motor(int speed_single,int pwm)
{
  char cmd_return[200];  
  sprintf(cmd_return, "{#%03dP%04dT%04d!}",0,pwm,1);
  mySerial.print(cmd_return);  
}



void moveTest(){
  XYSetVel(0.05, 0.0, 0.0);delay(2000); //forward           前进
  XYSetVel(0.0,0.0, 0.0);delay(2000);//停止
  XYSetVel(-0.05,0.0,0.0);delay(2000);  //back              后退
  XYSetVel(0.0,0.0, 0.0);delay(2000);
  XYSetVel(0.0,0.0,-0.20);delay(2000);  //left              左转
  XYSetVel(0.0,0.0, 0.0);delay(2000);
  XYSetVel(0.0 ,0.0,0.20 );delay(2000);  //right            右转
  XYSetVel(0.0,0.0, 0.0);delay(2000);
  XYSetVel( 0.0, -0.05, 0.0);delay(2000);//Left translation 左平移
  XYSetVel( 0.0, 0.05, 0.0);delay(2000);//right translation 右平移
  XYSetVel(0.0,0.0, 0.0);delay(2000);
}
