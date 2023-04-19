/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-03-03 https://www.robotway.com/
  ------------------------------*/
#include <Servo.h>

Servo servo_pin_7;
Servo servo_pin_8;

void setup()
{
  servo_pin_7.attach(7);
  servo_pin_8.attach(8);
}

void loop()
{
  servo_pin_7.write( 160 );
  delay( 1000 );
  servo_pin_8.write( 120 );
  delay( 1000 );
  servo_pin_7.write( 0 );
  delay( 1000 );
  servo_pin_8.write( 0 );
  delay( 1000 );
}
