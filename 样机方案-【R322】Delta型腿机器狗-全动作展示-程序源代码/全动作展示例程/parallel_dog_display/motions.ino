/***** 独立动作相关代码 *****/

/***** 大狗初始化 *****/
void dogInit()
{
  //4个肩部舵机初始位置
  tlc_setServo(LEG1_S4, Leg1_S4Pos);
  tlc_setServo(LEG2_S4, Leg2_S4Pos);
  tlc_setServo(LEG3_S4, Leg3_S4Pos);
  tlc_setServo(LEG4_S4, Leg4_S4Pos);

  //4腿复位，延时1s
  dogReset({0, 0, Leg_Init_Z_Pos}, 1000);
}

/*****
  复位动作
  initPos  : 4腿复位位置
  waitTime : 复位后等待时间,ms
*****/
void dogReset(Point3d initPos, uint waitTime)
{
  calc(initPos, 1, 1, 1, 1);
  Tlc.update();
  delay(waitTime);
}

/*****
  蹲起动作
  (x,y) : 4腿水平投影位置
  z1    : 4腿最低位置
  z2	  : 4腿最高位置
  times : 动作次数
*****/
void upDown(float x, float y, float z1, float z2, uint times)
{
  //动作速度设置常量
  static const float dz = 0.2; //单次运动幅度0.2mm
  static const uint dt = 10; //单次动作间隔10ms
  //动作计数器
  uint count = 0;
  dogReset({x, y, z1}, 200);
  while (count++ < times)
  {
    for (float z = z1; z <= z2; z += dz)
    {
      calc({x, y, z}, 1, 1, 1, 1);
      Tlc.update();
      delay(dt);
    }
    for (float z = z2; z >= z1; z -= dz)
    {
      calc({x, y, z}, 1, 1, 1, 1);
      Tlc.update();
      delay(dt);
    }
  }
}

/*****
  原地圆形摆动动作
  (ox,oy): 4腿圆形轨迹圆心
  z      : 4腿高度
  r      : 4腿圆形轨迹半径
  times  : 动作次数
*****/
void drawCircle(float ox, float oy, float z, float r, uint times)
{
  //动作速度设置常量
  static const float dRad = 0.1; //单次动作弧度增量0.1rad
  static const uint dt  = 80; //单次动作间隔10ms
  //动作计数器
  uint count = 0;
  dogReset({ 0, 0, z}, 200);
  while (count++ < times) {
    for (float a = -M_PI; a <= M_PI; a += dRad)
    {
      float x = ox + r * cos(a);
      float y = oy + r * sin(a);
      calc({x, y, z}, 1, 1, 0, 0);
      calc({ -x, -y, z}, 0, 0, 1, 1);
      Tlc.update();
      delay(dt);
    }
  }
}

/*****
  原地踏步动作
  (x,y) : 4腿水平投影位置
  z1    : 4腿最低位置
  z2    : 4腿最高位置
  times : 动作次数
*****/
void stepping(float x, float y, float z1, float z2, uint times)
{
  static const float dz = 2; //单次运动幅度2mm
  static const uint dt = 5; //单次动作间隔5ms
  float z;
  uint count = 0;
  dogReset({x, y, z1}, 200);
  while (count < times) {
    count += 1;
    for (z = z1; z <= z2; z += dz)
    {
      calc({x, y, z}, 1, 0, 0, 1);
      Tlc.update();
      delay(dt);
    }
    for (z = z2; z >= z1; z -= dz)
    {
      calc({x, y, z}, 1, 0, 0, 1);
      Tlc.update();
      delay(dt);
    }
    for (z = z1; z <= z2; z += dz)
    {
      calc({x, y, z}, 0, 1, 1, 0);
      Tlc.update();
      delay(dt);
    }
    for (z = z2; z >= z1; z -= dz)
    {
      calc({x, y, z}, 0, 1, 1, 0);
      Tlc.update();
      delay(dt);
    }
  }
}

/*****
  原地摆臂动作
  height : 摆臂高度(肩部舵机抬升角度)
  times  : 摆臂次数
******/
void liftShoulder(uint height, uint times)
{
  static const uint dt = 30; //单次动作间隔30ms
  uint count = 0;
  uint pos, i;
  for(uint count = 0; count < times; count++)
  {
    //lift leg1
    dogReset({0, 0, -140}, 500);
    calc({30, 20, -140}, 0, 1, 0, 0);
    calc({ -30, -20, -140}, 0, 0, 1, 0);
    calc({ -30, -20, -120}, 0, 0, 0, 1);
    Tlc.update();
    delay(1000);
    for (pos = Leg1_S4Pos, i = 0; i < height; pos--, i++)
    {
      tlc_setServo(LEG1_S4, pos);
      Tlc.update();
      delay(dt);
    }
    for (i = 0; i < height; pos++, i++)
    {
      tlc_setServo(LEG1_S4, pos);
      Tlc.update();
      delay(dt);
    }
    // lift leg3
    dogReset({0, 0, -140}, 500);
    calc({30, 20, -140}, 1, 0, 0, 0);
    calc({ -30, -20, -140}, 0, 0, 0, 1);
    calc({30, -20, -110}, 0, 1, 0, 0);
    Tlc.update();
    delay(1000);
    for (pos = Leg3_S4Pos, i = 0; i < height; pos++, i++)
    {
      tlc_setServo(LEG3_S4, pos);
      Tlc.update();
      delay(dt);
    }
    for (i = 0; i < height; pos--, i++)
    {
      tlc_setServo(LEG3_S4, pos);
      Tlc.update();
      delay(dt);
    }
    //lift leg2
    dogReset({0, 0, -140}, 500);
    calc({30, 20, -140}, 0, 0, 0, 1);
    calc({ -30, -20, -140}, 1, 0, 0, 0);
    calc({30, -20, -120}, 0, 0, 1, 0);
    Tlc.update();
    delay(1000);
    for (pos = Leg2_S4Pos, i = 0; i < height; pos++, i++)
    {
      tlc_setServo(LEG2_S4, pos);
      Tlc.update();
      delay(dt);
    }
    for (i = 0; i < height; pos--, i++)
    {
      tlc_setServo(LEG2_S4, pos);
      Tlc.update();
      delay(dt);
    }
    //lift leg4
    dogReset({0, 0, -140}, 500);
    calc({30, 20, -140}, 0, 0, 1, 0);
    calc({ -30, -20, -140}, 0, 1, 0, 0);
    calc({ -30, -20, -100}, 1, 0, 0, 0);
    Tlc.update();
    delay(1000);
    for (pos = Leg4_S4Pos, i = 0; i < height; pos--, i++)
    {
      tlc_setServo(LEG4_S4, pos);
      Tlc.update();
      delay(dt);
    }
    for (i = 0; i < height; pos++, i++)
    {
      tlc_setServo(LEG4_S4, pos);
      Tlc.update();
      delay(dt);
    }
  }
}
