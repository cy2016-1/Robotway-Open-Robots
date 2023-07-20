/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-07-14 https://www.robotway.com/
  ------------------------------*/
void setup()
{
	pinMode(5, OUTPUT);		//设置引脚5的功能为输出
}

void loop()
{
	WindStart();	
	delay(1000);

	WindStop();
	delay(1000);
}

void WindStart()	//风扇旋转函数
{
	digitalWrite(5, HIGH);	//置高引脚5的输出电平
}

void WindStop()		//风扇旋转停止函数
{
	digitalWrite(5, LOW);	//置低引脚5的输出电平
}
