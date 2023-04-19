/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-02-10 https://www.robotway.com/                               
------------------------------------------------------------------------------------*/
void Right();
void Left();
void Stop();
void Forward();
void Back();

void setup()
{
  pinMode( 17, INPUT);
  pinMode( 18, INPUT);
  pinMode( 14, INPUT);
  pinMode( 10, OUTPUT);
  pinMode( 6, OUTPUT);
  pinMode( 5, OUTPUT);
  pinMode( 9, OUTPUT);
}

void loop()
{
  if (((!( digitalRead(14)) && ! (digitalRead(17)) ) ))
  {
    Forward();
  }
  if (( digitalRead(14) ))
  {
    Left();
    delay( 300 );
  }
  if (( digitalRead(17) ))
  {
    Right();
    delay( 300 );
  }
  if (( digitalRead(18) ))
  {
    Back();
    delay( 1000 );
    analogWrite(5 , 100);
    analogWrite(6 , 0);
    analogWrite(9 , 0);
    analogWrite(10 , 100);
    delay( 1500 );
  }
}

void Right()
{
  analogWrite(5 , 0);
  analogWrite(6 , 0);
  analogWrite(9 , 100);
  analogWrite(10 , 0);
}

void Forward()
{
  analogWrite(5 , 100);
  analogWrite(6 , 0);
  analogWrite(9 , 100);
  analogWrite(10 , 0);
}

void Back()
{
  analogWrite(5 , 0);
  analogWrite(6 , 100);
  analogWrite(9 , 0);
  analogWrite(10 , 100);
}

void Left()
{
  analogWrite(5 , 100);
  analogWrite(6 , 0);
  analogWrite(9 , 0);
  analogWrite(10 , 0);
}

void Stop()
{
  analogWrite(5 , 0);
  analogWrite(6 , 0);
  analogWrite(9 , 0);
  analogWrite(10 , 0);
}
