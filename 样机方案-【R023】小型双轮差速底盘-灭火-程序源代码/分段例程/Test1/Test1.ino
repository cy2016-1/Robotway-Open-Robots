/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-07-14 https://www.robotway.com/
  ------------------------------*/
#include <Servo.h>	//调用舵机库函数

#define middle1 105	//定义对应舵机的中间值，即停止转动的值
#define middle2 89	//此值需要测量，各个舵机不一定相同

Servo myservo[2];	//声明舵机类数组，用于控制的两个舵机

void setup()
{
	myservo[0].attach(4);	//绑定舵机的输出引脚
	myservo[1].attach(3);
}

void loop()
{
	Left();	//调用左转函数
	delay(1000);	//延时函数

	Right();
	delay(1000);

	Forwards();
	delay(1000);

	stop();
	delay(1000);
}

void Left()	//左转函数
{
	myservo[0].write(middle1);	//输出相应的舵机参数，使舵机运行
	myservo[1].write(middle2 + 20);
}

void Right()	//右转函数
{
	myservo[0].write(middle1 - 20);
	myservo[1].write(middle2);
}

void Forwards()	//前进函数
{
	myservo[0].write(middle1 - 20);
	myservo[1].write(middle2 + 20);
}

void stop()	//后退函数
{
	myservo[0].write(middle1);
	myservo[1].write(middle2);
}
