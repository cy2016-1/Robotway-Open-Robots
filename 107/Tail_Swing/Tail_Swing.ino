/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-9-8 https://www.robotway.com/
  ------------------------------
  实验功能：实现机器毛毛虫尾部关节运动。
  -----------------------------------------------------
  实验接线：尾部关节模组的舵机接D8。                                     
 ------------------------------------------------------------------------------------*/
#include <Servo.h> 
#include <MsTimer2.h>
int servoPort[5]={8,3,11,7,4}; //毛毛虫的舵机连接顺序及接口号，从尾巴开始。
Servo myServo[5];
long timeCount;
#define DELTATIME 10

void setup() {         
  Serial.begin(9600);       
  for(int i = 0; i < 5; i++)
    myServo[i].attach(servoPort[i]);    
  MsTimer2::set(DELTATIME, Timer); 
  MsTimer2::start();
  delay(100);
}


void loop() {
  ServoMove(0,60,120,2000); //0号舵机在2000ms内从60°转到120°
}

void Timer() {
  timeCount++;
}

void ServoMove(int which, int start, int finish, long t)
{
  static int a;
  static long count = 0;
  static int i = 0;
  static boolean begin = true;

  if(begin){
    if( ( start - finish ) > 0 ) 
      a = -1;
    else 
      a = 1;

    count = timeCount;
    begin = false;
  }
  else{
    if( ( timeCount - count ) < (t/DELTATIME) ){
      if( ( timeCount - count ) > ( i * (t/DELTATIME) / (abs(start-finish)) ) ){
        myServo[which].write( start + i * a );  
        delay(1);
        i++;      
        Serial.println(start + i * a);
      }
    }
    else{
      i = 0;
      begin = true;
      count = 0;
    }   
  }
}
