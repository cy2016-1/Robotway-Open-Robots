/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-05-31 https://www.robotway.com/
  ------------------------------*/
#define EN        8       //步进电机使能端，低电平有效
#define Y_DIR     6       //y轴 步进电机方向控制
#define Y_STP     3       //y轴 步进控制

//函数：step    功能：控制步进电机方向，步数。
//参数：dir 方向控制, dirPin对应步进电机的DIR引脚，stepperPin 对应步进电机的step引脚， steps 步进的步数

//无返回值
void step(boolean dir, byte dirPin, byte stepperPin, int steps)

{
  digitalWrite(dirPin, dir);

  delay(50);

  for (int i = 0; i < steps; i++) {

    digitalWrite(stepperPin, HIGH);

    delayMicroseconds(800);   //调试步进电机速度函数

    digitalWrite(stepperPin, LOW);

    delayMicroseconds(800);   //调试步进电机速度函数

  }

}

void setup() {
  // put your setup code here, to run once:
   pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);
   pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);

}

void loop() {
  // put your main code here, to run repeatedly: 
   step(false, Y_DIR, Y_STP, 200); //y轴电机 反转1圈，200步为一圈
  delay(1000);
  step(true, Y_DIR, Y_STP, 200); //y轴电机 正转1圈，200步为一圈
  delay(1000);
}
