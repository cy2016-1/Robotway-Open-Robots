/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-07-14 https://www.robotway.com/
  ------------------------------*/
#include <LedControl.h>
#include <Servo.h>

#define middle1 88
#define middle2 88

LedControl lc=LedControl(12,11,13,1);
Servo myservo[2];
int pin[3] = {A0, A4, A3};
int time[3];
byte value;
byte value_his = 0;
int flag = 0;
int times = 0;

void setup()
{
	LedInit();
	Serial.begin(9600);	//串口，用于调试
	myservo[0].attach(4);
	myservo[1].attach(3);
}

void loop()
{
	value = 0;
	for(int i=0; i<3; i++){
	    value |= (digitalRead(pin[i]) << i);
	    if(!digitalRead(pin[i])){
	        time[i] = millis();
	    }
	}

	if(TimeDeal())
	{
		times++;
		Serial.print(times);
	}
	else
	{
		if(times > 1){
			Serial.println();
		    flag += 1;
		    Serial.println(flag);
		}
		times = 0;
	}

	if(flag == 3){
	    while(1){
	        stop();
	    }
	}

	if(value == 0x07){
	    value = value_his;
	}

	switch (value) {
		case 0x00:	//全部触发
			LedOn(0);
		    LedOn(1);
		    LedOn(2);
		    Forwards();
		    //delay(500);
			break;
		case 0x01:	//触发右边两个
		    LedOn(1);
		    LedOn(2);
		    while(digitalRead(pin[1])){
		        Right();
		    }
	      	break;
	    case 0x03:	//触发右边一个
	      	LedOn(2);
	      	while(digitalRead(pin[1])){
		        Right();
		    }
	      	break;
	    case 0x04:	//触发左边两个
	    	LedOn(0);
		    LedOn(1);
		    while(digitalRead(pin[1])){
		        Left();
		    }
	      	break;
	    case 0x05:	//触发中间一个
	    	LedOn(1);
	    	Forwards();
	      	break;
	    case 0x06:	//触发左边一个
	    	LedOn(0);
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

bool TimeDeal()
{
	if(millis() > 500){
		if((abs(time[1] - time[0]) < 100) && (abs(time[1] - time[2]) < 100)){
	    return true;
	}
		else
			return false;   
		}
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

void LedOn(int key)
{
	for(int i=0; i<2; i++){
	    for(int j=3*key; j<3*key+2; j++){
	        lc.setLed(0, i, j, true);
	    }
	}
}

void LedInit() 
{
	lc.shutdown(0,false); //start the 8*8 led
 	lc.setIntensity(0,8);
	lc.clearDisplay(0); 
}
