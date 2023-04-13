/**************** wifi protocol *********************
* ff 02 01 xx ff
left speed slider, adjust speed, xx : 0 ~ 10
* ff 02 02 xx ff
right speed slider, operate panel, xx : 0 ~ 10
* ff 01 07 xx ff
x point of screen, xx :
* ff 01 08 xx ff
y point of screen, xx : 00 ~ 99
* ff 0a 01 xx ff
moveDirection, xx : 1 ~ 5
*************** main process ***********************
__________________________
| \
start - wait mode - infrared start - automode 60s
\ \ |
\ ------------------ wifi mode - wait 10s
\____________________________________|
*/
#include <Servo.h>
Servo servoX;
Servo servoY;
boolean dataComplete;
int inputData[4]; //data from wifi
void setup()
{
	Serial.begin(9600);
	servoX.attach(4);
	servoY.attach(3);
}
void loop()
{
//control by wifi
	if (dataComplete)   //接收完 WiFi 数据后
	{
		if(inputData[0] == 1)
		{
			if(inputData[1] == 7)   //当数据为 17** 的时候 X 轴舵机动
			{
				servoX.write(inputData[2]);
			}
			if(inputData[1] == 8)   //当数据为 18** 的时候 Y 轴舵机动
			{
				servoY.write(inputData[2]);
			}
		}
	}
}
void serialEvent()
{
	static int i;
	static boolean revStart;
	while (Serial.available())
	{
//get data from wifi
		int inData = Serial.read();
		if (inData == 0xff && !revStart)
		{
			revStart = true;
		}
		else if(revStart)
		{
			inputData[i] = inData;
			i++;
			if(i > 3)
			{
				if(inputData[3] == 0xff)
				{
					dataComplete = true;
					i = 0;
					revStart = false;
				}
				else
				{
					i = 0;
					revStart = false;
				}
			}
		}
	}
}
