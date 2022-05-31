/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-31 https://www.robotway.com/
  ---------------------------------------------
  实验功能：
          实现带传动模块正反转.
          具体现象为：带传动模块正转一秒，再反转一秒.
  ---------------------------------------------
  实验接线：
          带传动模块电机接D5,D6引脚
 ------------------------------------------------------------------------------------*/

//程序初始化部分：设置引脚模式.
void setup(){
  pinMode( 5 , OUTPUT); //引脚D5设置为输出模式
  pinMode( 6 , OUTPUT); //引脚D6设置为输出模式
}

void loop()
{
  digitalWrite( 5 , LOW );  //----------.
  digitalWrite( 6 , HIGH ); //  正转1秒  |
  delay( 1000);             //----------*
  
  digitalWrite( 5 , HIGH ); //----------.
  digitalWrite( 6 , LOW);   //  反转1秒  |
  delay( 1000);             //----------*
}
