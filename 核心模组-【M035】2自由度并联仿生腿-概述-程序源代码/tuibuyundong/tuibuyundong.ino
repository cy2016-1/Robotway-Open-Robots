/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-06-02 https://www.robotway.com/
  ------------------------------*/
#include<Servo.h>
#define upper_servo_initialangle 90
#define lower_servo_initialangle 90
Servo upper_servo;   //大腿舵机
Servo lower_servo;   //小腿舵机

void setup() 
{
  upper_servo.attach(4);
  lower_servo.attach(7);
  upper_servo.write(upper_servo_initialangle);
  lower_servo.write(lower_servo_initialangle);
  delay(1000);
}

void loop() 
{
  //大腿动一下
  for(int i=0;i<30;i++)
  {
    upper_servo.write(upper_servo_initialangle+i);
    delay(100);
  }
  for(int j=30;j>0;j--)
  {
    upper_servo.write(upper_servo_initialangle+j);
    delay(100);
  }
  
  //小腿动一下
  for(int i=0;i<30;i++)
  {
    lower_servo.write(lower_servo_initialangle+i);
    delay(100);
  }
  for(int j=30;j>0;j--)
  {
    lower_servo.write(lower_servo_initialangle+j);
    delay(100);
  }
}
