/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-07-14 https://www.robotway.com/
  ------------------------------*/
#include <Servo.h>

#define ECHOPIN A3
#define TRIGPIN 2 
#define middle1 105
#define middle2 89

int pin[3] = {A0, A2, A4};
int value[3];
Servo myservo[2];

void setup()
{
	pinMode(ECHOPIN, INPUT);
  	pinMode(TRIGPIN, OUTPUT);
	myservo[0].attach(4);
	myservo[1].attach(3);
	pinMode(5, OUTPUT);
}

void loop()
{
	for(int i=0; i<3; i++){
	    value[i] = analogRead(pin[i]);	
	}

	int distance = Distance();

	switch (ValueDeal()) {		//根据传感器处理函数的返回值进行相应的处理
		case 0:
			Left();
			break;
	    case 1:
	    	Forward();
	      break;
	    case 2:
	        Right();
	        break;
	    case 3:
	    	if(distance < 10){	//当小车距离障碍10CM时进行避障处理
	    		Back();
	    		delay(1000);
	    	    Left();
	    	    delay(500);
	    	}
	    	else
	    		Forward();
	    	break;
	    default:
	    	Stop();
	}
}

int ValueDeal()
{
	if(value[0] < 900 || value[1] < 900 || value[2] < 900){
	    if(value[0] < value[1]){
	        if(value [0] < value[2]){
	            return 0;
	        }
	        else
	        	return 2;
	    }
	    else
	    {
	    	if(value[1] < value[2]){
	    	    return 1;
	    	}
	    	else
	    		return 2;
	    }
	}
	return 3;
}

int Distance()
{
	digitalWrite(TRIGPIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW);
    int distance = pulseIn(ECHOPIN, HIGH, 14705);
    distance = (int)(distance/58);
    return distance;
}

void Forward()
{
	myservo[0].write(middle1 - 30);
	myservo[1].write(middle2 + 30);
}
void Back()
{
	myservo[0].write(middle1 + 20);
	myservo[1].write(middle2 - 20);
}

void Left()
{
	myservo[0].write(middle1);
	myservo[1].write(middle2 + 30);
}

void Right()
{
	myservo[0].write(middle1 - 30);
	myservo[1].write(middle2);
}

void Stop()
{
	myservo[0].write(middle1);
	myservo[1].write(middle2);
}
