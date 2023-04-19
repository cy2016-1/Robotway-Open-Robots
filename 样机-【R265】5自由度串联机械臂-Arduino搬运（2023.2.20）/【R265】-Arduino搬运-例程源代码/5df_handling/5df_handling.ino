/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-02-20 https://www.robotway.com/
  ------------------------------*/
/*
 本程序要实现一个5自由度串联机械臂搬运物品的功能。
 由机械臂从夹爪到底座的舵机依次连接在Bigfish扩展板的D4、D7、D11、D3、D8、D12接口上。
 */
#define EYEINIT 174
#define HEADINIT 90
#define NECKINIT 124
#define UPBODYINIT 72
#define DOWNBODYINIT 100
#define FOOTINIT 88

#define EYE0 130
#define HEAD0 90
#define NECK0 170
#define UPBODY0 160
#define DOWNBODY0 79
#define FOOT0 36

#define EYE1 130
#define HEAD1 90
#define NECK1 170
#define UPBODY1 160
#define DOWNBODY1 80
#define FOOT1 130

#include<Wire.h>
#include <Servo.h>                                            
#define PIN_SERVO_EYE 4                                        //定义各个舵机所对应的端口;
#define PIN_SERVO_HEAD 7
#define PIN_SERVO_NECK  11
#define PIN_SERVO_UPBODY  3
#define PIN_SERVO_DOWNBODY 8
#define PIN_SERVO_FOOT 12


#define OPERATE_TIME 3000

#define SERVO_EYE 0                                        //定义各个舵机所对应的端口;
#define SERVO_HEAD 1
#define SERVO_NECK  2
#define SERVO_UPBODY  3
#define SERVO_DOWNBODY 4
#define SERVO_FOOT 5

int servoPin[6] = {PIN_SERVO_EYE, PIN_SERVO_HEAD, PIN_SERVO_NECK, PIN_SERVO_UPBODY,PIN_SERVO_DOWNBODY,PIN_SERVO_FOOT};
Servo myServo[6];


void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(9600);
  resetArm();
}

void loop() {
  // put your main code here, to run repeatedly: 

    resetArm(); //机械臂复位
    getCube();  //机械臂开始抓取货物
    putCube();  //机械臂开始释放货物
    delay(2000);//等待2秒
}


void resetArm(){  //舵机复位函数;
    for(int i = 0; i < 6; i++)
        myServo[i].attach(servoPin[i]);
        myServo[SERVO_EYE].write(EYEINIT);
        myServo[SERVO_HEAD].write(HEADINIT);
        myServo[SERVO_NECK].write(NECKINIT);
        myServo[SERVO_UPBODY].write(UPBODYINIT);
        myServo[SERVO_DOWNBODY].write(DOWNBODYINIT);
        myServo[SERVO_FOOT].write(FOOTINIT);
        delay(1500);
}

void getCube(){   //抓取物料动作序列函数;

    ServoMove(SERVO_FOOT, FOOTINIT, FOOT0, OPERATE_TIME);
    ServoMove(SERVO_UPBODY, UPBODYINIT,UPBODY0, OPERATE_TIME);
    ServoMove(SERVO_HEAD, HEADINIT, HEAD0, OPERATE_TIME);
    ServoMove(SERVO_NECK, NECKINIT, NECK0, OPERATE_TIME);
    ServoMove(SERVO_EYE, EYEINIT, EYE0, OPERATE_TIME);
    ServoMove(SERVO_DOWNBODY, DOWNBODYINIT, DOWNBODY0, OPERATE_TIME);
 
    ServoMove(SERVO_HEAD, HEAD0, HEADINIT, OPERATE_TIME);
    ServoMove(SERVO_UPBODY, UPBODY0, UPBODYINIT, OPERATE_TIME);
    ServoMove(SERVO_EYE,  EYE0, EYEINIT, OPERATE_TIME);
    ServoMove(SERVO_NECK, NECK0, NECKINIT, OPERATE_TIME);
    ServoMove(SERVO_DOWNBODY, DOWNBODY0, DOWNBODYINIT, OPERATE_TIME);
}


void putCube()     //机械臂开始释放货物
{
    ServoMove(SERVO_FOOT, FOOT0, FOOT1 , OPERATE_TIME);
    ServoMove(SERVO_HEAD, HEADINIT, HEAD1, OPERATE_TIME);
    ServoMove(SERVO_NECK, NECKINIT, NECK1, OPERATE_TIME);
    ServoMove(SERVO_UPBODY, UPBODYINIT,UPBODY1, OPERATE_TIME);
    ServoMove(SERVO_EYE, EYEINIT, EYE1, OPERATE_TIME);
    ServoMove(SERVO_DOWNBODY, DOWNBODYINIT, DOWNBODY1, OPERATE_TIME);  

    ServoMove(SERVO_HEAD, HEAD1, HEADINIT, OPERATE_TIME);
    ServoMove(SERVO_UPBODY, UPBODY1, UPBODYINIT, OPERATE_TIME);
    ServoMove(SERVO_EYE,  EYE1, EYEINIT, OPERATE_TIME);
    ServoMove(SERVO_NECK, NECK1, NECKINIT, OPERATE_TIME);
    ServoMove(SERVO_DOWNBODY, DOWNBODY1, DOWNBODYINIT, OPERATE_TIME);
    ServoMove(SERVO_FOOT, FOOT1, FOOTINIT , OPERATE_TIME);          
}


void ServoMove(int which, int _start, int _finish, long t)  //舵机动作函数:它有四个参数,舵机号,初始角度,目标角度,动作时间;
{ 
    static int direct;
    static int diff;
    static long deltaTime;
    if(_start <= _finish)
      direct = 1;
    else
      direct = -1;
    diff = abs(_finish - _start);
    deltaTime = (long) (t / 180);
    
    for(int i = 0; i < diff; i++){
        myServo[which].write(_start + i * direct);
        Serial.println(_start + i * direct);
        delay(deltaTime);
    }
}
