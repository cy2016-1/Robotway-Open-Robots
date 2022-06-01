/*------------------------------------------------------------------------------------
  版权说明：Copyright 2022 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2022-5-31 https://www.robotway.com/
  ----------------------------------
  实验功能：
          实现云台模组的两个舵机同时运动.
  -----------------------------------------------
  实验接线：
               云台
             .-----.
             |     |   控制云台上下的舵机接：D3
           .---------.
           |         | 控制云台左右转动的舵机接：D4
           |         |
        -----------------
 ------------------------------------------------------------------------------------*/
#include <Servo.h>  //调用舵机库函数
Servo servo_pin_3; //声明控制云台上下转动的舵机
Servo servo_pin_4; //声明控制云台左右转动的舵机

//程序初始化部分：使能舵机引脚，并设置舵机初始角度
void setup() {
  servo_pin_3.attach(3); //使能3号舵机
  servo_pin_4.attach(4); //使能4号舵机
  servo_pin_3.write(0);  //3号舵机初始转到0度
  servo_pin_4.write(0);  //4号舵机初始转到0度
}

void loop() {
  Servo_Move( 0,95, 0,180); //D4舵机缓慢从0度转到180度,同时D3舵机缓慢从0度转到95度
  Servo_Move( 95,0, 180,0); //D4舵机缓慢从180度转到0度,同时D3舵机缓慢从95度转到0度
}

/*两舵机同时转动子函数.使用方法如下所示：
  servo_loop_count：表示舵机从A角度转到B角度分成了多少份.
  delay(20);表示每一份需要的延时时间.
  Servo_Move( 30, 45, 23, 80 );表示的意识是：D4舵机缓慢从23度转到80度,同时D3舵机缓慢从30度转到45度
  Servo_Move( 45, 30, 80, 23 );表示的意识是：D4舵机缓慢从80度转到23度,同时D3舵机缓慢从45度转到30度
 */
void Servo_Move(float servo3_start_angle, float servo3_end_angle, float servo4_start_angle, float servo4_end_angle){
  servo_pin_3.write( servo3_start_angle ); //设置3号舵机初始角度
  servo_pin_4.write( servo4_start_angle ); //设置4号舵机初始角度
  float xunhuan_count = 30.0;
  float delta_servo3 = 0;
  float delta_servo4 = 0;
  float servo3_calculate_angle = 0;
  float servo4_calculate_angle = 0;
  int   servo3_really_angle  = 0;
  int   servo4_really_angle  = 0;
  delta_servo3 = - ( ( servo3_start_angle - servo3_end_angle ) / xunhuan_count );
  delta_servo4 = - ( ( servo4_start_angle - servo4_end_angle ) / xunhuan_count );
  for( float i = 0; i< xunhuan_count; i++ )
  {
    servo3_calculate_angle = servo3_calculate_angle + delta_servo3;
    servo4_calculate_angle = servo4_calculate_angle + delta_servo4;
    servo3_really_angle = int(servo3_calculate_angle);
    servo4_really_angle = int(servo4_calculate_angle);
    servo_pin_4.write(servo4_really_angle);
    servo_pin_3.write(servo3_really_angle);
    delay(20);
  }
}
