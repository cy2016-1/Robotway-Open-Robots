/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-05-24 https://www.robotway.com/
  ------------------------------*/
#include <Servo.h>

Servo servo_pin_3;
Servo servo_pin_4;
int _ABVAR_1_angle_first = 0 ;
int _ABVAR_2_num = 0 ;
int _ABVAR_3_angle_second = 0 ;

void swing_reset();
void leftUp_Swing();

void setup()
{
  servo_pin_3.attach(3);
  servo_pin_4.attach(4);
  servo_pin_3.write( 100 );

  servo_pin_4.write( 14 );

  delay( 1000 );

}

void loop()
{
  leftUp_Swing();
  swing_reset();
}

void leftUp_Swing()
{
  _ABVAR_1_angle_first = 100 ;
  for (_ABVAR_2_num= 1; _ABVAR_2_num<= ( 14 ); _ABVAR_2_num++ )
  {
    _ABVAR_1_angle_first = ( _ABVAR_1_angle_first - 5 ) ;
    servo_pin_3.write( _ABVAR_1_angle_first );
    delay( 50 );
  }
  delay( 1000 );
}

void swing_reset()
{
  _ABVAR_3_angle_second = 30 ;
  for (_ABVAR_2_num= 1; _ABVAR_2_num<= ( 14 ); _ABVAR_2_num++ )
  {
    _ABVAR_3_angle_second = ( _ABVAR_3_angle_second + 5 ) ;
    servo_pin_3.write( _ABVAR_3_angle_second );
    delay( 50 );
  }
  delay( 1000 );
}
