
#include "HBR640.h" //使用hbr640模块需要的函数库；
HBR640 hbr640;      //实例化一个语音识别模块；
#define Numbers_of_Voece 20 //定义的语音库数量（根据实际情况更改）；
#define Voice_Time 2700 //语音命令延时时间；
#define Near_Infrared_Sensor A0//定义近红外传感器引脚；

unsigned char b = 0xC8;
unsigned char c = 0x00;
unsigned char a[Numbers_of_Voece] = {0x00,
0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09}; //定义的语音库相关词条序号

void setup() {
  // put your setup code here, to run once:
  hbr640.open(); //开始进行语音识别
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
  if(hbr640.isHeard()) //如果监测到识别语句
  {  
    int value = hbr640.getSentence(); //获得识别语句的序号
    switch (value) 
   {
    case 0: Get_Mode( a+0, b , c ,1); hbr640.open(); break;
    case 1: Get_Mode( a+1, b , c ,1); hbr640.open(); break;
//    case 3: Serial.write(_YUYIN4, 3); hbr640.open(); break;
//    case 4: Serial.write(_YUYIN5, 3); hbr640.open(); break;
//    case 5: Serial.write(_YUYIN6, 3); hbr640.open(); break;
//    case 6: Serial.write(_YUYIN7, 3); hbr640.open(); break;
//    case 7: Serial.write(_YUYIN8, 3); hbr640.open(); break;
//    case 8: Serial.write(_YUYIN9, 3); hbr640.open(); break;
//    case 9: Serial.write(_YUYIN10, 3); hbr640.open(); break;    
//    case 10: Serial.write(_YUYIN11, 3); hbr640.open(); break;
//    case 11: Serial.write(_YUYIN12, 3); hbr640.open(); break;
//    case 12: Serial.write(_YUYIN13, 3); hbr640.open(); break;  
    default:  break;
    }  
  }  
}

int ReadSensor(int which)//读取传感器的监测状态；
{
  int Data = ! digitalRead(Near_Infrared_Sensor);
  if(Data) {
    delay(20); //防止传感器误触发
    if(!digitalRead(Near_Infrared_Sensor))
    return Data;
  }
  else  return Data;
}

void serialEvent()
{
  hbr640.lisen(); //在串口接收事件中调用语音识别的监听指令
}
