/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-02-09 https://www.robotway.com/                                    
------------------------------------------------------------------------------------*/
int pin[3] = {A0, A3, A4};           //按车头前进方向，从右至左定义，后面经过公式计算，会转化为从左至右的顺序
int s;
void setup()
{
  pinMode( 5 , OUTPUT);
  pinMode( 6 , OUTPUT);
  pinMode( 9 , OUTPUT);
  pinMode( 10 , OUTPUT);
}

void loop()
{
   s = 0;
        for(int i=0; i<3; i++)                 //循环获取三个传感器的值
        {
            s|= (!digitalRead(pin[i]) << i);   //经过左移运算和或运算后，按照A0、A3、A4的顺序产生一个三位2进制数值，表示3个传感器的组合触发状态
        }
        switch (s) 
        {
          case 0x00: //三个均未触发
          back();
          Left();
          break;
          case 0x01: //右侧传感器触发，直线上摆动或遇到右转弯
          Right();
          break;
          case 0x02: //中间传感器触发，直线上直行
          Forwards();
          break;
          case 0x04: //左侧传感器触发，直线上摆动或遇到左转弯
          Left();
          break;
          case 0x06: //左侧两个触发，遇到左转弯
          Left();
          break;
          default:;break;
        }
  }
 
void Left()
{
digitalWrite( 5 , LOW );
digitalWrite( 6 , HIGH);
digitalWrite( 9 , HIGH );
digitalWrite( 10 , LOW );
}

void Right()
{
digitalWrite( 5 , HIGH );
digitalWrite( 6 , LOW );
digitalWrite( 9 , LOW );
digitalWrite( 10 , HIGH );
}

void Forwards()
{
digitalWrite( 5 , HIGH );
digitalWrite( 6 , LOW );
digitalWrite( 9 , HIGH );
digitalWrite( 10 , LOW );
}

void back()
{
digitalWrite( 5 , LOW );
digitalWrite( 6 , HIGH );
digitalWrite( 9 , LOW );
digitalWrite( 10 , HIGH );
}
