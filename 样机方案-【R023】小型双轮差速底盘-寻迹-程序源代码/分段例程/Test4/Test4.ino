/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-07-14 https://www.robotway.com/
  ------------------------------*/
#include <Servo.h>

#define middle1 88
#define middle2 88

Servo myservo[2];
int pin[3] = {A0, A4, A3};
byte value;
byte value_his = 0;	//记录上一次的传感器值

void setup()
{
	myservo[0].attach(4);
	myservo[1].attach(3);
}

void loop()
{
	value = 0;
	for(int i=0; i<3; i++){
	    value |= (digitalRead(pin[i]) << i);
	}

	if(value == 0x07){	//当传感器都没有触发时默认为上一次的值
	    value = value_his;
	}

	switch (value) {
		case 0x00:	//全部触发
		    Forwards();
			break;
		case 0x01:	//触发右边两个
		    while(digitalRead(pin[1])){		//通过while循环使小车回到跑道中间
		        Right();
		    }
	      	break;
	    case 0x03:	//触发右边一个
	      	while(digitalRead(pin[1])){
		        Right();
		    }
	      	break;
	    case 0x04:	//触发左边两个
		    while(digitalRead(pin[1])){
		        Left();
		    }
	      	break;
	    case 0x05:	//触发中间一个
	    	Forwards();
	      	break;
	    case 0x06:	//触发左边一个
	    	while(digitalRead(pin[1])){
		        Left();
		    }
	      	break;
	    default:
	      	stop();
	}
	value_his = value;
}

void Left()
{
	myservo[0].write(middle1);
	myservo[1].write(middle2 + 20);
}

void Right()
{
	myservo[0].write(middle1 - 20);
	myservo[1].write(middle2);
}

void Forwards()
{
	myservo[0].write(middle1 - 20);
	myservo[1].write(middle2 + 20);
}

void stop()
{
	myservo[0].write(middle1);
	myservo[1].write(middle2);
}
