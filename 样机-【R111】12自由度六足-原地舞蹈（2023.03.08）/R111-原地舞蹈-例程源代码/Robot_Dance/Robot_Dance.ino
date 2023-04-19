/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-02-16 https://www.robotway.com/
  ------------------------------*/
#include <Arduino.h>
#include <avr/pgmspace.h>
#include "Config.h"
#include <Tlc5940.h>
#include <tlc_servos.h>
int count_input = 0;
boolean _b = false;
/**************+++++++++++动作组数组，请将转换后的动作组数据粘贴到相应的动作组中+++++++***************************/
const PROGMEM int actionInit[] = {
  1090, 1790, 1220, 980, 650, 1800, 1020, 1330, 520, 1155, 1260, 2020,
  1090, 1790, 1220, 980, 650, 1800, 1020, 1330, 520, 1155, 1260, 2020,
};
const PROGMEM int actionLeft[] = {
};
const PROGMEM int actionRight[] = {
};
const PROGMEM int actionBack[] = {
};
const PROGMEM int actionDance[] = {
};
const PROGMEM int actionDance[] = {
  1660, 1230, 1220, 980, 1280, 1190, 1020, 1330, 1090, 1155, 1260, 1540,
  1090,1790,1220,980,650,1800,1020,1330,520,1155,1260,2020,
  1490,1590,1220,980,850,1400,1020,1330,1320,1155,1260,2020,
  1490,1590,1220,980,850,1400,1020,1330,1320,1155,1700,1700,
  1490,1590,1220,980,850,1400,1020,1330,1320,1155,1700,2020,
  1090,1790,1220,980,650,1800,1020,1330,520,1155,1260,2020,
  1490,1590,1220,980,850,1400,1020,1330,520,1155,1260,1220,
  1490,1590,1220,980,850,1400,1020,1330,800,700,1260,1220,
  1490,1590,1220,980,850,1400,1020,1330,520,700,1260,1220,
  1090,1790,1220,980,650,1800,1020,1330,520,1155,1260,2020,
  1670,1190,1220,980,1370,1100,1020,1330,1100,1155,1260,1430,
  1090,1190,1220,980,1370,1800,620,1730,1100,1155,1260,1430,
  1090,1190,1220,980,1370,1100,620,1730,1100,1155,1260,1430,
  1670,1190,1220,980,1370,1800,620,1730,1100,1155,1260,1430,
  1090,1190,1220,980,1370,1100,620,1730,1100,1155,1260,1430,
  1090,1190,1220,980,1370,1800,700,1570,1100,1155,1260,1430,
  1670,1190,1220,980,1370,1100,700,1570,1100,1155,1260,1430,
  1670,1190,1220,980,1370,1100,700,1570,520,520,1930,2020,
  1670,1190,1220,980,1370,1100,700,1570,800,520,1930,1700,
  1670,1190,1220,980,1370,1100,700,1570,520,520,1930,2020,
  1670,1190,1220,980,1370,1100,700,1570,800,520,1930,1700,
  1670,1190,1220,980,1370,1100,700,1570,1100,1155,1260,1430,
  1670,1190,1220,980,1370,1100,1020,1330,1100,1155,1260,1430,
  1670,1190,1220,980,1370,1100,1020,1330,1100,1155,1260,1430,
  1670,1190,1220,980,900,1590,1020,1330,720,1155,1260,1430,
  1320,1540,1220,980,1370,1100,1020,1330,1100,1155,1260,1830,
  1670,1190,1220,980,1370,1100,1020,1330,1100,1155,1260,1430,
  1320,1410,1220,980,1370,1100,1020,1330,1100,1155,1260,1950,
  1300,1670,1220,980,1370,1100,1020,1330,1100,1155,1260,1600,
  1670,1190,1220,980,940,1540,1020,1330,920,1155,1260,1430,
  1670,1190,1220,980,1235,1480,1020,1330,580,1155,1260,1430,
  1670,1190,1220,980,940,1540,1020,1330,920,1155,1260,1430,
  1670,1190,990,1210,940,1540,1140,1100,920,1400,1060,1430,
  1300,1670,990,1210,1370,1100,1140,1100,1100,1400,1060,1600,
  1320,1540,990,1210,1370,1100,1140,1100,1100,1400,1060,1830,
  1670,1190,990,1210,1370,1100,1140,1100,1100,1400,1060,1430,
  1670,1190,990,1210,1370,1100,1140,1100,1100,1400,1060,1430,
  1670,1190,1280,920,1370,1100,920,1410,1100,1030,1410,1430,
  1670,1190,990,1210,1370,1100,1140,1100,1100,1400,1060,1430,
  1670,1190,1280,920,1370,1100,920,1410,1100,1030,1410,1430,
  1670,1190,1220,980,1370,1100,1020,1330,1100,1155,1260,1430,
};

/**************************+++++---------分割线--------++++++*******************************************************/

//动作组数组长度获取函数，增加动作组时需要按如下格式添加：actPwmNum[增加的动作组序号] = sizeof(增加的动作组名称) / sizeof(增加的动作组名称[0]);
void act_length()
{
  actPwmNum[0] = (sizeof(actionMove) / sizeof(actionMove[0]))/servo_num;
  actPwmNum[1] = (sizeof(actionLeft) / sizeof(actionLeft[0]))/servo_num;
  actPwmNum[2] = (sizeof(actionRight) / sizeof(actionRight[0]))/servo_num;
  actPwmNum[3] = (sizeof(actionBack) / sizeof(actionBack[0]))/servo_num;
  actPwmNum[4] = (sizeof(actionDance) / sizeof(actionDance[0]))/servo_num;
  actPwmNum[5] = (sizeof(actionInit) / sizeof(actionInit[0]))/servo_num;
}

//map映射函数
long map_servo(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//PWM 转换为舵机角度的函数，增加动作组时需要修改
void vlaue2angle(int p, int act)
{
  switch(act)
  {
    case 0:  value_cur[p] = map_servo(pgm_read_word_near(actionMove + p + servo_num * count_input), 500, 2500, 0, 180);  break;
    case 1:  value_cur[p] = map_servo(pgm_read_word_near(actionLeft + p + servo_num * count_input), 500, 2500, 0, 180);  break;
    case 2:  value_cur[p] = map_servo(pgm_read_word_near(actionRight + p + servo_num * count_input), 500, 2500, 0, 180);  break;
    case 3:  value_cur[p] = map_servo(pgm_read_word_near(actionBack + p + servo_num * count_input), 500, 2500, 0, 180);  break;
    case 4:  value_cur[p] = map_servo(pgm_read_word_near(actionDance + p + servo_num * count_input), 500, 2500, 0, 180); break;
    case 5:  value_cur[p] = map_servo(pgm_read_word_near(actionInit + p + servo_num * count_input), 500, 2500, 0, 180); break;
    default: break;
  } 
}

//舵机初始化函数，动作组第一行为舵机初始化值
void servo_init(int act, int num)
{  
 
  if(!_b)
  {
    for(int i=0;i<servo_num;i++)
    {
      vlaue2angle(i, act);
      tlc_setServo(servo_pin[i], value_cur[i]);
      value_pre[i] = value_cur[i];
    }
    Tlc.update();
    //delay(1000);
  }
  
  num == 1 ? _b = true : _b = false;

}

//舵机移动函数，参数： act：动作组宏定义名称 ；num：动作组执行的次数，num > 0 ；
void servo_move(int act, int num)
{  
  float value_delta[servo_num] = {};
  float in_value[servo_num] = {};
  servo_init(act, num);
  for(int i=0;i< num * actPwmNum[act];i++)
  {
    count_input++;
    
    if(count_input == actPwmNum[act]) 
    {
      count_input = 0;
      continue;
    }
    for(int i=0;i<servo_num;i++)
    {
      vlaue2angle(i, act);
      in_value[i] = value_pre[i];
      value_delta[i] = (value_cur[i] - value_pre[i]) / frequency;
    }
    for(int i=0;i<frequency;i++)
    {
      for(int k=0;k<servo_num;k++)
      {
        in_value[k] += value_delta[k];  
        value_pre[k] = in_value[k];
      }
      for(int j=0;j<servo_num;j++)
      {        
        tlc_setServo(servo_pin[j], in_value[j]);
        delayMicroseconds(servo_speed);
      }
      Tlc.update();
    }
    delayMicroseconds(action_delay);
  }
}
/********************************************************-------分割线--------****************************************************/
//初始化函数
void setup() {
  Serial.begin(9600);     //开启串口通信，波特率9600
  Tlc.init(0);
  tlc_initServos(); 
  act_length();
  delay(action_delay);
}

//主函数，跳舞
void loop() {
    servo_move(action_dance, 2);
    delay(100);
}
