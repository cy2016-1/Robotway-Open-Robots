#include<Servo.h>
const int x1=17;//x1,x2,x3分别是左中右的灰度传感器
const int x2=16;
const int x3=14;
const int y1=12;//y1,y2为左边第一第二轮子
const int y2=8;
const int y4=11;//y4,y5为右边第一第二轮子
const int y5=7;
const int p1=180;
const int p2=90;
const int p3=0;
Servo a1,a2,a3,a4,a5,a6;
void setup() {
  pinMode(x1,INPUT);
  pinMode(x2,INPUT);
  pinMode(x3,INPUT);
  a1.attach(y1);
  a2.attach(y2);
  //a3.attach(y3);
  a4.attach(y4);
  a5.attach(y5);
  //a6.attach(y6);
}

void turnright(){
  a1.write(p3);
  a2.write(p3);
  //a3.write(p3);
  a4.write(p2);
  a5.write(p2);
  //a6.write(p2);
}
void turnleft(){
  a1.write(p2);
  a2.write(p2);
  //a3.write(p2);
  a4.write(p1);
  a5.write(p1);
  //a6.write(p1);
}
void forward(){
  a1.write(p3);
  a2.write(p3);
  //a3.write(p3);
  a4.write(p1);
  a5.write(p1);
  //a6.write(p1);
}
void back(){
  a1.write(p1);
  a2.write(p1);
 // a3.write(p1);
  a4.write(p3);
  a5.write(p3);
 //a6.write(p3);
}
void loop() {
  int b1=digitalRead(x1);
  int b2=digitalRead(x2);
  int b3=digitalRead(x3);
  if(b1==0&&b2==0&&b3==0){back();}
  if(b1==0&&b2==0&&b3==1){turnright();}
  if(b1==0&&b2==1&&b3==0){forward();}
  if(b1==1&&b2==0&&b3==0){turnleft();}
  if(b1==0&&b2==1&&b3==1){turnright();}
  if(b1==1&&b2==1&&b3==0){turnleft();}
  if(b1==1&&b2==1&&b3==1){forward();}
}