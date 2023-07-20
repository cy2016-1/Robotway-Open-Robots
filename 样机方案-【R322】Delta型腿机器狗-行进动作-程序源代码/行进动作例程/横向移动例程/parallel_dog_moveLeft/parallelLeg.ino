/*****
并联腿部逆解计算相关代码

已知：(单位mm)
给定的脚部空间位置Fo(x,y,z)
与舵机相连的连杆长度l1 = 60
与脚底相连的连杆长度l2 = 105
x-z平面(y=0)内两对称的舵机轴简化位置：O1(20,0,0),O2(-20,0,0)
y-z平面(x=0)内的舵机轴简化位置：O3(0, 40, 0)

计算1号舵机舵角：
圆<Fo,l2><O1,l1>的交点，取x值较大的点
计算2号舵机舵角：
圆<Fo,l2><O2,l1>的交点，取x值较小的点
计算3号舵机舵角：
圆<Fo,l2><O3,l1>的交点，取y值较大的点

*****/


//计算平面两点距离
double distance(double x1, double y1, double x2, double y2)
{
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

//计算<o1,r1>,<o2,r2>两圆交点坐标i1,i2
bool intersection(Point o1, Point o2, double r1, double r2, Point &i1, Point &i2)
{
  double d = distance(o1.x, o1.y, o2.x, o2.y);
  if (d == 0) return false;
  if (d > (r1 + r2)) return false;
  if (d < r1 - r2 || d < r2 - r1) return false;

  double a = (r1 * r1 - r2 * r2 + d * d) / 2.0 / d;
  double h = sqrt(r1 * r1 - a * a);
  double tx = o1.x + a * (o2.x - o1.x) / d;
  double ty = o1.y + a * (o2.y - o1.y) / d;
  i1.x = tx + h * (o2.y - o1.y) / d;
  i1.y = ty - h * (o2.x - o1.x) / d;
  i2.x = tx - h * (o2.y - o1.y) / d;
  i2.y = ty + h * (o2.x - o1.x) / d;
  return true;
}

//简化模型中三个舵机轴的初始位置
const Point o1 = {20, 0}; // 在x-z平面(y=0)内的平面坐标 x = 20, z = 0
const Point o2 = { -20, 0}; // 在x-z平面(y=0)内的平面坐标 x = -20, z = 0
const Point o3 = {40, 0}; // 在y-z平面(x=0)内的平面坐标 y = 40, z = 0

const float l1 = 60;
const float l2 = 105;

//逆解计算，由脚底坐标计算出舵机位置
bool calc(Point3d p, bool leg1, bool leg2, bool leg3, bool leg4)
{
  int s1, s2, s3;
  bool ret = true;
  Point i1, i2, i3, ti;
  //x-z
  float rxz = sqrt(l2 * l2 - p.y * p.y);
  Point oxz = {p.x, p.z};
  ret = intersection(o1, oxz, l1, rxz, ti, i1);
  if (!ret) return false;
  ret = intersection(o2, oxz, l1, rxz, i2, ti);
  if (!ret) return false;
  //y-z
  float ryz = sqrt(l2 * l2 - p.x * p.x);
  Point oyz = {p.y, p.z};
  ret = intersection(o3, oyz, l1, ryz, ti, i3);
  if (!ret) return false;

  s1 = atan2(i1.y, i1.x) * 180.0 / M_PI;
  s2 = atan2(i2.y, -i2.x) * 180.0 / M_PI;
  s3 = atan2(i3.y, i3.x) * 180.0 / M_PI;

  if (leg1)
  {
    tlc_setServo(LEG1_S1, s1 + 90 - 15);
    tlc_setServo(LEG1_S2, 90 - s2 - 15);
    tlc_setServo(LEG1_S3, s3 + 90 - 10);
  }
  if (leg4)
  {
    tlc_setServo(LEG4_S1, s1 + 90 + 5);
    tlc_setServo(LEG4_S2, 90 - s2 - 15);
    tlc_setServo(LEG4_S3, s3 + 90);
  }
  if (leg2)
  {
    tlc_setServo(LEG2_S1, s1 + 90 + 0);
    tlc_setServo(LEG2_S2, 90 - s2 - 5);
    tlc_setServo(LEG2_S3, 90 - s3 - 10);
  }
  if (leg3)
  {
    tlc_setServo(LEG3_S1, s1 + 90 - 8);
    tlc_setServo(LEG3_S2, 90 - s2 - 12);
    tlc_setServo(LEG3_S3, 90 - s3 - 15);
  }

  return true;
}


