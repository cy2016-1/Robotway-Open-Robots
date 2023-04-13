/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-10-20 https://www.robotway.com/
  ------------------------------
  实验功能： 6自由度双足翻跟头
  -----------------------------------------------------
  实验接线（从行走时朝前的方向看）：
左侧髋：D4；右侧髋：D3；
左侧膝：D7；右侧膝：D8；
左侧踝：D11；右侧踝：D12.
 ------------------------------------------------------------------------------------*/
#include <Servo.h>
Servo myServo[6]; 
int num = 20;
int servo_port[6]={4,7,11,3,8,12};   //定义舵机；
int servo_num = sizeof(servo_port)/sizeof(servo_port[0]);  //servo_pin length
float value_init[6]={86,101,88,82,92,81}; //各个舵机的初始位置     

#define servo_speed 110   //舵机时间；

void setup() {
  Serial.begin(9600);
  reset();                //初始化舵机
  delay(3000);
}

void loop() {
   for(int i=0;i<3;i++)   //让机器人执行三次动作
   {
    delay(1000);
    ketou();             //机器人头着地
    delay(30);
    zuofanzhuan();       //机器人4、7、11舵机所对应的腿翻转
    delay(30);
    youfanzhuan();       //机器人3、8、12舵机所对应的腿翻转
    delay(30);
    qili();              //机器人起立
    delay(300);
   }
  servo_move(86,101,88,82,92,81);  //机器人翻三个跟头后一直保持直立状态
 delay(1/0);            //程序一直执行延时；
}

void qili()              //机器人起立
{
  servo_move(170,22,118,169,168,48);
  servo_move(86,101,88,82,92,81);
}

void youfanzhuan()      //机器人3、8、12舵机所对应的腿翻转
{
  servo_move(7,176,56,169,168,48);
  servo_move(170,22,118,169,168,48);      
}

void zuofanzhuan()      //机器人4、7、11舵机所对应的腿翻转
{
  servo_move(7,176,56,5,8,113); 
  servo_move(7,176,56,169,168,48);  
}

void ketou()             //机器人头着地
{
  servo_move(86,101,88,82,92,81);
  servo_move(7,176,56,5,8,113); 
}

void reset()             //初始化舵机
{
   for(int i=0; i<servo_num; i++)
  {
    ServoGo(i, value_init[i]);
  }
}


void ServoGo(int which , int where)//给舵机写入相应角度
{
  if(where!=200)
  {
    if(where==201) ServoStop(which);
    else
    {
      ServoStart(which);
      myServo[which].write(where);
    }
  }
}

void ServoStart(int which)
{
  if(!myServo[which].attached())myServo[which].attach(servo_port[which]);
  pinMode(servo_port[which], OUTPUT);
}


void ServoStop(int which)  //释放舵机
{
  myServo[which].detach();
  digitalWrite(servo_port[which],LOW);
}


void servo_move(float value0, float value1, float value2, float value3, float value4, float value5)
{
  
  float value_arguments[] = {value0, value1, value2, value3, value4, value5};//定义新数组
  float value_delta[servo_num];
  
  for(int i=0;i<servo_num;i++)
  {
    value_delta[i] = (value_arguments[i] - value_init[i]) / num;//给要转动的舵机写入（转动的角度/num）度，并将该度数定义为新的数组
  }
  
  for(int i=0;i<num;i++)
  {
    for(int k=0;k<servo_num;k++)
    {
      value_init[k] = value_delta[k] == 0 ? value_arguments[k] : value_init[k] + value_delta[k];//将新写入的舵机角度与初始化舵机角度比较，如果
                                                                                                //与初始化角度不相同，则初始化角度+给要转动的舵机写入（转动的角度/num）度
                                                                                                //组成新的数组并作为初始舵机角度数组，否则，为初始舵机角度数组。
    }
    
    for(int j=0;j<servo_num;j++)
    {
      ServoGo(j,value_init[j]);
    }
    delay(servo_speed);
  }
}
