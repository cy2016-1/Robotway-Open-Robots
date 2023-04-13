#include "HBR640.h"
#include <Servo.h>
HBR640 hbr640; //实例化一个语音识别模块
void setup(){
  hbr640.open(); //开始进行语音识别
  servo_pin_4.attach(4);
}

void loop(){
  if(hbr640.isHeard()) //如果监测到识别语句
  {
    int value = hbr640.getSentence(); //获得识别语句的序号
    switch (value) 
   {
    case 0: 
          servo_pin_4.write( 50 );
          break;
    case 1:  
          servo_pin_4.write( 90 );
          break;
     default:
           break;
    }   	
  }
}

void serialEvent()
{
	hbr640.lisen(); //在串口接收事件中调用语音识别的监听指令
}
