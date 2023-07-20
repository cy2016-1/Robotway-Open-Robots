/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-06-15 https://www.robotway.com/
  ------------------------------*/
int sensor[4]= {A0,A2,A4,A3}; //定义数组~传感器接口

/* 宏定义舵机角度，以及延时时间 */
#define SERVO_OUT 70
#define SERVO_IN  120

#define Delay_right 7000
#define Delay_up 7000

#include <Servo.h> 

Servo myservo;


void setup() {
  // put your setup code here, to run once:

  for(int i=0;i<4;i++) //传感器接口设置为输入
    pinMode(sensor[i],INPUT_PULLUP);

/* 电机接口设置为输出*/
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);  
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);  
  Serial.begin(9600);  //串口初始化

  myservo.attach(4);  
  myservo.write(SERVO_IN);  // 3号舵机收回来
  delay(300);
  motorReset(); // 电机初始化，回到复位位置

        
}

void loop() 
{

  myservo.write(SERVO_OUT); // 3号舵机伸出去
  delay(300);
  myservo.write(SERVO_IN);  // 3号舵机收回来
  delay(300);

  X_Motor_right();          // 2 号电机右移 Delay_right时间，然后停止
  delay(Delay_right);
  X_Motor_stop();

  Y_Motor_up();             // 1号电机上移 Delay_up时间，然后停止
  delay(Delay_up);
  Y_Motor_stop();

  myservo.write(SERVO_OUT); // 3号舵机伸出去
  delay(300);
  myservo.write(SERVO_IN);  // 3号舵机收回来
  delay(300);

  motorReset(); // 电机初始化，回到复位位置

  

}

/***************************** MOTOR **************************************/
void X_Motor_left()
{
  digitalWrite(5,LOW);
  digitalWrite(6,HIGH);
}
void X_Motor_right()
{

  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);

}
void X_Motor_stop()
{

  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
}


void Y_Motor_up()
{

  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);

}
void Y_Motor_down()
{

  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);

}
void Y_Motor_stop()
{

  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
}

void motorReset(){

  while(!SensorTrigger(0))  //A0传感器不触发，2号电机左移
  {
      X_Motor_left();
      Serial.print("A0:  ");
      Serial.println(digitalRead(A0));
  }
  X_Motor_stop();        //A0传感器触发，2号电机停止

  while(!SensorTrigger(2))//A4传感器不触发，1号电机向下移动
  {
      Y_Motor_down();
      Serial.print("A4:  ");
      Serial.println(digitalRead(A4));
  }
  Y_Motor_up();//A0传感器触发，2号电机向上300ms，然后停止
  delay(300);
  Y_Motor_stop();

}
/***********************************************************************************/
boolean SensorTrigger( int which )
{ 
  boolean where = false;
  if( !digitalRead( sensor[ which ] ) )
  {
    delay( 100 );
    if( !digitalRead( sensor[ which ] ) ) where = true;
  }    
  return( where );
}
