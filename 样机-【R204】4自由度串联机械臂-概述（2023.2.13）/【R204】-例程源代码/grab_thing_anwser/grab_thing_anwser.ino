/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-02-02 https://www.robotway.com/
  ------------------------------
  实验功能： 实现4自由度串联机械臂抓取物品、放下的功能
  -----------------------------------------------------
  实验接线：舵机接口依次D8、D3、D11、D7、D4                                     
------------------------------------------------------------------------------------*/
int a=0,b=0,c=0,d=0,e=0,f=0;
#include <Servo.h>
Servo servo_pin_4;
Servo servo_pin_7;
Servo servo_pin_11;
Servo servo_pin_3;
Servo servo_pin_8;
void setup()
{
  servo_pin_4.attach(4);
  servo_pin_4.write( 76);
  servo_pin_7.attach(7);
  servo_pin_7.write( 110);
  servo_pin_11.attach(11);
  servo_pin_11.write(68);
  servo_pin_3.attach(3);
  servo_pin_3.write(157);
  servo_pin_8.attach(8);
  servo_pin_8.write(81);
  delay(3000);//set up the initial posotion.Each servo is different,
              // so u must use Software of Processing to monitor your initial positions of servo.
}
void loop()
{ 
  int a=76;b=110;c=68;d=157;e=81;
  servo_pin_4.write(a);
  servo_pin_7.write(b);
  servo_pin_11.write(c);
  servo_pin_3.write(d);
  servo_pin_8.write(e);
  //Now begin to move,you can use Processing to record a serials of movements.
  //Here's my records.Aiming to grab a thing and put it back.
  for(e=80;e>=50;e-=1)            
  {servo_pin_8.write(e);delay(30);}  
  
  for(d=158;d>=62;d-=3)
  {servo_pin_3.write(d);delay(30);} 
  
  for(b=110;b>=19;b-=3)
  {servo_pin_7.write(b); delay(30);}

  
  for(e=50;e<=80;e+=1)
  {servo_pin_8.write(e);delay(30);}
  
     for(b=19;b<=110;b+=3)
  {servo_pin_7.write(b);delay(30);} 
  delay(3000);

      for(b=110;b>=19;b-=3)
  {servo_pin_7.write(b);delay(30);} 
  
    
  for(e=80;e>=50;e-=1)
  {servo_pin_8.write(e);delay(30);}
  
   for(b=19;b<=110;b+=3)
  {servo_pin_7.write(b);delay(30);} 
  
    for(d=62;d<=158;d+=3)
  {servo_pin_3.write(d);delay(30);} 
  
    for(e=50;e<=81;e+=1)
  {servo_pin_8.write(e);delay(30);}
  
}
