
//假想循迹场地，有直线、左转弯、右转弯、十字路口；
//双轮小车，并排安装三个灰度传感器；

int pin[3] = {A4, A3, A0};           //按车头前进方向，从右至左定义，后面经过公式计算，会转化为从左至右的顺序
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
          Forwards();
          break;
          case 0x01: //右侧传感器触发，直线上摆动或遇到右转弯
          Right();
          break;
          case 0x02: //中间传感器触发，直线上直行
          Forwards();
          break;
          case 0x03: //右侧两个触发，遇到右转弯
          Right();
          break;
          case 0x04: //左侧传感器触发，直线上摆动或遇到左转弯
          Left();
          break;
          case 0x06: //左侧两个触发，遇到左转弯
          Left();
          break;
          case 0x07: //三个同时触发，遇到十字路口
          Forwards();
          break;
          default:;break;
        }
  }
 
void Left()
{
digitalWrite( 5 , HIGH );
digitalWrite( 6 , LOW );
digitalWrite( 9 , LOW );
digitalWrite( 10 , LOW );
}

void Right()
{
digitalWrite( 5 , LOW );
digitalWrite( 6 , LOW );
digitalWrite( 9 , HIGH );
digitalWrite( 10 , LOW );
}

void Forwards()
{
digitalWrite( 5 , HIGH );
digitalWrite( 6 , LOW );
digitalWrite( 9 , HIGH );
digitalWrite( 10 , LOW );
}
