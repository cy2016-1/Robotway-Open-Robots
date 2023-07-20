/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-05-30 https://www.robotway.com/
  ------------------------------*/
void setup()
{
  pinMode( 19 , OUTPUT);
  pinMode( 18 , OUTPUT);
}

void loop()
{
  digitalWrite( 19 , HIGH );
  digitalWrite( 18 , LOW );
  delay( 1000 );
  digitalWrite( 18 , HIGH );
  digitalWrite( 19 , LOW );
  delay( 1000 );
}
