/*****腿部运动轨迹计算及控制相关代码*****/

bool _turnLeftFlag = false; // 左转状态标记
bool _turnRightFlag = false; // 右转状态标记
void setTurnLeftFlag(bool flag)
{
  _turnLeftFlag = flag;
}
void setTurnRightFlag(bool flag)
{
  _turnRightFlag = flag;
}

//4条腿在轨迹中的当前时间
uint leg1Time = 0;
uint leg2Time = Track_Cycle / 2.0;
uint leg3Time = Track_Cycle / 2.0;
uint leg4Time = 0;

/***** 
差值计算t时刻腿部应在矩形轨迹中的位置
_start : 矩形轨迹左下角，轨迹起点
_end : 矩形轨迹右上角
*****/
struct Point3d calcPoint(int t , Point3d _start , Point3d _end)
{
  float x = 0, y = 0, z = 0;

  if (t >= 0 && t < track_t1)
  {
    x = _start.x;
    y = _start.y;
    z = _start.z + (_end.z - _start.z)  * t / track_t1;
    return {x, y, z};
  }
  else if (t >= track_t1 && t < track_t2)
  {
    x = _start.x + (_end.x - _start.x) * (t - track_t1) / (track_t2 - track_t1);
    y = _start.y + (_end.y - _start.y) * (t - track_t1) / (track_t2 - track_t1);
    z = _end.z;
    return {x, y, z};
  }
  else if (t >= track_t2 && t < track_t3)
  {
    x = _end.x;
    y = _end.y;
    z = _end.z - (_end.z - _start.z) * (t - track_t2) / (track_t3 - track_t2);
    return {x, y, z};
  }
  else if (t >= track_t3 && t < track_t4)
  {
    x = _end.x - (_end.x - _start.x) * (t - track_t3) / (track_t4 - track_t3);
    y = _end.y - (_end.y - _start.y) * (t - track_t3) / (track_t4 - track_t3);
    z = _start.z;
    return {x, y, z};
  }
}

//按当前运动状态及时间t得到各腿的位置
struct Point3d getPos(int t)
{
  Point3d time_point;
  switch (currentMode) {
    case DOG_MODE_FRONT:
      time_point = calcPoint(t, { track_x1, 0.0, track_z1}, {track_x2, 0.0, track_z2});
      break;
    case DOG_MODE_BACK:
      time_point = calcPoint(t, {track_x2, 0, track_z1}, { track_x1, 0, track_z2});
      break;
    case DOG_MODE_LEFT:
      time_point = calcPoint(t, {0, track_y1, track_z1}, {0, track_y2, track_z2});
      break;
    case DOG_MODE_RIGHT:
      time_point = calcPoint(t, {0, track_y2, track_z1}, {0, track_y1, track_z2});
      break;
    case DOG_MODE_LEFT_FRONT:
      time_point = calcPoint(t, { track_x3, track_y1, track_z1}, {track_x4, track_y2, track_z2});
      break;
    case DOG_MODE_RIGHT_FRONT:
      time_point = calcPoint(t, { track_x3, track_y2, track_z1}, {track_x4, track_y1, track_z2});
      break;
    case DOG_MODE_LEFT_BACK:
      time_point = calcPoint(t, {track_x4, track_y1, track_z1}, { track_x3, track_y2, track_z2});
      break;
    case DOG_MODE_RIGHT_BACK:
      time_point = calcPoint(t, {track_x4, track_y2, track_z1}, { track_x3, track_y1, track_z2});
      break;
    case DOG_MODE_TURN_LEFT:
      _turnLeftFlag = true;
      break;
    case DOG_MODE_TURN_RIGHT:
      _turnRightFlag = true;
      break;
    default:
      break;
  }
  return time_point;
}

void leg1() {
  if (_turnLeftFlag) currentMode = DOG_MODE_LEFT_BACK; // trick
  else if (_turnRightFlag) currentMode = DOG_MODE_RIGHT_FRONT; // trick

  if (leg1Time == Track_Cycle) {
    updateCycleCount(); //第一条腿完成一周期后认为动作完成一整个周期
    leg1Time = 0;
  }
  leg1Time++;

  Point3d pos = getPos(leg1Time);
  calc({pos.x, pos.y, pos.z + getTrackZPos(1)}, 1, 0, 0, 0);
}
void leg2() {
  if (_turnLeftFlag) currentMode = DOG_MODE_RIGHT_BACK; // trick
  else if (_turnRightFlag) currentMode = DOG_MODE_LEFT_FRONT; // trick

  if (leg2Time == Track_Cycle) leg2Time = 0;
  leg2Time++;

  Point3d pos = getPos(leg2Time);
  calc({pos.x, pos.y, pos.z + getTrackZPos(2)}, 0, 1, 0, 0);
}

void leg3() {
  if (_turnLeftFlag) currentMode = DOG_MODE_LEFT_FRONT; // trick
  else if (_turnRightFlag) currentMode = DOG_MODE_RIGHT_BACK; // trick

  if (leg3Time == Track_Cycle) leg3Time = 0;
  leg3Time++;

  Point3d pos = getPos(leg3Time);
  calc({-pos.x, -pos.y, pos.z + getTrackZPos(3)}, 0, 0, 1, 0);
}

void leg4() {
  if (_turnLeftFlag) currentMode = DOG_MODE_RIGHT_FRONT; // trick
  else if (_turnRightFlag) currentMode = DOG_MODE_LEFT_BACK; // trick

  if (leg4Time == Track_Cycle) leg4Time = 0;
  leg4Time++;

  Point3d pos = getPos(leg4Time);
  calc({-pos.x, -pos.y, pos.z + getTrackZPos(4)}, 0, 0, 0, 1);
}



