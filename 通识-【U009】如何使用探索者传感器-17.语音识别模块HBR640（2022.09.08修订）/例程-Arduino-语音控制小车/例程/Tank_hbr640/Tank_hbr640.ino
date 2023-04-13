/*******************************************************************************************************
实现功能：
          用语音640实现语音坦克小车；


实现思路：
          将语音640安装好后，如果接收到命令为“前进”，小车前进1秒后停止；如果接收到命令为“后退”，小车
          后退1秒后停止；如果接收到命令为“左转”，小车左转1秒后停止；如果接收到命令为“右转”，小车右转
          1秒后停止；如果接收到命令为“停止”，小车停止；否则，没有接收到命令，小车停止；


实验接线：
          小车左轮接到D9，D10；
          小车右轮接到D5，D6；
          语音640模块接到BigFish扩展板的扩展坞上；
*******************************************************************************************************/

#include "HBR640.h" //语音640需要的函数库
#define DelayTime 1000//小车执行相关动作的时间；
HBR640 hbr640;      //实例化一个语音识别模块
void setup(){
  hbr640.open(); //开始进行语音识别
  pinMode( 5 , OUTPUT);
  pinMode( 6 , OUTPUT);
  pinMode( 9 , OUTPUT);
  pinMode( 10 , OUTPUT);//将直流电机设置为输出模式；
}

void loop(){
  if(hbr640.isHeard()) //如果监测到识别语句
  {
    int value = hbr640.getSentence(); //获得识别语句的序号
    switch (value) 
   {
    case 0x00: MotorMode(1,DelayTime); break;//如果接收到命令为“前进”，小车前进1秒后停止；
    case 0x01: MotorMode(2,DelayTime); break;//如果接收到命令为“后退”，小车后退1秒后停止；
    case 0x02: MotorMode(3,DelayTime); break;//如果接收到命令为“左转”，小车左转1秒后停止；
    case 0x03: MotorMode(4,DelayTime); break;//如果接收到命令为“右转”，小车右转1秒后停止；
    case 0x04: MotorMode(5,DelayTime); break;//如果接收到命令为“停止”，小车停止；
    default:  break;
    }     
  }
}

void MotorMode(int mode,int t) //直流电机模式；
{
  switch(mode)
  {
     case 1: Forward(t); break;
     case 2: Back(t); break;     
     case 3: Left(t); break;
     case 4: Right(t); break;    
     case 5: Stop(t); break;    
  }
}
void Forward(int t) //前进
{
   digitalWrite(10,LOW);digitalWrite(9,HIGH);
   digitalWrite(5,HIGH);digitalWrite(6,LOW);
   delay(t); Stop(2);  
}

void Back(int t)    //后退
{
   digitalWrite(10,HIGH);digitalWrite(9,LOW);
   digitalWrite(5,LOW);digitalWrite(6,HIGH);
   delay(t);  Stop(2);
}

void Left(int t)   //左转
{
   digitalWrite(5,HIGH);digitalWrite(6,LOW);
   digitalWrite(9,LOW);digitalWrite(10,HIGH);
   delay(t); Stop(2); 
}

void Right(int t)   //右转
{
   digitalWrite(5,LOW);digitalWrite(6,HIGH);
   digitalWrite(9,HIGH);digitalWrite(10,LOW);
   delay(t); Stop(2);
}

void Stop(int t)   //停止
{
    digitalWrite(5,LOW);digitalWrite(6,LOW);
    digitalWrite(9,LOW);digitalWrite(10,LOW);
    delay(t);  
}
 
void serialEvent() //程序会自动调用该程序；
{
    hbr640.lisen(); //在串口接收事件中调用语音识别的监听指令
}
