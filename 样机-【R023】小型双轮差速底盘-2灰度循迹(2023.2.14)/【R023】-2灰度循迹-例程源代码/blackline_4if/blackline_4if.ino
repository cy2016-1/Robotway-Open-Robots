/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-02-09 https://www.robotway.com/                                    
------------------------------------------------------------------------------------*/
void turnleft_slow();
void forward();
void carstop();
void turnright_slow();

void setup()
{
  pinMode( 18, INPUT);
  pinMode( 14, INPUT);
  pinMode( 10, OUTPUT);
  pinMode( 6, OUTPUT);
  pinMode( 5, OUTPUT);
  pinMode( 9, OUTPUT);
}

void loop()
{
  if (( digitalRead(14) && digitalRead(18) ))
  {
    forward();
  }
  if (( !( digitalRead(14) ) && digitalRead(18) ))
  {
    turnleft_slow();
  }
  if (( digitalRead(14) && !( digitalRead(18) ) ))
  {
    turnright_slow();
  }
  if (( !( digitalRead(14) ) && !( digitalRead(18) ) ))
  {
    carstop();
    delay( 5000 );
  }
}

void turnright_slow()
{
  analogWrite(6 , 80);
  analogWrite(10 , 0);
  analogWrite(5 , 0);
  analogWrite(9 , 0);
}

void carstop()
{
  analogWrite(6 , 0);
  analogWrite(10 , 0);
  analogWrite(5 , 0);
  analogWrite(9 , 0);
}

void turnleft_slow()
{
  analogWrite(6 , 0);
  analogWrite(10 , 0);
  analogWrite(5 , 80);
  analogWrite(9 , 0);
}

void forward()
{
  analogWrite(6 , 80);
  analogWrite(10 , 0);
  analogWrite(5 , 80);
  analogWrite(9 , 0);
}
