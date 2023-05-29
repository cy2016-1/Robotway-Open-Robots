#ifndef _LEG_H_
#define _LEG_H_

#include <Arduino.h>
#include <Servo.h>
#include <math.h>

const float L1 = 0.0896; // outer upper leg length(m)
const float L2 = 0.03;   // inner upper leg length(m)
const float L3 = 0.09;   // adjustable link length(m)
const float L4 = 0.1;    // lower leg length(m)
const float LPos = 0.04; // link length from upper leg(m)

/********** graphical algorithms **********/
struct point2d
{
  float x;
  float y;
  void print() {
    Serial.print("x=");
    Serial.print(x);
    Serial.print(", y=");
    Serial.println(y);
  }
};

#define DISTANCE(x1, y1, x2, y2) sqrt( \
    ((x1) - (x2)) * ((x1) - (x2)) +    \
    ((y1) - (y2)) * ((y1) - (y2)))

int circleIntersections(point2d o1, point2d o2, float r1, float r2, point2d &p1, point2d &p2) {
  float d = DISTANCE(o1.x, o1.y, o2.x, o2.y);
  if (d == 0)
  {
    return 1;
  }
  if (d > (r1 + r2))
  {
    return 2;
  }
  if (d < r1 - r2 || d < r2 - r1)
  {
    return 3;
  }
  float a = (r1 * r1 - r2 * r2 + d * d) / 2.0 / d;
  float h = sqrt(r1 * r1 - a * a);
  float tx = o1.x + a * (o2.x - o1.x) / d;
  float ty = o1.y + a * (o2.y - o1.y) / d;
  p1.x = tx + h * (o2.y - o1.y) / d;
  p1.y = ty - h * (o2.x - o1.x) / d;
  p2.x = tx - h * (o2.y - o1.y) / d;
  p2.y = ty + h * (o2.x - o1.x) / d;
  return 0;
}

#define RAD_TO_DEGREE(d) ((d)*180.0 / M_PI)

int cartesianToAlphaBeta(float x, float y, int leg_dirction, float &alpha, float &beta) {  
  point2d foot_pos = {x, y}, origin = {0, 0};
  point2d i1, i2;
  if (!circleIntersections(origin, foot_pos, L1, L4, i1, i2)) {
    alpha = atan2(i2.x, i2.y);
    point2d intersection;
    intersection.x = i2.x + (foot_pos.x - i2.x) / L4 * LPos;
    intersection.y = i2.y + (foot_pos.y - i2.y) / L4 * LPos;
    if (!circleIntersections(origin, intersection, L2, L3, i1, i2)) {
      beta = atan2(i1.x, i1.y);
      return 0;
    }
  }
  return 1;
}



/********** leg controller **********/
class Leg {
 public:
  Leg(int opin, int ipin, int mido, int midi, int dir, int pos) {
    _outer_servo.attach(opin);
    _inner_servo.attach(ipin);
    _mido = mido;
    _midi = midi;
    _outer_servo.writeMicroseconds(_mido);
    _inner_servo.writeMicroseconds(_midi);
    _direction = dir;
    _position = pos;
  }

  void initPos(){
    footPos(0, 0.13);
  }

 void write(float alpha, float beta) {
   alpha = RAD_TO_DEGREE(alpha);
   beta = RAD_TO_DEGREE(beta);
   float pwo = _mido + _direction*alpha / 135.0 *1000.0;
   float pwi = _midi + _direction*beta / 135.0 * 1000.0;
   _outer_servo.writeMicroseconds(pwo);
   _inner_servo.writeMicroseconds(pwi);
 }

 void footPos(float x, float y)
 {
   float alpha, beta;
   cartesianToAlphaBeta(x*_position, y, 1, alpha, beta);//笛卡尔到阿尔法贝塔
   write(alpha, beta);
   _cur_x = x;
   _cur_y = y;
 }

 void up(float delta = 0.003, float threshold = 0.10) {
   if (_cur_y - delta >= threshold) _cur_y -= delta;
 }
 void down(float delta = 0.003, float threshold = 0.16) {
   if (_cur_y + delta <= threshold) _cur_y += delta;
 }
 void back(float delta = 0.002, float threshold = -0.05) {
   if (_cur_x - delta >= threshold) _cur_x -= delta;
 }
 void front(float delta = 0.002, float threshold = 0.05) {
   if (_cur_x + delta <= threshold) _cur_x += delta;
 }
 void updatePos() {
   footPos(_cur_x, _cur_y);
 }

 private:
  Servo _outer_servo;
  Servo _inner_servo;
  int _mido;
  int _midi;
  int _direction;
  int _position;
  float _cur_x;
  float _cur_y;
};

Leg leg0(4, A0, 1600, 1480, -1, -1);
Leg leg1(7, A2, 1450, 1480, 1, -1);
Leg leg2(3, 8, 1550, 1450, 1, 1);
Leg leg3(12, 11, 1450, 1450, -1, 1);

#endif
