//#include <SoftwareSerial.h> 
//// Pin10为RX，接HC05的TXD
//// Pin11为TX，接HC05的RXD
//SoftwareSerial BT(10, 11);
//
//char val;
//void setup() {
//  Serial.begin(9600);
//  Serial.println("BT is ready!");
//  BT.begin(9600);
//}
//void loop() {
//  if (Serial.available()) {
//    val = Serial.read();
//    BT.print(val);
//  
//  if (BT.available()) {
//    val = BT.read();
//    Serial.print(val);
//  }
//}

#include<Servo.h>

Servo servo_pin_3;//云台竖直           未调整
Servo servo_pin_4;//云台平
Servo servo_pin_7;//竖
Servo servo_pin_8;//平

void setup()
{
  Serial.begin(9600);
  servo_pin_3.attach(3);
  servo_pin_4.attach(4);
  servo_pin_7.attach(7);
  servo_pin_8.attach(8);
  servo_pin_3.write(90);
  servo_pin_4.write(90);
  servo_pin_7.write(135);
  servo_pin_8.write(90);
}

void loop()
{
    delay(3000);//延时
    servo_pin_4.write(90);
    servo_pin_3.write(90);
    servo_pin_7.write(135);
    servo_pin_8.write(90);
    delay(2000);
    move3();//左右摆动
    move1();//固定
    delay(200000);
}
void move1(){
  servo_pin_3.write(80);
  servo_pin_4.write(80);
  servo_pin_7.write(175);
  servo_pin_8.write(95);//偏右
}

void move3(){
  for(int i=0;i<10;i++)//摄像头左右摆动
  {
    servo_pin_4.write(110);
    servo_pin_3.write(110);
    delay(200);
    servo_pin_4.write(70);
    servo_pin_3.write(70);
    }
}
//void move2(){
//  servo_pin_3.write(80);
//  servo_pin_4.write(90);
//  servo_pin_7.write(180);
//  servo_pin_8.write(80);
//  delay(1000000);
//}
////#include<Servo.h>
////
////Servo servo_pin_3;
////
////#define ECHOPIN 14 
////#define TRIGPIN 15 
////void setup()
////{
////  Serial.begin(9600);
////  pinMode(ECHOPIN, INPUT);
////  pinMode(TRIGPIN, OUTPUT);
////  servo_pin_3.attach(3);
////} 
////
////void loop()
////{
////  float distance;
////  for(int i=0;i<300;i++)
////  {
////    servo_pin_3.write(10);
////    digitalWrite(TRIGPIN, LOW);
////    delay(2);
////    digitalWrite(TRIGPIN, HIGH);
////    delay(10);
////    digitalWrite(TRIGPIN, LOW);
////    distance = pulseIn(ECHOPIN, HIGH);
////    distance= distance/58;
////    Serial.println(distance);
////  }
////  if(distance<=70)
////  {
////    move1();
////    Serial.println("已执行");
////  }
////  else 
////    Serial.println("未检测到");
////}
////void move1()
////{
////        for(int i=0;i<170;i++){
////          servo_pin_3.write( 10+i );
////          delay(5);
////        }
////  delay(15000000);
////}
////
////
//
//
//
////#include<Servo.h>
////Servo servo_pin_3;
////#define hongwai 15 
////void setup()
////{
////  Serial.begin(9600);
////  pinMode(hongwai, INPUT);
////  servo_pin_3.attach(3);
////} 
////void loop()
////{
////  delay(5000);
////  servo_pin_3.write(10);
////
////  if(digitalRead(hongwai)){
////    Serial.println("未检测到");
////     }
////  else 
////    {
////      move1();
////    Serial.println("已执行");
////  } 
////}
////void move1()
////{
////  for(int i=1;i<=160;i++)
////  {
////        servo_pin_3.write( 10+i );
////        delay( 10 );
////  } 
////  delay(5000);
////}
