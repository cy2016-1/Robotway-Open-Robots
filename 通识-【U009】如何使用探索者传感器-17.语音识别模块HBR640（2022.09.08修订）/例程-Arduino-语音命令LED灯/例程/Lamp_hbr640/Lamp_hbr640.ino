/*******************************************************************************************************
实现功能：
          用语音640实现语音台灯的打开和关闭；


实现思路：
          将语音640安装好后，如果接收到命令为“开灯”，台灯打开；
          如果接收到命令为“关灯”，台灯关闭；


实验接线：
          台灯LED模块的输入线接到Bigfish扩展板的A0，A1；
          语音640模块接到BigFish扩展板的扩展坞上；
*******************************************************************************************************/

#include "HBR640.h" //语音640需要的函数库
HBR640 hbr640;      //实例化一个语音识别模块
void setup(){
  hbr640.open(); //开始进行语音识别
  pinMode( 14 , OUTPUT);
  pinMode( 15 ,OUTPUT);//将A0，A1针脚设置为输出模式；
  delay(1000);
}

void loop(){
  if(hbr640.isHeard()) //如果监测到识别语句
  {
    int value = hbr640.getSentence(); //获得识别语句的序号
    switch (value) 
   {
    case 0x00: LampMode(1); break;//如果接收到命令为“开灯”，台灯打开；
    case 0x01: LampMode(2); break;//如果接收到命令为“关灯”，台灯关闭；
    default:  break;
    }     
  }
}

void LampMode(int mode) //台灯模式；
{
  switch(mode)
  {
     case 1: Open(); break;
     case 2: Close(); break;     
  }
}
void Open() //台灯打开
{
   digitalWrite(14,LOW);digitalWrite(15,HIGH);
}

void Close()    //台灯关闭
{
   digitalWrite(14,LOW);digitalWrite(15,LOW);
   
}

 
void serialEvent() //程序会自动调用该程序；
{
    hbr640.lisen(); //在串口接收事件中调用语音识别的监听指令
}
