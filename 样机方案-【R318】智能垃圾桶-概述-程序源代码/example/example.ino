/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-07-06 https://www.robotway.com/
  ------------------------------*/
/*
实验现象：
        近红外触发后垃圾桶开盖

实验接线：
    
*  近红外接A0，步进电机接扩展板X:
 *  
*/

#define V_MAX 3500  //设置步进电机速度

int sensor0 = A0; //近红外

void setup() {
  Serial.begin(9600);//设置波特率
  pinMode(sensor0, INPUT);
  initMotor(); //初始化步进电机
}

void loop() {
  if(!digitalRead( sensor0 ))
  {
    move(0.9);
    delay(3000);
    move(-0.9);
  }
  else
  {
    delay(10);
  }
}
