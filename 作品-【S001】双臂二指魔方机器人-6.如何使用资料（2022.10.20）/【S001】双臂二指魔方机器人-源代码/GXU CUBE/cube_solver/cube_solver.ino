#define EN        8       //步进电机使能端，低电平有效
#define STEPS_X 3200  
#define STEPS_Z 3200
int liml=0,limr=0,solve_step=0;
int lj=0,rj=0;
String a= ""; //用 String 声明字符串变量
#include <Servo.h>
#include <math>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include<time.h>
#include<ctime>
Servo servo_pin_8;
Servo servo_pin_3;
void stepperSet();    //步进电机速度设置函数
void stepperMove();   //步进电机步进函数
void stepperMove_x();
void stepperMove_z();
AccelStepper stepper_x(1, 2, 5);    // X
AccelStepper stepper_z(1, 4, 7);    // Z
MultiStepper steppers;
int start=0,end=0;
void setup(){  
    servo_pin_8.attach(8);
    servo_pin_3.attach(3);
    Serial.begin(9600);
    pinMode(EN, OUTPUT);
    digitalWrite(EN, LOW);
    stepperSet(120000,120000);
    L0S();R0S();
}
void L0()
{
  lj=0;
  servo_pin_8.write(75);
  delay(250);
}
void L1()
{
  lj=1;
  servo_pin_8.write(147);
  delay(220);
}
void L0S()
{
  lj=0;
  servo_pin_8.write(75);
  delay(100);
}

void R0()
{
  rj=0;
  servo_pin_3.write(75);
  delay(250);
  solve_step++;
}
void R0S()
{
  rj=0;
  servo_pin_3.write(75);
  delay(100);
}
void R1()
{
  rj=1;
  servo_pin_3.write(153);
  delay(220);
    solve_step++;
}
void Ls()
{
   if(lj==1)
   {
     stepper_z.setMaxSpeed(80000);
     stepperMove_z(-800);
   }
   else if(lj==0 && rj==1)
   {
      stepper_z.setMaxSpeed(60000);
      stepperMove_z(-800);
   }
   else
   {
    stepper_z.setMaxSpeed(70000);
     stepperMove_z(-800);
   }
   liml=liml-90;
   delay(20);
}
void Ln()
{
    if(lj==1)
   {
     stepper_z.setMaxSpeed(80000);
      stepperMove_z(800);
   }
   else if(lj==0 && rj==1)
   {
     stepper_z.setMaxSpeed(60000);
      stepperMove_z(800);
   }
   else
   {
     stepper_z.setMaxSpeed(70000);
      stepperMove_z(800);
   }
   liml=liml+90;
   delay(20);
}
void Rs()
{
    if(lj==1)
   {
     stepper_x.setMaxSpeed(80000);
      stepperMove_x(-800);
   }
   else if(lj==0 && rj==1)
   {
     stepper_x.setMaxSpeed(60000);
     stepperMove_x(-800);
   }
   else
   {
     stepper_x.setMaxSpeed(70000);
      stepperMove_x(-800);
   }
   limr=limr-90;
   delay(20);
}
void Rn()
{
    if(lj==1)
   {
     stepper_x.setMaxSpeed(80000);
      stepperMove_x(800);
   }
   else if(lj==0 && rj==1)
   {
      stepper_x.setMaxSpeed(60000);
      stepperMove_x(800);
   }
   else
   {
     stepper_x.setMaxSpeed(70000);
     stepperMove_x(800);
   }
   limr=limr+90;
   delay(20);
}
void L180()
{
  if(liml<0)
   {
      if(lj==1)
   {
     stepper_z.setMaxSpeed(80000);
      stepperMove_z(1600);
   }
   else if(lj==0 && rj==1)
   {
      stepper_z.setMaxSpeed(60000);
      stepperMove_z(1600);
   }
   else
   {
     stepper_z.setMaxSpeed(70000);
      stepperMove_z(1600);
   }
     liml=liml+180;
   }
   else
   {
     if(lj==1)
   {
     stepper_z.setMaxSpeed(80000);
      stepperMove_z(-1600);
   }
   else if(lj==0 && rj==1)
   {
     stepper_z.setMaxSpeed(60000);
      stepperMove_z(-1600);
   }
   else
   {
     stepper_z.setMaxSpeed(70000);
      stepperMove_z(-1600);
   }
     liml=liml-180;
   }
   delay(20);
}
void R180()
{
   if(limr<0)
   {
      if(lj==1)
   {
     stepper_x.setMaxSpeed(80000);
      stepperMove_x(1600);
   }
   else if(lj==0 && rj==1)
   {
     stepper_x.setMaxSpeed(60000);
      stepperMove_x(1600);
   }
   else
   {
     stepper_x.setMaxSpeed(70000);
      stepperMove_x(1600);
   }
     limr=limr+180;
   }
   else
   {
      if(lj==1)
   {
     stepper_x.setMaxSpeed(80000);
      stepperMove_x(-1600);
   }
   else if(lj==0 && rj==1)
   {
     stepper_x.setMaxSpeed(60000);
      stepperMove_x(-1600);
   }
   else
   {
     stepper_x.setMaxSpeed(70000);
      stepperMove_x(-1600);
   }
     limr=limr-180;
   }
   delay(20);
}
void loop(){
  solve_step=0;
  while (Serial.available() > 0) { //监测串口缓存，当有数据输入时，循环赋值给incomingByte
 a += char(Serial.read());//读取单个字符值，转换为字符，并按顺序一个个赋值给incomingByte
 delay(2);//不能省略，因为读取缓冲区数据需要时间
 }
 if ( a.length() > 0 ) { //如果incomingByte有字符串，执行下面语句
 Serial.println(a);
 start=millis();	
	}
 int l,n,s=1,solve[25]={0};
	l=a.length()-5;
for(int i=0;i<l;i++)
{
  if(a[i]=='1') a[i-1]=a[i-1]-49;
  if(a[i]=='3') a[i-1]=a[i-1]-12;
}
	for(int i=0;i<l;i++)
	{
	    if(a[i]==' ')
	   	{
	     	s++;
	     	solve[s]=0;
		}	
		else 
		{
			n=a[i];
			solve[s]=solve[s]+n;
		}	
	}
	for(int i=1;i<s;i++)
	{
		if(solve[i]==85||solve[i]==124||solve[i]==135) 
{
                 if(abs(liml)%180==90&&abs(limr)%180==0)
                 {
                   R1();L180();R0();L1();
                   if(liml>0) Ls();
                   else Ln();
                   L0();
                 }
                 else
                 {
                  if(abs(liml)%180==0&&abs(limr)%180==90)
                  {
                    R1();
                    if(limr>0) Rs();
                    else Rn();
                    L180();R0();
                  }
                  else
                  {
                      if(abs(liml)%180==0&&abs(limr)%180==0)
                      {
                        R1();L180();R0();
                      }
                  }
                 }
                 if(solve[i]==85)  Rs();
                 if(solve[i]==124)  Rn();
                 if(solve[i]==135) R180();
                 for(int j=i+1;j<s;j++)
{
if(solve[j]==68||solve[j]==107||solve[j]==118) solve[j]=solve[j]+17;
else
{
    if(solve[j]==76||solve[j]==115||solve[j]==126) solve[j]=solve[j]+6;
    else
    {
      if(solve[j]==82||solve[j]==121||solve[j]==132) solve[j]=solve[j]-6;
      else
      {
        if(solve[j]==85||solve[j]==124||solve[j]==135) solve[j]=solve[j]-17;
      }
    }
}
}     
} 
                if(solve[i]==68||solve[i]==107||solve[i]==118) 
                {
                  if(abs(liml)%180==90)
                 {
                  L1();
                   if(liml>0) Ls();
                   else Ln();
                   L0();
                 }
                if(solve[i]==68)   Rs();
                if(solve[i]==107)  Rn();
                if(solve[i]==118)  R180();
                }
                

                 if(solve[i]==70||solve[i]==109||solve[i]==120) 
                 {
                   if(abs(liml)%180==90&&abs(limr)%180==0)
                 {
                   L1();
                   if(liml>0) Ls();
                   else Ln();
                   R180(); L0();
                 }
                 else
                 {
                  if(abs(liml)%180==0&&abs(limr)%180==90)
                  {
                    L1();R180();L0();R1();
                   if(limr>0) Rs();
                   else Rn();
                   R0();
                  }
                  else
                  {
                      if(abs(liml)%180==0&&abs(limr)%180==0)
                      {
                        L1();R180();L0();
                      }
                  }
                 }
                 if(solve[i]==70)   Ls();
                 if(solve[i]==109)  Ln();
                 if(solve[i]==120)  L180();
for(int j=i+1;j<s;j++)
{
if(solve[j]==66||solve[j]==105||solve[j]==116) solve[j]=solve[j]+4;
else
{
    if(solve[j]==76||solve[j]==115||solve[j]==126) solve[j]=solve[j]+6;
    else
    {
      if(solve[j]==82||solve[j]==121||solve[j]==132) solve[j]=solve[j]-6;
      else
      {
        if(solve[j]==70||solve[j]==109||solve[j]==120) solve[j]=solve[j]-4;
      }
    }
}
}
                 }
                if(solve[i]==66||solve[i]==105||solve[i]==116) 
                {
                  if(abs(limr)%180==90)
                 {
                  R1();
                   if(limr>0) Rs();
                   else Rn();
                   R0();
                 }
                if(solve[i]==66)   Ls();
                if(solve[i]==105)  Ln();
                if(solve[i]==116)  L180();
                }
                if(solve[i]==76||solve[i]==115||solve[i]==126)
{
                if(abs(liml)%180==90&&abs(limr)%180==0)
                 {
                   R1();Ls();R0();
                    if(solve[i]==76)   Rs();
                    if(solve[i]==115)  Rn();
                    if(solve[i]==126)  R180();
                    for(int j=i+1;j<s;j++)
{
if(solve[j]==85||solve[j]==124||solve[j]==135) solve[j]=solve[j]-9;
else
{
    if(solve[j]==68||solve[j]==107||solve[j]==118) solve[j]=solve[j]+14;
    else
    {
      if(solve[j]==82||solve[j]==121||solve[j]==132) solve[j]=solve[j]+3;
      else
      {
        if(solve[j]==76||solve[j]==115||solve[j]==126) solve[j]=solve[j]-8;
      }
    }
}
}
                 }
                 else
                 {
                  if(abs(liml)%180==0&&abs(limr)%180==90)
                  {
                    L1();Rn();L0();
                    if(solve[i]==76)   Ls();
                    if(solve[i]==115)  Ln();
                    if(solve[i]==126)  L180();
                    for(int j=i+1;j<s;j++)
{
if(solve[j]==70||solve[j]==109||solve[j]==120) solve[j]=solve[j]+6;
else
{
    if(solve[j]==66||solve[j]==105||solve[j]==116) solve[j]=solve[j]+16;
    else
    {
      if(solve[j]==82||solve[j]==121||solve[j]==132) solve[j]=solve[j]-12;
      else
      {
        if(solve[j]==76||solve[j]==115||solve[j]==126) solve[j]=solve[j]-10;
      }
    }
}
}
                  }
                  else
                  {
                      if(abs(liml)%180==0&&abs(limr)%180==0)
                      {
                       R1();Ls();R0();L1();
                       if(liml>0) Ls();
                       else Ln();
                       L0();
                       if(solve[i]==76)   Rs();
                    if(solve[i]==115)  Rn();
                    if(solve[i]==126)  R180();
                    for(int j=i+1;j<s;j++)
{
if(solve[j]==85||solve[j]==124||solve[j]==135) solve[j]=solve[j]-9;
else
{
    if(solve[j]==68||solve[j]==107||solve[j]==118) solve[j]=solve[j]+14;
    else
    {
      if(solve[j]==82||solve[j]==121||solve[j]==132) solve[j]=solve[j]+3;
      else
      {
        if(solve[j]==76||solve[j]==115||solve[j]==126) solve[j]=solve[j]-8;
      }
    }
}
}
                      }
                  }
                 }
               
} 
                if(solve[i]==82||solve[i]==121||solve[i]==132)
{
                  if(abs(liml)%180==90&&abs(limr)%180==0)
                 {
                   R1();Ln();R0();
                    if(solve[i]==82)   Rs();
                    if(solve[i]==121)  Rn();
                    if(solve[i]==132)  R180();
                    for(int j=i+1;j<s;j++)
{
if(solve[j]==85||solve[j]==124||solve[j]==135) solve[j]=solve[j]-3;
else
{
    if(solve[j]==68||solve[j]==107||solve[j]==118) solve[j]=solve[j]+8;
    else
    {
      if(solve[j]==76||solve[j]==115||solve[j]==126) solve[j]=solve[j]+9;
      else
      {
        if(solve[j]==82||solve[j]==121||solve[j]==132) solve[j]=solve[j]-14;
      }
    }
}
}
                 }
                 else
                 {
                  if(abs(liml)%180==0&&abs(limr)%180==90)
                  {
                    L1();Rs();L0();
                    if(solve[i]==82)   Ls();
                    if(solve[i]==121)  Ln();
                    if(solve[i]==132)  L180();
                    for(int j=i+1;j<s;j++)
{
if(solve[j]==70||solve[j]==109||solve[j]==120) solve[j]=solve[j]+12;
else
{
    if(solve[j]==66||solve[j]==105||solve[j]==116) solve[j]=solve[j]+10;
    else
    {
      if(solve[j]==76||solve[j]==115||solve[j]==126) solve[j]=solve[j]-6;
      else
      {
        if(solve[j]==82||solve[j]==121||solve[j]==132) solve[j]=solve[j]-16;
      }
    }
}
}
                  }
                  else
                  {
                      if(abs(liml)%180==0&&abs(limr)%180==0)
                      {
                        R1();Ln();R0();L1();
                       if(liml>0) Ls();
                       else Ln();
                       L0();
                       if(solve[i]==82)   Rs();
                    if(solve[i]==121)  Rn();
                    if(solve[i]==132)  R180();
                    for(int j=i+1;j<s;j++)
{
if(solve[j]==85||solve[j]==124||solve[j]==135) solve[j]=solve[j]-3;
else
{
    if(solve[j]==68||solve[j]==107||solve[j]==118) solve[j]=solve[j]+8;
    else
    {
      if(solve[j]==76||solve[j]==115||solve[j]==126) solve[j]=solve[j]+9;
      else
      {
        if(solve[j]==82||solve[j]==121||solve[j]==132) solve[j]=solve[j]-14;
      }
    }
}
}
                      }
                  }
                 }
} 

 }
 /*Serial.println(solve_step);*/
 liml=0,limr=0;
 if ( a.length() > 0 ) { //如果incomingByte有字符串，执行下面语句
 end=millis();
 double endtime=(double)(end-start);
  Serial.print("Total time:");
  Serial.print(endtime);
  Serial.println("ms");
	}
 a= ""; //清空变量，准备下次输入
}
void stepperSet(long v_x,long v_z){
  stepper_x.setMaxSpeed(v_x);          
  stepper_x.setAcceleration(2000000.0);  
  stepper_z.setMaxSpeed(v_z);
  stepper_z.setAcceleration(2000000.0);

  steppers.addStepper(stepper_x);
  steppers.addStepper(stepper_z);
}

void stepperMove(long _x,long _z){
    long positions[2];
    positions[0] = _x;
    positions[1] = _z;
    steppers.moveTo(positions);
    steppers.runSpeedToPosition();
    stepper_x.setCurrentPosition(0);
    stepper_z.setCurrentPosition(0);
}
void stepperMove_x(long _x)
{
  stepper_x.moveTo(_x);
  stepper_x.runToPosition();
  stepper_x.setCurrentPosition(0);
}
void stepperMove_z(long _z)
{
  stepper_z.moveTo(_z);
  stepper_z.runToPosition();
  stepper_z.setCurrentPosition(0);
}
