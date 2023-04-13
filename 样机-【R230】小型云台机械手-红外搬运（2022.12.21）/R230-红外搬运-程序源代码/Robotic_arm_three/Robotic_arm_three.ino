/*******************************************************************************************

 版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-12-21 https://www.robotway.com/
---------------------------------------------------------------------------------------
实验需求:
         实现机器人搬运货物。

实现思路：
         程序的整体思路为：在机械臂前方安装近红外传感器，如果近红外触发（检测到有货物），机械臂
         开始抓取货物，并将货物从一个区域搬运到另一个指定区域；否则，机械臂不动作。

实验接线:
         最上端的机械爪舵机接D4;
         中间的机械身躯舵机接D7；
         最下端的机械底座舵机接D11；
         近红外传感器接A0。
********************************************************************************************/
#include<ServoTimer2.h>
#define NearInfraredSensor A0   //定义的近红外感器引脚的引脚
#define Upward_servo_close 66   //机械爪闭合的角度值
#define Upward_servo_open 115   //机械爪张开的角度值

#define Middle_servo_init 85    //机械臂的初始角
#define Middle_servo_left 10    //机械臂向左偏的角度
#define Middle_servo_left1 50   //机械臂向左偏的角度

#define Down_servo_middle 75   //机械底座初始角度值
#define Down_servo_left 5      //机械底座向左偏的角度值

ServoTimer2 myservo[3];       //声明舵机数组；

int myservo_pin[3] = { 4, 7, 11 }; //定义三个舵机引脚号；
int myservo_angle_init[3] = { Upward_servo_open, Middle_servo_left, Down_servo_middle };
//定义三个舵机的初始角度值；
int servo_num = sizeof(myservo_pin) / sizeof(myservo_pin[0]); //得出舵机总数


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(NearInfraredSensor,INPUT); //传感器设置为输入模式；
  ResetServo();       //初始化舵机角度
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly: 
  int  Data_of_Sensor = !digitalRead( NearInfraredSensor );
  int  Data = 0;
  if( Data_of_Sensor == 1 ) {   //第1次判断近红外是否触发（是否有货物）
    delay(300);
    if( !digitalRead( NearInfraredSensor ) ) //第2次判断近红外是否触发（是否有货物）
      {
           Grab_And_Release();        //如果检测到有货物，机械臂开始抓取货物；
      }
  }
  else {
    delay(2);    //否则，程序等待；
  }
}



void Grab_And_Release() //如果检测到有货物，机械臂开始抓取货物；
{
  ServoMove(1,Middle_servo_left,Middle_servo_init,1500);     //机械臂向下降（准备抓取货物）  
  ServoMove(0,Upward_servo_open,Upward_servo_close,1500);    //机械爪闭合（抓取货物）
  ServoMove(1,Middle_servo_init,Middle_servo_left1,1500);    //机械臂向上抬
  ServoMove(2,Down_servo_middle,Down_servo_left,1500);       //机械底座转到物料放置区
  ServoMove(1,Middle_servo_left1,Middle_servo_init,1500);    //机械臂向下降（准备释放货物）
  ServoMove(0,Upward_servo_close,Upward_servo_open,1500);    //机械爪张开（释放货物）
  ServoMove(1,Middle_servo_init,Middle_servo_left,1500);     //机械臂回复到初始角度
  ServoMove(2,Down_servo_left,Down_servo_middle,1500);       //机械底座回复到初始角度
}


void ResetServo()     //初始化舵机角度
{
  for(int i=0;i<servo_num;i++)
  {
    myservo[i].attach(myservo_pin[i]);
    myservo[i].write( MapAngle(myservo_angle_init[i]) );
  }
}

int MapAngle(int which)  //映射函数（将0到180映射到500到2500）
{
  return ( map(which,0,180,500,2500) );
}

void ServoGo(int which,int where)   //开始驱动舵机（使舵机转动）；
{
   myservo[which].write(MapAngle(where));
}

void ServoMove(int which,int start,int finish,int t) //舵机转动(舵机从start角度值转到finish角度值需要的时间为t ms)
{
   int a=0;
   if( ( start - finish ) > 0 ) a = -1;
   else a = 1;
   for(int i=0;i<abs(start-finish);i++)
  {
    ServoGo(which,start+a*i);
    delay(t/(abs(start-finish)));
  }
}
