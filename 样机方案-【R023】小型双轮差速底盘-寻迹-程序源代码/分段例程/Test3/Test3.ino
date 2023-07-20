/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-07-14 https://www.robotway.com/
  ------------------------------*/
#include <LedControl.h>	//调用点阵库函数
#include <Servo.h>

LedControl lc=LedControl(12,11,13,1);	//声明点阵类，并设置对应的引脚
int pin[3] = {A0, A4, A3};	//设置传感器的对应的三个引脚
byte value;	//声明传感器值变量

void setup()
{
	LedInit();	//初始化点阵
}

/************************************************************************************
此程序用到了for与switch的配合框架，可用于多传感器的实时处理，请细细体会！
具体解析：for循环中使用了位处理，这样的结果就是value的一个数据位对应一个传感器的状态，
		  此程序value的类型为byte，则可支持8个传感器，如果要使用更多传感器可定义int等。
		  传感器触发时返回值为0，因此value值与传感器触发的状态对应关系以A0触发为例：
		  A0传感器触发-->二进制：00000110-->十六进制：0x06-->对应case 0x06；
		  所以这样做的好处就是当传感器的状态发生改变时程序可以快速的到达指定的处理方式
**************************************************************************************/
void loop()
{
	value = 0;
	for(int i=0; i<3; i++){		//通过循环检测，读取传感器的状态值
	    value |= (digitalRead(pin[i]) << i);	//通过位处理得到结果值，digitalRead()用于读取数字值
	}

	switch (value) {		//根据结果值进行相应的事件处理
		case 0x00:	//全部触发
			LedOn(0);	//点亮相应的点阵
		    LedOn(1);
		    LedOn(2);
			break;
		case 0x01:	//触发右边两个
		    LedOn(1);
		    LedOn(2);
	      	break;
	    case 0x03:	//触发右边一个
	      	LedOn(2);
	      	break;
	    case 0x04:	//触发左边两个
	    	LedOn(0);
		    LedOn(1);
	      	break;
	    case 0x05:	//触发中间一个
	    	LedOn(1);
	      	break;
	    case 0x06:	//触发左边一个
	    	LedOn(0);
	      	break;
	    default:
	      	;
	}
}

void LedOn(int key)		//根据参数点亮相应的点阵LED
{
	lc.clearDisplay(0);
	for(int i=0; i<2; i++){
	    for(int j=3*key; j<3*key+2; j++){
	        lc.setLed(0, i, j, true);
	    }
	}
}

void LedInit() 	//点阵初始化函数
{
	lc.shutdown(0,false);
 	lc.setIntensity(0,8);
	lc.clearDisplay(0); 
}
