/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-26 https://www.robotway.com/
  -----------------------------------------
  实验功能：
          实现小车大半径转向.
  -----------------------------------------
  实验接线：
                车头
             .--------.
             |        |
             |        |
       左轮   |       |  右轮
      D5, D6 *--------* D9, D10
 ----------------------------------------------------------------------------------*/

// 大半径转向
void bigTurn();

//程序初始化部分.
void setup() {
  pinMode( 5 , OUTPUT);  //将引脚5设置为输出模式
  pinMode( 6 , OUTPUT);  //将引脚6设置为输出模式
  pinMode( 9 , OUTPUT);  //将引脚9设置为输出模式
  pinMode( 10 , OUTPUT); //将引脚10设置为输出模式
}

//主程序部分
void loop() {
  bigTurn();
  delay( 100 );
}

//大半径转向子程序封装.
void bigTurn()
{
  analogWrite( 5 , 0 );    //给引脚5设置0速度
  analogWrite( 6 , 255);   //给引脚6设置255速度
  analogWrite( 9 , 0 );    //给引脚9设置0速度
  analogWrite( 10 , 150 ); //给引脚10设置255速度
}
