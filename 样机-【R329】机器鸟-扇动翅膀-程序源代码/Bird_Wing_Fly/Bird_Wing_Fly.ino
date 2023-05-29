/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-05-24 https://www.robotway.com/
  ------------------------------*/
#include <Servo.h>

int _ABVAR_1_Subdivision_number = 0 ;
int _ABVAR_2_Flags = 0 ;
Servo servo_pin_3;
int _ABVAR_3_Servo3_Start = 0 ;
int _ABVAR_4_Servo3_End = 0 ;
int _ABVAR_5_Angle_Of_Each_Time = 0 ;
int _ABVAR_6_value1 = 0 ;
int _ABVAR_7_Angle_Of_Change = 0 ;
int _ABVAR_8_value2 = 0 ;

void Wing_Open();
void Wing_Close();

void setup()
{
  servo_pin_3.attach(3);
  _ABVAR_1_Subdivision_number = 14 ;

  _ABVAR_2_Flags = 0 ;

  servo_pin_3.write( 80 );

  delay( 1000 );

}

void loop()
{
  Wing_Close();
  Wing_Open();
}

void Wing_Close()
{
  _ABVAR_3_Servo3_Start = 10 ;
  _ABVAR_4_Servo3_End = 80 ;
  _ABVAR_5_Angle_Of_Each_Time = ( abs( ( _ABVAR_3_Servo3_Start - _ABVAR_4_Servo3_End ) ) / _ABVAR_1_Subdivision_number ) ;
  if (( ( ( _ABVAR_3_Servo3_Start - _ABVAR_4_Servo3_End ) ) > ( 1 ) ))
  {
    _ABVAR_2_Flags = -1 ;
  }
  else
  {
    _ABVAR_2_Flags = 1 ;
  }
  for (_ABVAR_6_value1= 1; _ABVAR_6_value1<= ( ( _ABVAR_1_Subdivision_number + 1 ) ); _ABVAR_6_value1++ )
  {
    _ABVAR_7_Angle_Of_Change = ( _ABVAR_3_Servo3_Start + ( _ABVAR_5_Angle_Of_Each_Time * _ABVAR_2_Flags ) ) ;
    servo_pin_3.write( _ABVAR_7_Angle_Of_Change );
    _ABVAR_3_Servo3_Start = _ABVAR_7_Angle_Of_Change ;
    delay( 28 );
  }
}

void Wing_Open()
{
  _ABVAR_3_Servo3_Start = 80 ;
  _ABVAR_4_Servo3_End = 10 ;
  _ABVAR_5_Angle_Of_Each_Time = ( abs( ( _ABVAR_3_Servo3_Start - _ABVAR_4_Servo3_End ) ) / _ABVAR_1_Subdivision_number ) ;
  if (( ( ( _ABVAR_3_Servo3_Start - _ABVAR_4_Servo3_End ) ) > ( 1 ) ))
  {
    _ABVAR_2_Flags = -1 ;
  }
  else
  {
    _ABVAR_2_Flags = 1 ;
  }
  for (_ABVAR_8_value2= 1; _ABVAR_8_value2<= ( ( _ABVAR_1_Subdivision_number + 1 ) ); _ABVAR_8_value2++ )
  {
    _ABVAR_7_Angle_Of_Change = ( _ABVAR_3_Servo3_Start + ( _ABVAR_5_Angle_Of_Each_Time * _ABVAR_2_Flags ) ) ;
    servo_pin_3.write( _ABVAR_7_Angle_Of_Change );
    _ABVAR_3_Servo3_Start = _ABVAR_7_Angle_Of_Change ;
    delay( 65 );
  }
}
