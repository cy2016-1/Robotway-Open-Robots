/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-05-23 https://www.robotway.com/
  ------------------------------*/
#include <Servo.h>

int _ABVAR_1_angle_current2 = 0 ;
int _ABVAR_2_num = 0 ;
Servo servo_pin_4;
int _ABVAR_3_angle_current1 = 0 ;

void up_down();
void down_up();

void setup()
{
  servo_pin_4.attach(4);
}

void loop()
{
  down_up();
  up_down();
}

void down_up()
{
  _ABVAR_1_angle_current2 = 30 ;
  for (_ABVAR_2_num= 1; _ABVAR_2_num<= ( 16 ); _ABVAR_2_num++ )
  {
    _ABVAR_1_angle_current2 = ( _ABVAR_1_angle_current2 + 5 ) ;
    servo_pin_4.write( _ABVAR_1_angle_current2 );
    delay( 50 );
  }
}

void up_down()
{
  _ABVAR_3_angle_current1 = 110 ;
  for (_ABVAR_2_num= 1; _ABVAR_2_num<= ( 16 ); _ABVAR_2_num++ )
  {
    _ABVAR_3_angle_current1 = ( _ABVAR_3_angle_current1 - 5 ) ;
    servo_pin_4.write( _ABVAR_3_angle_current1 );
    delay( 50 );
  }
}
