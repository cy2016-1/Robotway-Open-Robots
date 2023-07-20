/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-06-16 https://www.robotway.com/
  ------------------------------*/
void setup()
{
  pinMode( 5 , OUTPUT);
  pinMode( 6 , OUTPUT);
}

void loop()
{
  digitalWrite( 5 , HIGH );
  digitalWrite( 6 , LOW );
  delay( 500 );
  digitalWrite( 5 , HIGH );
  digitalWrite( 6 , HIGH );
  delay( 1000 );
  digitalWrite( 5 , LOW );
  digitalWrite( 6 , HIGH );
  delay( 500 );
  digitalWrite( 5 , HIGH );
  digitalWrite( 6 , HIGH );
  delay( 1000 );
}
