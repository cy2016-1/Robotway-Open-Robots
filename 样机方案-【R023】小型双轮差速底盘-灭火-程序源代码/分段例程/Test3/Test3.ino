/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-07-14 https://www.robotway.com/
  ------------------------------*/
#define ECHOPIN A3	//使用宏定义对超声波模块连接的引脚进行定义
#define TRIGPIN 2
void setup()
{
  Serial.begin(9600);	//打开串口
  pinMode(ECHOPIN, INPUT);	
  pinMode(TRIGPIN, OUTPUT);	
} 

void loop()
{
  Serial.println(Distance());	//串口打印距离
  delay(500);
}

int Distance()	//超声波距离测量函数，返回测量的距离
{
	digitalWrite(TRIGPIN, LOW);	
  	delayMicroseconds(2);
  	digitalWrite(TRIGPIN, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(TRIGPIN, LOW);
  	int distance = pulseIn(ECHOPIN, HIGH);
  	distance= distance/58;
  	return distance;
}
