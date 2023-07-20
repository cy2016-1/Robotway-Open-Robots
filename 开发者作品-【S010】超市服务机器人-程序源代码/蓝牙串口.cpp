#include<Servo.h>
const int x1=16;
const int x2=18;
const int x3=17;
const int x4=14;
const int x5=15;
const int y1=3;//左边第一个轮子插口
const int y2=12;//左边第2个轮子插口
const int y4=4;//右边第一个轮子插口
const int y5=11;//右边第二个轮子插口
const int y7=7;
const int p1=180;
const int p2=90;
const int p3=0;
char q;
Servo a1,a2,a3,a4,a5,a6;
void setup() {
  Serial.begin(9600);
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
void turnright2(){
  a1.write(p3);
  a2.write(p3);
  //a3.write(p3);
  a4.write(p3);
  a5.write(p3);
  //a6.write(p2);
}
void turnleft2(){
  a1.write(p1);
  a2.write(p1);
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
  //a3.write(p1);
  a4.write(p3);
  a5.write(p3);
  //a6.write(p3);
}
void sstop(){
  a1.write(p2);
  a2.write(p2);
  //a3.write(p2);
  a4.write(p2);
  a5.write(p2);
  //a6.write(p2);
}
void loop() {
    while(Serial.available()){
        q=Serial.read();
        if(q=='1') forward();
        if(q=='2') turnleft();
        if(q=='3') turnright();
        if(q=='4') back();
        if(q=='5') sstop();
    }
}