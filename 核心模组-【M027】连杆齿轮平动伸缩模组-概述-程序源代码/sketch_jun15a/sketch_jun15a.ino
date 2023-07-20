/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-06-21 https://www.robotway.com/
  ------------------------------*/
#include <Servo.h>

Servo servo_pin_3;

void setup()
{
  servo_pin_3.attach(3);
}

void loop()
{
  servo_pin_3.write( 45 );
  delay( 500 );
  servo_pin_3.write( 105 );
  delay( 500 );
}
