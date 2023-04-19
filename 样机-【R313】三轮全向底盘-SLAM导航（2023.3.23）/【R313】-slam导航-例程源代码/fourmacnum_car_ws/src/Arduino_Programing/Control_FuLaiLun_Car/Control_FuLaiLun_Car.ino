/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-03-16 https://www.robotway.com/
  ------------------------------*/
/***************************************************************************************************
实验功能：
         驱动全向三轮底盘实现前进、后退、左转、右转、左平移、右平移

实验接线：
         步进电机细分：16细分
         步进电机方向引脚：dir: x: 44, y: 32, z: 42, a: 30
         步进电机步进引脚：stp: x: 45, y: 33, z: 43, a: 31

实验现象：
         上电后，小车前进3秒，停止5秒；后退3秒，停止5秒；
         左平移3秒，停止5秒；右平移3秒，停止5秒；左转3秒，停5秒，右转3秒，停5秒，小车停止。
***************************************************************************************************/
//DUE控制版需要启用USE_USBON或USE_NATIVE_USB,UNO不需要
//#define USE_USBCON          //PAOGRAMMING PORT
#define USE_NATIVE_USB      //NATIVE USB PORT
#include <ros.h>
#include <ros/time.h>
#include <geometry_msgs/Vector3.h>
ros::NodeHandle  nh;
#define Action_implement_delay 3000 //单个动作执行所用时间
#define Action_wait_for_delay 5000  //动作与动作之间的间隔时间
#define Set_Speed_Test 0.04
void XYRun(double vx, double vy, double w);
void messageCb( const geometry_msgs::Vector3& vel_cmd)  {XYSetVel(vel_cmd.x, vel_cmd.y, vel_cmd.z);}
ros::Subscriber<geometry_msgs::Vector3> vel_cmd_sub("vel_cmd", &messageCb );

geometry_msgs::Vector3 pose_message;
ros::Publisher pose_feedback_pub("pose_feedback",&pose_message);
geometry_msgs::Vector3 vel_message;
ros::Publisher vel_feedback_pub("vel_feedback",&vel_message);

const int kMessagePubRate = 5;
unsigned long message_pub_time = 0;
const int kReadMotorDeltaT = 50;
unsigned long position_read_time = 0;
float current_x = 0,current_y = 0,current_a = 0;
float current_vx = 0,current_vy = 0,current_va = 0;

void setup()
{
  delay(1000);
  Serial.begin(57600);
  initMotor();
//  Stepper_move_test();
  nh.initNode();
  nh.subscribe(vel_cmd_sub);
  nh.advertise(pose_feedback_pub);
  nh.advertise(vel_feedback_pub);
  XYSetVel(0.0,0.0,0.0);
  position_read_time = millis();
  message_pub_time = millis();
}

void loop()
{
  XYRun();  
  if(millis()>position_read_time)
  {
    XYRead();
    position_read_time += kReadMotorDeltaT;
  }
  if(millis()>message_pub_time)
  {
    pose_message.x = current_x;
    pose_message.y = current_y;
    pose_message.z = current_a;
    vel_message.x = current_vx;
    vel_message.y = current_vy;
    vel_message.z = current_va;
    pose_feedback_pub.publish(&pose_message);
    vel_feedback_pub.publish(&vel_message);
    message_pub_time+=1000.0/kMessagePubRate;
  }
  nh.spinOnce();  
}
