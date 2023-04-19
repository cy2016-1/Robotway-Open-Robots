/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-01-30 https://www.robotway.com/
  -----------------------------------------------------------------------------------
/*
  wift car:
  2019/08/19:
  JN
  left: 9, 5;
  right: 10, 6;  
 */

const String FORWARD = "F";
const String BACK = "B";
const String LEFT = "L";
const String RIGHT = "R";
const String STOP = "S";

int speed_left = 41;
int speed_right = 41;

void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  
  
  
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  Stop();
  delay(1000);
}

void loop() {
  String data = SerialRead();
  
  //if(data != ""){    
    if(data == FORWARD)
      Forward();
    else if(data == BACK)
      Back();
    else if(data == LEFT)
      Left();
    else if(data == RIGHT)
      Right();   
    else if(data == STOP)
      Stop();
 // }
}

String SerialRead(){
  String str;
  while(Serial.available()){
    str += char(Serial.read());
  }
  return str;
}

void Forward(){
  analogWrite(9, speed_left);
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(10, speed_right);
}

void Back(){
  analogWrite(9, 0);
  analogWrite(5, speed_left);
  analogWrite(6, speed_right);
  analogWrite(10, 0);
}

void Left(){
  analogWrite(9, 0);
  analogWrite(5, speed_left);
  analogWrite(6, 0);
  analogWrite(10, speed_right);
}

void Right(){
  analogWrite(9, speed_left);
  analogWrite(5, 0);
  analogWrite(6, speed_right);
  analogWrite(10, 0);
}

void Stop(){
  analogWrite(9, speed_left);
  analogWrite(5, speed_left);
  analogWrite(6, speed_right);
  analogWrite(10,speed_right);
}
