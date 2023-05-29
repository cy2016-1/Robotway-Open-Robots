/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-05-17 https://www.robotway.com/
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
  Dog_Walk();    //狗前进（行走）
}



void Dog_Walk()
{
   static long t_control = millis();
   static int t0 = millis();
   if(t_control){   t0 = millis();   }
    if ((millis() - t_control) > 50)
    {
      float x[4], y[4];
      long t = millis() - t0;
      gait(t, 0.5, x[0], y[0], forwardGait);
      gait(t, 0, x[1], y[1], forwardGait);
      gait(t, 0, x[2], y[2], forwardGait);
      gait(t, 0.5, x[3], y[3], forwardGait);
      leg0.footPos(x[0], y[0]);
      leg1.footPos(x[1], y[1]);
      leg2.footPos(x[2], y[2]);
      leg3.footPos(x[3], y[3]);
      t_control = millis();
    }      
}

 
