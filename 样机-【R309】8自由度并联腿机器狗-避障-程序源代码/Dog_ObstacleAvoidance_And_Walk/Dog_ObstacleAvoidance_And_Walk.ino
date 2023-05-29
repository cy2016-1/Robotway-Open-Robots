/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-05-18 https://www.robotway.com/
  ------------------------------*/
#include "leg.h"
#include "gait.h"
#include "sensor.h"


enum{DOGBALANCE=1,DOGWALK,DogObstacleAvoidanceWalk};

float Eular[3]; /* 欧拉角 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.begin(115200);
  sensorSetup();
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Dog_ObstacleAvoidance_And_Walk();  //狗行走并避障。
}





void Dog_ObstacleAvoidance_And_Walk()
{
   static long t_control = millis();
   static int t0 = millis();
   static int status = 0;
   static gaitParam cur_gait = backwardGait;    //狗步态1
   static gaitParam cur_gait2 = backwardGait2;  //狗步态2
   if( 1 ){
    cur_gait = backwardGait;
    cur_gait2 = backwardGait2;
    t0 = millis();
   }
   float f = readFront();
   float b = readBack();
   readPose();
    if ((millis() - t_control) > 50)
    {
      float x[4], y[4];
      long t = millis() - t0;
      if (f && !b)
      {
        cur_gait = forwardGait;
        cur_gait2 = forwardGait2;
      }
      else if (b && !f)
      {
        cur_gait = backwardGait;
        cur_gait2 = backwardGait2;
      }
      gait(t, 0.5, x[0], y[0], cur_gait);
      gait(t, 0, x[1], y[1], cur_gait2);
      gait(t, 0, x[2], y[2], cur_gait2);
      gait(t, 0.5, x[3], y[3], cur_gait);
      leg0.footPos(x[0], y[0]);
      leg1.footPos(x[1], y[1]);
      leg2.footPos(x[2], y[2]);
      leg3.footPos(x[3], y[3]);
      t_control = millis();
    }  
}
