/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-05-15 https://www.robotway.com/
  ------------------------------*/
#include <Servo.h>

Servo servo_pin_4;

void setup()
{
  servo_pin_4.attach(4);
}

void loop()
{
  servo_pin_4.write( 90 );
  delay( 1000 );
  servo_pin_4.write( 0 );
  delay( 1000 );
  servo_pin_4.write( 90 );
  delay( 1000 );
  servo_pin_4.write( 180 );
  delay( 1000 );
}
