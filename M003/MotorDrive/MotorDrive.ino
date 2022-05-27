/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-27 https://www.robotway.com/
  ----------------------------
  实验功能：
          实现直流电机模组正转反转.
  -----------------------------
  实验接线：
          直流电机引脚接D5,D6引脚.
 ------------------------------------------------------------------------------------*/
//程序初始化部分：初始化直流电机引脚.
void setup() {
  pinMode( 5 , OUTPUT);//将引脚5设置为输出模式
  pinMode( 6 , OUTPUT);//将引脚6设置为输出模式
}

//主程序部分：实现直流电机持续执行正转一秒，反转1秒动作组.
void loop() {
  digitalWrite( 5 , LOW );       //-------------.
  digitalWrite( 6 , HIGH );      //电机模组正转1秒|
  delay( 1000);                  //-------------*
  
  digitalWrite( 5 , HIGH );      //-------------.
  digitalWrite( 6 , LOW);        //电机模组反转1秒|
  delay( 1000);                  //-------------*
}
