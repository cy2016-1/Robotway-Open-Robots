/*******************************************************************************************************
实现功能：
          用语音640实现语音风扇的打开和关闭；


实现思路：
          将语音640安装好后，如果接收到命令为“风扇打开”，风扇开始转动；
          如果接收到命令为“风扇关闭”，风扇停止转动；


实验接线：
          风扇的直流电机线接到D9，D10；
          语音640模块接到BigFish扩展板的扩展坞上；
*******************************************************************************************************/

#include "HBR640.h" //语音640需要的函数库
HBR640 hbr640;      //实例化一个语音识别模块
void setup(){
  hbr640.open(); //开始进行语音识别
  pinMode( 9 , OUTPUT);
  pinMode( 10 ,OUTPUT);//将直流电机设置为输出模式；
  delay(1000);
}

void loop(){
  if(hbr640.isHeard()) //如果监测到识别语句
  {
    int value = hbr640.getSentence(); //获得识别语句的序号
    switch (value) 
   {
    case 0x00: FanMode(1); break;//如果接收到命令为“风扇打开”，风扇开始转动；
    case 0x01: FanMode(2); break;//如果接收到命令为“风扇关闭”，风扇停止转动；
    default:  break;
    }     
  }
}

void FanMode(int mode) //风扇模式；
{
  switch(mode)
  {
     case 1: Open(); break;
     case 2: Close(); break;     
  }
}
void Open() //风扇打开
{
   digitalWrite(10,LOW);digitalWrite(9,HIGH);
}

void Close()    //风扇关闭
{
   digitalWrite(10,LOW);digitalWrite(9,LOW);
   
}

 
void serialEvent() //程序会自动调用该程序；
{
    hbr640.lisen(); //在串口接收事件中调用语音识别的监听指令
}
