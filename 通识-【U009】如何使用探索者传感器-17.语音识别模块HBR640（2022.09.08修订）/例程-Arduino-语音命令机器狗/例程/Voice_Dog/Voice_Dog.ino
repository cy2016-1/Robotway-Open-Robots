/*******************************************************************************************************
实现功能：
          用语音hbr640和近红外传感器实现小狗识别陌生人；


实现思路：
          将语音模块Hbr640和近红外安装好后，如果近红外触发（说明此时有陌生人靠近小狗），语音模块开始说
          “汪汪汪”；


实验接线：
          近红外模块接到A0；
          语音640模块接到BigFish扩展板的扩展坞上；
*******************************************************************************************************/


#include "HBR640.h" //使用hbr640模块需要的函数库；
HBR640 hbr640;      //实例化一个语音识别模块；
#define Numbers_of_Voece 20 //定义的语音库数量（根据实际情况更改）；
#define Voice_Time 1500 //语音命令延时时间；
#define Near_Infrared_Sensor A0//定义近红外传感器引脚；
#define Left_Speed 65    //小车左侧轮子的速度
#define Right_Speed 95   //小车右侧轮子的速度
#define Motor_num 4      //定义的直流电机引脚数
#define MaxSpeed 255     //定义直流电机最大速度；

unsigned char b = 0xC8;
unsigned char c = 0x00;
unsigned char a[Numbers_of_Voece] = {0x00,
0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09}; //定义的语音库相关词条序号
int Motor_Pin[4] = {5,6,9,10}; //定义直流电机引脚

void setup() {
  // put your setup code here, to run once:
  hbr640.open(); //开始进行语音识别
  for(int i=0;i<Motor_num;i++){
    pinMode(Motor_Pin[i] , OUTPUT);    //将直流电机引脚设置为输出模式
  }
  pinMode(Near_Infrared_Sensor,INPUT); //设置近红外传感器为输入模式；
  delay(2000);
}

void Get_Mode(byte character[] ,unsigned char s,unsigned char d,int Num)
{ //将烧写好的语音命令发送给hbr640模块
  unsigned char _YuYin[3];
  _YuYin[0] =  s; _YuYin[1] = character[0]; _YuYin[2] =d;
  for(int i=0;i<Num;i++){
    Serial.write(_YuYin,3); 
    delay(Voice_Time);
  }
}

void loop() {
  // put your main code here, to run repeatedly: 
  unsigned long t = millis();
  while(millis()-t<1000){
     Motor_Go();
     Dog();
  }
  unsigned long s = millis();
  while(millis()-s<1000){
     Motor_Back();
     Dog();
  }  
}

void Dog()  //检测是否有陌生人靠近
{
  if(ReadSensor(Near_Infrared_Sensor)){ 
     Motor_Stop();
     Get_Mode( a, b , c ,1); //如果近红外传感器触发，语音模块执行相对应的语音；
  }  
}

int ReadSensor(int which)    //读取传感器的监测状态；
{
  int Data = ! digitalRead(Near_Infrared_Sensor);
  return Data;
}

void Motor_Go() //前进
{
   analogWrite(Motor_Pin[0],Right_Speed);
   analogWrite(Motor_Pin[1],0);
   analogWrite(Motor_Pin[2],Left_Speed);
   analogWrite(Motor_Pin[3],0);
}

void Motor_Left() //左转
{
   analogWrite(Motor_Pin[0],Right_Speed);
   analogWrite(Motor_Pin[1],0);
   analogWrite(Motor_Pin[2],0);
   analogWrite(Motor_Pin[3],Left_Speed);  
}

void Motor_Right() //右转
{
   analogWrite(Motor_Pin[0],0);
   analogWrite(Motor_Pin[1],Right_Speed);
   analogWrite(Motor_Pin[2],Left_Speed);
   analogWrite(Motor_Pin[3],0);  
}

void Motor_Back() //后退
{
   analogWrite(Motor_Pin[0],0);
   analogWrite(Motor_Pin[1],Right_Speed);
   analogWrite(Motor_Pin[2],0);
   analogWrite(Motor_Pin[3],Left_Speed);  
}

void Motor_Stop() //停止
{
   analogWrite(Motor_Pin[0],MaxSpeed);
   analogWrite(Motor_Pin[1],MaxSpeed);
   analogWrite(Motor_Pin[2],MaxSpeed);
   analogWrite(Motor_Pin[3],MaxSpeed);  
}
