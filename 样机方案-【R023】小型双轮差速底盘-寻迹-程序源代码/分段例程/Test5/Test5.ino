/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-07-14 https://www.robotway.com/
  ------------------------------*/
#include <Servo.h>
#include <LedControl.h>

#define middle1 88
#define middle2 88

Servo myservo[2];
LedControl lc=LedControl(12,11,13,1);

int pin[3] = {A0, A4, A3};
byte value;
byte value_his = 0;
int time[3];	//用于记录传感器的触发时间

void setup()
{
	LedInit();
	myservo[0].attach(4);
	myservo[1].attach(3);
}

void loop()
{
	value = 0;
	for(int i=0; i<3; i++){
	    value |= (digitalRead(pin[i]) << i);
	    if(!digitalRead(pin[i])){
	        time[i] = millis();	//调用mills函数可以得到此时单片机的运行时间
	    }
	}

	if(TimeDeal())
	{
		if(millis() > 1000){	//用于排除刚开机时的误判
		    LedDis();		//十字路口显示
		}
	}

	if(value == 0x07){	//当传感器都没有触发时默认为上一次的值
	    value = value_his;
	}

	switch (value) {
		case 0x00:	//全部触发
		    Forwards();
			break;
		case 0x01:	//触发右边两个
		    while(digitalRead(pin[1])){
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
	lc.clearDisplay(0);
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

bool TimeDeal()	//十字路口识别函数
{
	if(millis() > 500){
		if((abs(time[1] - time[0]) < 100) && (abs(time[1] - time[2]) < 100)){	//当中间传感器与另外两个传感器触发的时间小于100毫秒时判定为十字路口
	    return true;
	}
	else
		return false;   
	}
}

void LedDis()	//十字路口显示函数
{
	for(int i=3; i<5; i++){
	    for(int j=0; j<8; j++){
	        lc.setLed(0, i, j, true);
	    }
	}
	for(int i=3; i<5; i++){
	    for(int j=0; j<8; j++){
	        lc.setLed(0, j, i, true);
	    }
	}
}

void LedInit() 
{
	lc.shutdown(0,false); //start the 8*8 led
 	lc.setIntensity(0,8);
	lc.clearDisplay(0); 
}
