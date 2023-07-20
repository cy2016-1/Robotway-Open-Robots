/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-07-14 https://www.robotway.com/
  ------------------------------*/
#include <Servo.h>	//调用舵机库

Servo myservo;	//声明一个舵机类

void setup()	//Arduino的设置函数
{
	myservo.attach(4);	//绑定控制舵机的引脚
}

void loop()		//Arduino的循环函数
{
	for(int i=0; i<180; i++){	//通过调节i值控制舵机的运行参数
	    myservo.write(i);	//输出控制舵机的运行参数
	    delay(500);	//延时
	}
}
