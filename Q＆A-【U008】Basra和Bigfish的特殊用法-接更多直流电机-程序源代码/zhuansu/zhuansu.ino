/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-05-30 https://www.robotway.com/
  ------------------------------*/
int _ABVAR_1_i = 0 ;

void setup()
{
  pinMode( 19, OUTPUT);
  pinMode( 18 , OUTPUT);
}

void loop()
{
  for (_ABVAR_1_i= 1; _ABVAR_1_i<= ( 255 ); _ABVAR_1_i++ )
  {
    analogWrite(19 , ( 255 - _ABVAR_1_i ));
    digitalWrite( 18 , LOW );
    delay( 100 );
  }
}
