/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-03-01 https://www.robotway.com/
  ------------------------------*/
/*
 * 颜色追踪下位机程序
 */

#include <ros.h>
#include <std_msgs/String.h>
#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#define CTL_BAUDRATE 115200 //总线舵机波特率
#define mySerial Serial1
#define SerialBaudrate 57600
#define RGB_LED_NU MBERS 3
#define Bus_servo_Angle_inits 1500
#define ActionDelayTimes 1500
//
#define wheel_speed_forward 0.07    //car forward speed
#define wheel_speed_back -0.07      //car back speed
#define wheel_speed_stop 0.0        //car stop speed 
#define wheel_speed_left 0.07       //car turnleft speed
#define wheel_speed_right -0.07     //car turnright speed
#define wheel_speed_left_translation -0.07   //speed of car left translation
#define wheel_speed_right_translation 0.07 //speed of car right translation

String receive_string="hello";
ros::NodeHandle  nh;
void messageCb( const std_msgs::String &toggle_msg){
   receive_string=toggle_msg.data;
}

ros::Subscriber<std_msgs::String> sub("hahaha", &messageCb );
//std_msgs::String str_msg;
//ros::Publisher chatter("chatter", &str_msg);
enum{FORWARD=1,BACK,LEFT,RIGHT,LEFT_TRANSLATION,RIGHT_TRANSLATION,STOP}; //the movement state of the car


void setup()
{
  delay(1100);
  Serial.begin(SerialBaudrate);
  mySerial.begin(CTL_BAUDRATE);
  init_Servo();  
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  if( (receive_string.length())<5 && (receive_string.length())>15 )
  {
     for(int i=0;i<1;i++){
     break;
     }
  }
    else{
       int SpacePosition[2] = {0,0};
       int Data_one = 0; 
       int Data_two = 0;
       int numbers_left=0 ,numbers_right=0;
       char num_left[32] = {}; 
       char num_right[32] = {};
       String x_data="";
       String y_data="";
       String z_data="";
       String new_string = "";                                                                                
       SpacePosition[0] = receive_string.indexOf('-');
       x_data = receive_string.substring(0,SpacePosition[0]);
       //if(x_data.length()>=4){break;}
       new_string = receive_string.substring(SpacePosition[0]+1);
       SpacePosition[1] = new_string.indexOf('+');
       y_data = new_string.substring(0,SpacePosition[1]);
       z_data = new_string.substring(SpacePosition[1]+1);

      Data_one = x_data.toInt();
      Data_two = y_data.toInt();
      //if( (Data_one<=120) && (z_data =="state") ){Car_Move(LEFT_TRANSLATION);}
      if( (Data_one<=280) && (Data_one>=20)){Car_Move(LEFT_TRANSLATION);}
      else if ( (Data_one>=360) && (Data_one<=600) ){Car_Move(RIGHT_TRANSLATION);}
      else if( z_data == "forward" ){Car_Move(FORWARD);}
      else if( z_data == "back" ){Car_Move(BACK );}
      else {Car_Move(STOP);}
     
      receive_string = "";
      x_data="";
      y_data="";
      z_data="";
      new_string="";
    }  
  nh.spinOnce();
  delay(100);
}
