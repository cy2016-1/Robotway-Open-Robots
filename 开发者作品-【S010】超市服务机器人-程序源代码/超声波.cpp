#include<Servo.h>
const int x1=16;//x1,x2,x3分别是前三个灰度传感器，左中右
const int x2=18;
const int x3=17;
const int x4=18;//超声波输入引脚
const int x5=19;//超声波输出c引脚
const int x6=14;
const int x7=15;
const int y1=3;//y1,y2,y3,y4是六个轮子舵机，12左边，45右边
const int y2=12;
const int y4=4;
const int y5=11;
const int y7=8;
const int y8=7;
const int p1=180;//轮子转速
const int p2=90;
const int p3=0;
const int u=88,c=45;
int rightdistance1,rightdistance2;//超声波距离
int leftdistance1,leftdistance2;
int middledistance1,middledistance2;
Servo a1,a2,a3,a4,a5,a6,a7,a8;//a1-a6车轮，a7是超声波旋转
void setup() {
  Serial.begin(9600);
  pinMode(x1,INPUT);
  //pinMode(x2,INPUT);
  pinMode(x3,INPUT);
  pinMode(x4,INPUT);
  pinMode(x5,OUTPUT);
  pinMode(x6,INPUT);
  pinMode(x7,OUTPUT);
  a1.attach(y1);
  a2.attach(y2);
  //a3.attach(y3);
  a4.attach(y4);
  a5.attach(y5);
  //a6.attach(y6);
  a7.attach(y7);
  a8.attach(y8);

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
void stop(){
  a1.write(p2);
  a2.write(p2);
  //a3.write(p2);
  a4.write(p2);
  a5.write(p2);
  //a6.write(p2);
}
int Distance_test1(){
    digitalWrite(x5,LOW);
    delayMicroseconds(2);
    digitalWrite(x5,HIGH);
    delayMicroseconds(20);
    digitalWrite(x5,LOW);
    float distance=pulseIn(x4,HIGH);
    distance=distance/58;
    return int(distance);
}
int Distance_test2(){
    digitalWrite(x7,LOW);
    delayMicroseconds(2);
    digitalWrite(x7,HIGH);
    delayMicroseconds(20);
    digitalWrite(x7,LOW);
    float distance=pulseIn(x6,HIGH);
    distance=distance/58;
    return int(distance);
}

void chaoshengbo(){
    if (a7.read()!=u){
        a7.write(u);
        delay(300);}
    if (a8.read()!=u){
        a8.write(u);
        delay(300);}
    middledistance1=Distance_test1();
    middledistance2=Distance_test2();
    if(middledistance1<=25 or middledistance2<=25){
        stop();
        delay(500);
        a7.write(u-c);
        a8.write(u+c);
        delay(500);
        rightdistance1=Distance_test1();
        leftdistance1=Distance_test2();
        delay(500);
        a7.write(u);
        a8.write(u);
        delay(1000);
        a7.write(u+c);
        a8.write(u-c);
        delay(500);
        leftdistance2=Distance_test1();
        rightdistance2=Distance_test2();
        delay(500);
        a7.write(u);
        a8.write(u);
        delay(1000);
        if(middledistance2>25 ){
           back();
            delay(500);
            turnright2();
            delay(int(500));
        }
        else if(middledistance1>25){
          back();
            delay(500);
            turnleft2();
            delay(int(500));
        }
        else{
        if (rightdistance2>leftdistance2){
            back();
            delay(500);
            turnright2();
            delay(int(500));
        }
        else if(rightdistance2<leftdistance2){
            back();
            delay(500);
            turnleft2();
            delay(int(500));
        }
        else forward();}
    }
    else forward();

}
void loop() {
  //huiduweiyi();
  chaoshengbo();
}