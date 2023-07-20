/***** 陀螺仪/原地及行进间平衡姿态调节相关代码 *****/

unsigned char _msgBuf[11]; //陀螺仪消息缓存
unsigned char _msgSgn = 0; //接收完整消息标志位

//原地平衡调节时4条腿高度
float _legZPos1 = Leg_Init_Z_Pos;
float _legZPos2 = Leg_Init_Z_Pos;
float _legZPos3 = Leg_Init_Z_Pos;
float _legZPos4 = Leg_Init_Z_Pos;

//行进间平衡调节时4条腿轨迹位置高度
float _trackZPos1 = 0;
float _trackZPos2 = 0;
float _trackZPos3 = 0;
float _trackZPos4 = 0;

int pitchStat(double pitchAngle); //俯仰角倾斜状态
int rollingStat(double rollingAngle); //翻转角倾斜状态

float getTrackZPos(uint index)
{
  switch (index) {
      case 1:
        return _trackZPos1;
        break;
      case 2:
        return _trackZPos2;
        break;
      case 3:
        return _trackZPos3;
        break;
      case 4:
        return _trackZPos4;
        break;
      default:
        break;
  }
  return 0;
}

//平衡调节状态
uint _adjustStat = ADJUST_STAT_OFF;

void switchAdjustStat(uint stat)
{
  _adjustStat = stat;
  if(stat == ADJUST_STAT_TRACK)
  {
    _trackZPos1 = _trackZPos2 = _trackZPos3 = _trackZPos4 = 0;
  } else if(stat == ADJUST_STAT_LEG)
  {
    _legZPos1 = _legZPos2 = _legZPos3 = _legZPos4 = Leg_Init_Z_Pos;
  }
}

//串口读取陀螺仪消息
void readGyroSerial()
{
  static uint _bufIndex = 0; // 缓存下标位置
  while (Serial.available()) {
    _msgBuf[_bufIndex] = (unsigned char)Serial.read();
    if (_bufIndex == 0 && _msgBuf[0] != 0x55) continue; //第0号数据不是帧头
    _bufIndex++;
    if (_bufIndex == 11)          //接收到11个数据
    {
      _bufIndex = 0;             //重新赋值，准备下一帧数据的接收
      _msgSgn = 1;
    }
  }
}

void adjustAct() {
  static unsigned long lastAdjustTime = millis(); // 前一次调节时间,ms
  if (_msgSgn)
  {
    _msgSgn = 0;

    //如果不需要调节或与前一次调节间隔时间过短，直接返回
    if ( !_adjustStat ||  millis() - lastAdjustTime <= ADJUST_DELTA_TIME) return; 

    //更新调节时间
    lastAdjustTime = millis();
    
    if (_msgBuf[0] == 0x55 && _msgBuf [1] == 0x53)   //检查帧头
    {
      double pitchAngle = (short(_msgBuf [3] << 8 | _msgBuf [2])) / 32768.0 * 180; //俯仰角
      double rollingAngle = (short(_msgBuf [5] << 8 | _msgBuf [4])) / 32768.0 * 180; //翻转角
      // double courseAngle = (short(_msgBuf [7] << 8 | _msgBuf [6])) / 32768.0 * 180; //航向角
      // double temperature = (short(_msgBuf [9] << 8 | _msgBuf [8])) / 340.0 + 36.25; //温度

      if (!pitchStat(pitchAngle) && !rollingStat(rollingAngle))
      {
        return;
      }

      if (pitchStat(pitchAngle) <= 0 && rollingStat(rollingAngle) >= 0 )
      {
        if (_adjustStat == ADJUST_STAT_TRACK)
        {
          if (_trackZPos4 < Track_Adjust_Max_Z) _trackZPos4 += Track_Adjust_Delta_Z;
          if (_trackZPos1 > Track_Adjust_Min_Z) _trackZPos1 -= Track_Adjust_Delta_Z;
        }
        else if (_adjustStat == ADJUST_STAT_LEG)
        {
          if (_legZPos4 < LEG_Adjust_Max_Z)_legZPos4 += Leg_Adjust_Delta_Z;
          if (_legZPos1 > Leg_Adjust_Min_Z)_legZPos1 -= Leg_Adjust_Delta_Z;
          calc({0, 0, _legZPos1}, 1, 0, 0, 0);
          calc({0, 0, _legZPos4}, 0, 0, 0, 1);
        }
      }
      if (pitchStat(pitchAngle) <= 0 && rollingStat(rollingAngle) <= 0 )
      {
        if (_adjustStat == ADJUST_STAT_TRACK)
        {
          if (_trackZPos2 > Track_Adjust_Min_Z) _trackZPos2 -= Track_Adjust_Delta_Z;
          if (_trackZPos3 < Track_Adjust_Max_Z) _trackZPos3 += Track_Adjust_Delta_Z;
        }
        else if (_adjustStat == ADJUST_STAT_LEG)
        {
          if (_legZPos2 > Leg_Adjust_Min_Z) _legZPos2 -= Leg_Adjust_Delta_Z;
          if (_legZPos3 < LEG_Adjust_Max_Z) _legZPos3 += Leg_Adjust_Delta_Z;
          calc({0, 0, _legZPos2}, 0, 1, 0, 0);
          calc({0, 0, _legZPos3}, 0, 0, 1, 0);
        }
      }
      if (pitchStat(pitchAngle) >= 0 && rollingStat(rollingAngle) >= 0 )
      {
        if (_adjustStat == ADJUST_STAT_TRACK)
        {
          if (_trackZPos3 > Track_Adjust_Min_Z) _trackZPos3 -= Track_Adjust_Delta_Z;
          if (_trackZPos2 < Track_Adjust_Max_Z) _trackZPos2 += Track_Adjust_Delta_Z;
        }
        else if (_adjustStat == ADJUST_STAT_LEG)
        {
          if (_legZPos3 > Leg_Adjust_Min_Z) _legZPos3 -= Leg_Adjust_Delta_Z;
          if (_legZPos2 < LEG_Adjust_Max_Z) _legZPos2 += Leg_Adjust_Delta_Z;
          calc({0, 0, _legZPos2}, 0, 1, 0, 0);
          calc({0, 0, _legZPos3}, 0, 0, 1, 0);
        }
      }
      if (pitchStat(pitchAngle) >= 0 && rollingStat(rollingAngle) <= 0 )
      {
        if (_adjustStat == ADJUST_STAT_TRACK)
        {
          if (_trackZPos1 < Track_Adjust_Max_Z) _trackZPos1 += Track_Adjust_Delta_Z;
          if (_trackZPos4 > Track_Adjust_Min_Z) _trackZPos4 -= Track_Adjust_Delta_Z;
        }
        else if (_adjustStat == ADJUST_STAT_LEG)
        {
          if (_legZPos1 < LEG_Adjust_Max_Z) _legZPos1 += Leg_Adjust_Delta_Z;
          if (_legZPos4 > Leg_Adjust_Min_Z ) _legZPos4 -= Leg_Adjust_Delta_Z;
          calc({0, 0, _legZPos1}, 1, 0, 0, 0);
          calc({0, 0, _legZPos4}, 0, 0, 0, 1);
        }
      }
      Tlc.update();
    }
  }
}

/***** 俯仰角倾斜状态 *****/
int pitchStat(double pitchAngle)
{
  if (pitchAngle > Balence_Range) return 1;
  else if (pitchAngle < -Balence_Range) return -1;
  else return 0;
}
/***** 翻转角倾斜状态 *****/
int rollingStat(double rollingAngle)
{
  if (rollingAngle > Balence_Range) return 1;
  else if (rollingAngle < -Balence_Range) return -1;
  else return 0;
}
