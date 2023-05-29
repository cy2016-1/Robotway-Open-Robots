/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-05-26 https://www.robotway.com/
  ------------------------------*/
#include<Servo.h>
#define SERVO_NUMBER	4
const int servo_pin[SERVO_NUMBER] = {4,7,3,8};//定义使用舵机的数组
const int servo_init_ang[SERVO_NUMBER] = {85,82,101,104};//定义小狗站立的初始角度
const int max_h_ang = 28;//小狗蹦跳时四肢的上下幅度
const int max_w_ang = 25;//小狗蹦跳时四肢的前后幅度
int servo_limit_ang[SERVO_NUMBER][2];
Servo myservo[SERVO_NUMBER];
int i=1;
void setup()
{
  Serial.begin(9600);
	servo_limit_ang[0][0] = (servo_init_ang[0]- max_h_ang/2) * (180.0 / 270.0);//将180°舵机的算法转换成270°舵机
	servo_limit_ang[0][1] = (servo_init_ang[0]+ max_h_ang/2) * (180.0 / 270.0);
	servo_limit_ang[1][0] = (servo_init_ang[1]+ max_w_ang/2) * (180.0 / 270.0);
	servo_limit_ang[1][1] = (servo_init_ang[1]- max_w_ang/2) * (180.0 / 270.0);
	servo_limit_ang[2][0] = (servo_init_ang[2]+ max_h_ang/2) * (180.0 / 270.0);
	servo_limit_ang[2][1] = (servo_init_ang[2]- max_h_ang/2) * (180.0 / 270.0);
	servo_limit_ang[3][0] = (servo_init_ang[3]- max_w_ang/2) * (180.0 / 270.0);
	servo_limit_ang[3][1] = (servo_init_ang[3]+ max_w_ang/2) * (180.0 / 270.0);
	resetDog();
	delay(2000);
}

void loop()
{
  bonceF(10000);//行走100秒
}

void resetDog()
{
  //初始化小狗
	for(int i=0;i<SERVO_NUMBER;++i)
	{
		myservo[i].attach(servo_pin[i]);
		myservo[i].write(servo_init_ang[i]);//小狗准备行走时的角度
               
	}
}


void bonceF(int run_number)
{
	float time_rate = 2.0;
	delay(1000);
	for(int i=0;i<run_number;++i)
	{
		for(int j=1;j<=10;++j)
		{
			myservo[0].write(map(servo_limit_ang[0][1]-max_h_ang/10*j,0,180,0,270));
			myservo[2].write(map(servo_limit_ang[2][1]+max_h_ang/10*j,0,180,0,270));	
			delay(max_h_ang/10*5*time_rate);			
		}
		for(int j=1;j<=10;++j)
		{
			myservo[1].write(map(servo_limit_ang[1][0]-max_w_ang/10*j,0,180,0,270));
			myservo[3].write(map(servo_limit_ang[3][0]+max_w_ang/10*j,0,180,0,270));
			delay(max_w_ang/10*5*time_rate);
		}
		for(int k=1;k<=10;++k)
		{
			myservo[0].write(map(servo_limit_ang[0][0]+max_h_ang/10*k,0,180,0,270));
			myservo[2].write(map(servo_limit_ang[2][0]-max_h_ang/10*k,0,180,0,270));
			delay(max_h_ang/10*5*time_rate);
		}
		for(int k=1;k<=10;++k)
		{
			myservo[1].write(map(servo_limit_ang[1][1]+max_w_ang/10*k,0,180,0,270));
			myservo[3].write(map(servo_limit_ang[3][1]-max_w_ang/10*k,0,180,0,270));
			delay(max_w_ang/10*5*time_rate);
		}
	}
}
