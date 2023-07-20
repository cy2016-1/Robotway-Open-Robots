/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-06-14 https://www.robotway.com/
  ------------------------------*/
#include <Servo.h>

Servo servo_pin_4;
Servo servo_pin_3;
Servo servo_pin_8;
Servo servo_pin_11;
Servo servo_pin_7;
int _ABVAR_1_i = 0 ;

void setup()
{
  pinMode( 14, INPUT);
  servo_pin_4.attach(4);
  servo_pin_3.attach(3);
  servo_pin_8.attach(8);
  servo_pin_11.attach(11);
  servo_pin_7.attach(7);
  pinMode( 9 , OUTPUT);
  pinMode( 10 , OUTPUT);
  pinMode( 5 , OUTPUT);
  pinMode( 6 , OUTPUT);
  servo_pin_4.write( 140 );

  servo_pin_3.write( 170 );

  servo_pin_8.write( 50 );

  servo_pin_11.write( 74 );

  servo_pin_7.write( 94 );

  delay( 1000 );

}

void loop()
{
  if (digitalRead(14))
  {
    for (_ABVAR_1_i= 1; _ABVAR_1_i<= ( 80 ); _ABVAR_1_i++ )
    {
      servo_pin_4.write( ( 140 - _ABVAR_1_i ) );
      delay( 10 );
    }
    delay( 1000 );
    for (_ABVAR_1_i= 1; _ABVAR_1_i<= ( 80 ); _ABVAR_1_i++ )
    {
      servo_pin_4.write( ( 60 + _ABVAR_1_i ) );
      delay( 10 );
    }
    digitalWrite( 9 , HIGH );
    digitalWrite( 10 , LOW );
    delay( 2000 );
    digitalWrite( 9 , LOW );
    digitalWrite( 10 , LOW );
    for (_ABVAR_1_i= 1; _ABVAR_1_i<= ( 100 ); _ABVAR_1_i++ )
    {
      servo_pin_3.write( ( 170 - _ABVAR_1_i ) );
      delay( 20 );
    }
    digitalWrite( 5 , HIGH );
    digitalWrite( 6 , LOW );
    delay( 1000 );
    digitalWrite( 5 , LOW );
    digitalWrite( 6 , LOW );
    delay( 1000 );
    for (_ABVAR_1_i= 1; _ABVAR_1_i<= ( 69 ); _ABVAR_1_i++ )
    {
      servo_pin_3.write( ( 70 - _ABVAR_1_i ) );
      delay( 20 );
    }
    for (_ABVAR_1_i= 1; _ABVAR_1_i<= ( 41 ); _ABVAR_1_i++ )
    {
      servo_pin_8.write( ( 50 + _ABVAR_1_i ) );
      delay( 20 );
    }
    for (_ABVAR_1_i= 1; _ABVAR_1_i<= ( 73 ); _ABVAR_1_i++ )
    {
      servo_pin_11.write( ( 74 - _ABVAR_1_i ) );
      delay( 20 );
    }
    for (_ABVAR_1_i= 1; _ABVAR_1_i<= ( 85 ); _ABVAR_1_i++ )
    {
      servo_pin_7.write( ( 94 - _ABVAR_1_i ) );
      delay( 20 );
    }
    for (_ABVAR_1_i= 1; _ABVAR_1_i<= ( 64 ); _ABVAR_1_i++ )
    {
      servo_pin_11.write( ( 1 + _ABVAR_1_i ) );
      delay( 20 );
    }
    for (_ABVAR_1_i= 1; _ABVAR_1_i<= ( 70 ); _ABVAR_1_i++ )
    {
      servo_pin_8.write( ( 91 - _ABVAR_1_i ) );
      delay( 20 );
    }
    for (_ABVAR_1_i= 1; _ABVAR_1_i<= ( 64 ); _ABVAR_1_i++ )
    {
      servo_pin_11.write( ( 65 - _ABVAR_1_i ) );
      delay( 20 );
    }
    for (_ABVAR_1_i= 1; _ABVAR_1_i<= ( 169 ); _ABVAR_1_i++ )
    {
      servo_pin_3.write( ( 1 + _ABVAR_1_i ) );
      delay( 20 );
    }
    for (_ABVAR_1_i= 1; _ABVAR_1_i<= ( 170 ); _ABVAR_1_i++ )
    {
      servo_pin_7.write( ( 9 + _ABVAR_1_i ) );
      delay( 20 );
    }
    for (_ABVAR_1_i= 1; _ABVAR_1_i<= ( 39 ); _ABVAR_1_i++ )
    {
      servo_pin_11.write( ( 1 + _ABVAR_1_i ) );
      delay( 20 );
    }
    for (_ABVAR_1_i= 1; _ABVAR_1_i<= ( 40 ); _ABVAR_1_i++ )
    {
      servo_pin_8.write( ( 20 + _ABVAR_1_i ) );
      delay( 20 );
    }
    for (_ABVAR_1_i= 1; _ABVAR_1_i<= ( 85 ); _ABVAR_1_i++ )
    {
      servo_pin_7.write( ( 179 - _ABVAR_1_i ) );
      delay( 20 );
    }
  }
  else
  {
    servo_pin_4.write( 140 );
    servo_pin_3.write( 170 );
    servo_pin_8.write( 50 );
    servo_pin_11.write( 74 );
    servo_pin_7.write( 94 );
    delay( 1000 );
  }
}
