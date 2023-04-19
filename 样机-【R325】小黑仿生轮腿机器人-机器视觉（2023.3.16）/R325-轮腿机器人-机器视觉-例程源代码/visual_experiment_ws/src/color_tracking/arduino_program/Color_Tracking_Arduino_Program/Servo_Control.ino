#include<Servo.h>
Servo myServo[4];
#define f 40

#define servo_num 4
//Servo myServo[4];
int servo_port[4] =   {42, 43, 27, 26};//x,y,z,a
float value_init[4] = {95, 95, 100, 88};//x,y,z,a 



void init_Servo()
{
  for(int i=0;i<servo_num;i++)
  {
    myServo[i].attach(servo_port[i]);delay(50);
    myServo[i].write( value_init[i] );
//    myServo[i].write( map( value_init[i],0,180,500,2500) );
  }delay(1500);
} 

void ServoStart(int which)//使能舵机
{
  if(!myServo[which].attached())myServo[which].attach(servo_port[which]);
  pinMode(servo_port[which], OUTPUT);
}

void ServoStop(int which)//释放舵机
{
  myServo[which].detach();
  digitalWrite(servo_port[which],LOW);
}

void ServoGo(int which , int where)//打开并给舵机写入相关角度
{
  if(where!=200)
  {
    if(where==201) ServoStop(which);
    else
    {
      ServoStart(which);
//      myServo[which].write(map(where,0,180,500,2500));
      myServo[which].write( where );
    }
  }
}

void servo_move(float value0, float value1, float value2, float value3,float t)
//value0, value1, value2, value3这四个参数时要写的舵机角度，float t这个参数是代表舵机运动的时间
{  
  float value_arguments[] = {value0, value1, value2, value3};
  float value_delta[servo_num];  
  for(int i=0;i<servo_num;i++)
  {
    value_delta[i] = (value_arguments[i] - value_init[i]) / f;
  }  
  for(int i=0;i<f;i++)
  {
    for(int k=0;k<servo_num;k++)
    {
      value_init[k] = value_delta[k] == 0 ? value_arguments[k] : value_init[k] + value_delta[k];
    }
    for(int j=0;j<servo_num;j++)
    {
      ServoGo(j,value_init[j]);
    }
    delay(t);
  }
}
