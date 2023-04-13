
/*********************************************************************
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-9-28 https://www.robotway.com/
********************** wifi protocol ***********************************
* ff 00 xx 00 ff
Controlled robot motion,xx :00 ~ 04
xx: 00:Stop
    01:Forward
    02:Backword
    03:Left
    04:Right
* ff 02 01 xx ff
  left speed slider, adjust speed, xx : 0 ~ 10

* ff 02 02 xx ff
  right speed slider, operate panel, xx : 0 ~ 10

参考:WIFI机器人网·机器人创意工作室上位机与下位机通信协议(V1.1版)
http://www.wifi-robots.com/thread-7051-1-1.html

*************************** main process ********************************
           __________________________
          |                          \
start - wait mode - infrared start - automode 60s
          \   \                         |
           \ ------------------ wifi mode - wait 10s
            \____________________________________|
*************************** servo motor *********************************

           |          |
            \        /    
              \    /
               ----              引脚     角度
               [  ]      ----->   D3      打开:90  夹取:60
                |
               [  ]      ----->   D4      抬起:90  放下:60
               
注：上述舵机为本套程序使用的，可根据需求修改。
***************************************************************************/

#include <Servo.h>
Servo servoX;
Servo servoY;
bool dataComplete;
bool isPanelOpen;
bool isPanelDown;
int ServoMotorOpenD3 = 90;   //舵机角度
int ServoMotorCloseD3 = 60;
int ServoMotorUpD4 = 90;
int ServoMotorDownD4 = 60;
int moveDirection;    // 1-forward, 2-backward, 3-left, 4-right, 5-stop
int inputData[4];     //data from wifi
int GripperDireciton; // 0 - close, 10 - open
int DownDireciton;    // 0 - Down,  10 - Up
void setup()
{
	Serial.begin(9600);
	servoX.attach(3);
	servoY.attach(4);
        isPanelOpen = false;
        isPanelDown = false;
        GripperDireciton = 10;
        DownDireciton = 10;
}

void loop()
{

  WiFi_Rescue_Robot();
}

void WiFi_Rescue_Robot()
{
  WifiControl();
  Move(moveDirection);
}

void WifiControl()
{
//control by wifi  
    if (dataComplete)   //接收完 WiFi 数据后
    {
          //operate wheel
          if(inputData[0] == 0x00)
          {
              if(inputData[1] != moveDirection){
              moveDirection = inputData[1];
              }
          }
	    //speed slider
            else if(inputData[0] == 0x02){
        
              //adjust speed
              if(inputData[1] == 0x01){
                if(inputData[2] != DownDireciton){
                  DownDireciton = inputData[2];
        
                  if(DownDireciton == 0 && !isPanelDown){
                    servoY.write(ServoMotorDownD4);
                    isPanelDown = true;
                  }
                  else if(DownDireciton == 10 && isPanelDown){
                    servoY.write(ServoMotorUpD4);
                    isPanelDown = false;
                  }
                }
              }
        
              //operate panel
              else if(inputData[1] == 0x02){
                if(inputData[2] != GripperDireciton){
                  GripperDireciton = inputData[2];
        
                  if(GripperDireciton == 0 && !isPanelOpen){
                    servoX.write(ServoMotorCloseD3);
                    isPanelOpen = true;
                  }
                  else if(GripperDireciton == 10 && isPanelOpen){
                    servoX.write(ServoMotorOpenD3);
                    isPanelOpen = false;
                  }
                }
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



void Move(int direction){
  switch (direction) {
    case 0x01:MoveForward();break;
    case 0x02:MoveBackward();break;
    case 0x03:MoveLeft();break;
    case 0x04:MoveRight();break;
    case 0x05:MoveStop();break;
      default:MoveStop();break;
  }
}

void MoveForward(){
  //motor_0 clockwise
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  
  //motor_1 clockwise
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
}

void MoveBackward(){
  //motor_0 clockwise
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  
  //motor_1 clockwise
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
}

void MoveRight(){
  //motor_0 clockwise
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  
  //motor_1 clockwise
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
}

void MoveLeft(){
  //motor_0 clockwise
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  
  //motor_1 clockwise
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);

}

void MoveStop(){
  //motor_0 clockwise
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);

  //motor_1 clockwise
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
}
