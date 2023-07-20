/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-06-26 https://www.robotway.com/
  ------------------------------*/
/*****
  Copyright 2017 Robot TIme
  原地踏步例程
*****/

#include "Tlc5940.h"
#include "tlc_servos.h"
#include <math.h>

#include "types.h"
#include "config.h"

// 相关函数声明
/***** 红外相关函数 *****/
void IRInit(); //红外初始化
void enableIR(); //红外使能
void disableIR(); //关闭红外
void updateIR(); //红外避障更新动作
/***** 平衡相关函数 *****/
void switchAdjustStat(uint stat); //切换平衡调节模式 不调节/原地调节/行进间调节
void readGyroSerial(); //读取陀螺仪串口消息
void adjustAct(); //平衡调节动作
/****** 腿部动作相关函数 *****/
void setTurnLeftFlag(bool flag); //修改左转状态标志位
void setTurnRightFlag(bool flag); //修改右转状态标志位
void leg1(); //更新1号腿（左前）位置
void leg2(); //更新2号腿（左后）位置
void leg3(); //更新3号腿（右前）位置
void leg4(); //更新4号腿（右后）位置
bool calc(Point3d p, bool leg1, bool leg2, bool leg3, bool leg4); //逆解计算函数
/***** 整机动作相关函数 *****/
void dogReset(Point3d initPos, uint waitTime); //复位动作
void dogInit(); //初始化动作
void upDown(float x, float y, float z1, float z2, uint times); //蹲起动作
void drawCircle(float ox, float oy, float z, float r, uint times); //原地圆形摆动动作
void stepping(float x, float y, float z1, float z2, uint times); // 原地踏步动作
void liftShoulder(uint height, uint times); //原地摆臂动作

//动作周期计数器
int cycleCount;
//复位计数器
void resetCycleCount()
{
  cycleCount = -1;
}
void updateCycleCount()
{
  cycleCount++;
}

//当前运动状态
dogMode currentMode;
//切换运动状态
void setMode(dogMode mode)
{
  if (mode == currentMode) return;
  if (mode == DOG_MODE_TURN_LEFT)
  {
    setTurnLeftFlag(true);
    setTurnRightFlag(false);
  } else if (mode == DOG_MODE_TURN_RIGHT)
  {
    setTurnLeftFlag(false);
    setTurnRightFlag(true);
  } else {
    setTurnLeftFlag(false);
    setTurnRightFlag(false);
  }

  if (mode == DOG_MODE_BACK) //后退时关闭红外传感器
  {
    disableIR();
  } else if (mode == DOG_MODE_STOP) //静止后开始原地姿态调节
  {
    switchAdjustStat(ADJUST_STAT_LEG);
    dogReset({0, 0, Leg_Init_Z_Pos}, 200);
  }
  currentMode = mode;
}

void updateMode()
{
  if (cycleCount == MOTION_TIMES + 1) setMode(DOG_MODE_BACK);
  if (cycleCount == 3 * MOTION_TIMES) setMode(DOG_MODE_LEFT);
  if (cycleCount == 4 * MOTION_TIMES) setMode(DOG_MODE_RIGHT);
  if (cycleCount == 5 * MOTION_TIMES) setMode(DOG_MODE_RIGHT_FRONT);
  if (cycleCount == 6 * MOTION_TIMES) setMode(DOG_MODE_RIGHT_BACK);
  if (cycleCount == 7 * MOTION_TIMES) setMode(DOG_MODE_LEFT_BACK);
  if (cycleCount == 8 * MOTION_TIMES) setMode(DOG_MODE_LEFT_FRONT);
  if (cycleCount == 9 * MOTION_TIMES) setMode(DOG_MODE_TURN_LEFT);
  if (cycleCount == 10 * MOTION_TIMES) setMode(DOG_MODE_TURN_RIGHT);
  if (cycleCount == 11 * MOTION_TIMES) setMode(DOG_MODE_STOP);
}

void setup()
{
  //陀螺仪连接串口，波特率115200
  Serial.begin(115200);

  //舵机驱动板初始化
  Tlc.init(0);
  tlc_initServos();  // Note: this will drop the PWM freqency down to 50Hz.

  //红外传感器初始化
  IRInit();

  //大狗身体初始化
  dogInit();

  //原地踏步10次后停止
  stepping(0, 0, -150, -100, 10);
  while(1);
}

void loop()
{
}
