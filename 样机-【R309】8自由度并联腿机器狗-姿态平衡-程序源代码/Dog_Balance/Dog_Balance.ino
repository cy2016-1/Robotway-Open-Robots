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
  Dog_Balance(); //狗保持平衡
}



void Dog_Balance()
{
   static long t_control = millis();
   float f = readFront();
   float b = readBack();
   readPose();
    if ((millis() - t_control) > 40) {
      if (f && !b) {
        leg0.back();
        leg1.back();
        leg2.back();
        leg3.back();
      } else if (b && !f) {
        leg0.front();
        leg1.front();
        leg2.front();
        leg3.front();
      }
      if (Eular[0] > 3) {
        leg0.down();
        leg1.down();
        leg2.up();
        leg3.up();
      }
      if (Eular[0] < -3) {
        leg0.up();
        leg1.up();
        leg2.down();
        leg3.down();
      }
      if (Eular[1] < 0 && Eular[1] > -176) {
        leg0.up();
        leg1.down();
        leg2.up();
        leg3.down();
      }
      if (Eular[1] > 0 && Eular[1] < 176) {
        leg0.down();
        leg1.up();
        leg2.down();
        leg3.up();
      }
      leg0.updatePos();
      leg1.updatePos();
      leg2.updatePos();
      leg3.updatePos();
      // SerialUSB.println();
      t_control = millis();
    }  
}

 
