/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-05-23 https://www.robotway.com/
  ------------------------------*/
#include <Servo.h>

int _ABVAR_1_angle_right = 0 ;
int _ABVAR_2_num = 0 ;
Servo servo_pin_4;
int _ABVAR_3_angle_left = 0 ;

void Right_Left();
void left_Right();

void setup()
{
  servo_pin_4.attach(4);
}

void loop()
{
  left_Right();
  Right_Left();
}

void Right_Left()
{
  _ABVAR_1_angle_right = 70 ;
  for (_ABVAR_2_num= 1; _ABVAR_2_num<= ( 8 ); _ABVAR_2_num++ )
  {
    _ABVAR_1_angle_right = ( _ABVAR_1_angle_right + 5 ) ;
    servo_pin_4.write( _ABVAR_1_angle_right );
    delay( 100 );
  }
}

void left_Right()
{
  _ABVAR_3_angle_left = 110 ;
  for (_ABVAR_2_num= 1; _ABVAR_2_num<= ( 8 ); _ABVAR_2_num++ )
  {
    _ABVAR_3_angle_left = ( _ABVAR_3_angle_left - 5 ) ;
    servo_pin_4.write( _ABVAR_3_angle_left );
    delay( 100 );
  }
}
