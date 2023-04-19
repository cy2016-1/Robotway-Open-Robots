#define SERVOLEFTNULL 500
#define SERVORIGHTNULL 500

#define SERVOFAKTORLEFT 603
#define SERVOFAKTORRIGHT 610

#define LIFT0 2000
#define LIFT1 1800
#define LIFT2 1400

#define SERVOPINLEFT 4
#define SERVOPINRIGHT 7
#define SERVOPINLIFT 11

#define LIFTSPEED 1500

#define L1 90
#define L2 117.6
#define L3 31.6

#define X1 40.0
#define Y1 -42
#define X2 111.4
#define Y2 -42

int initialx = 57,initialy = 93;


#include <Servo.h>

int servoLift = LIFT2;

Servo servo1;
Servo servo2;
Servo servo3;

volatile double lastX = initialx;
volatile double lastY = initialy;

//int last_min = 0;

void setup() {
  Serial.begin(9600);

  
}

void loop() {
  
  Serial.println("begin");
  
  if(1)
  {  
    
    if(!servo1.attached()) servo1.attach(SERVOPINLEFT);
    if(!servo2.attached()) servo2.attach(SERVOPINRIGHT);
    if(!servo3.attached()) servo3.attach(SERVOPINLIFT);
    
   
   number(45,110,1,1);
   number(60,110,3,1);
   number(70,110,11,1);
   number(80,110,1,1);
   number(95,110,4,1);
 
    /*
    ////////
    drawTo(0,120.0);
    delay(1000);
    
    Serial.println("----------------------");
    
    drawTo(140.0, 120.0);
    delay(1000);
    ///////
    */
    
    lift(2);
       
    servo1.detach();
    servo2.detach();
    servo3.detach();    
    
    
    Serial.println("end");
    
  }
  
}

void number(float bx, float by, int num, float scale) {

  switch (num) {

  case 0:
    drawTo(bx + 12 * scale, by + 6 * scale);
    lift(0);
    bogenGZS(bx + 7 * scale, by + 10 * scale, 10 * scale, -0.8, 6.7, 0.5);
    lift(1);
    break;
  case 1:

    drawTo(bx + 3 * scale, by + 15 * scale);
    lift(0);
    drawTo(bx + 10 * scale, by + 20 * scale);
    drawTo(bx + 10 * scale, by + 0 * scale);
    lift(1);
    break;
  case 2:
    drawTo(bx + 2 * scale, by + 12 * scale);
    lift(0);
    bogenUZS(bx + 8 * scale, by + 14 * scale, 6 * scale, 3, -0.8, 1);
    drawTo(bx + 1 * scale, by + 0 * scale);
    drawTo(bx + 12 * scale, by + 0 * scale);
    lift(1);
    break;
  case 3:
    drawTo(bx + 2 * scale, by + 17 * scale);
    lift(0);
    bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 3, -2, 1);
    bogenUZS(bx + 5 * scale, by + 5 * scale, 5 * scale, 1.57, -3, 1);
    lift(1);
    break;
  case 4:
    drawTo(bx + 10 * scale, by + 0 * scale);
    lift(0);
    drawTo(bx + 10 * scale, by + 20 * scale);
    drawTo(bx + 2 * scale, by + 6 * scale);
    drawTo(bx + 14 * scale, by + 6 * scale);
    lift(1);
    break;
  case 5:
    drawTo(bx + 2 * scale, by + 5 * scale);
    lift(0);
    bogenGZS(bx + 5 * scale, by + 6 * scale, 6 * scale, -2.5, 2, 1);
    drawTo(bx + 5 * scale, by + 20 * scale);
    drawTo(bx + 12 * scale, by + 20 * scale);
    lift(1);
    break;
  case 6:
    drawTo(bx + 2 * scale, by + 10 * scale);
    lift(0);
    bogenUZS(bx + 7 * scale, by + 6 * scale, 6 * scale, 2, -4.4, 1);
    drawTo(bx + 11 * scale, by + 20 * scale);
    lift(1);
    break;
  case 7:
    drawTo(bx + 2 * scale, by + 20 * scale);
    lift(0);
    drawTo(bx + 12 * scale, by + 20 * scale);
    drawTo(bx + 2 * scale, by + 0);
    lift(1);
    break;
  case 8:
    drawTo(bx + 5 * scale, by + 10 * scale);
    lift(0);
    bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 4.7, -1.6, 1);
    bogenGZS(bx + 5 * scale, by + 5 * scale, 5 * scale, -4.7, 2, 1);
    lift(1);
    break;

  case 9:
    drawTo(bx + 9 * scale, by + 11 * scale);
    lift(0);
    bogenUZS(bx + 7 * scale, by + 15 * scale, 5 * scale, 4, -0.5, 1);
    drawTo(bx + 5 * scale, by + 0);
    lift(1);
    break;

  case 111:

    lift(0);
    drawTo(initialx, initialy);
    drawTo(58, 42);

    drawTo(58, 45);
    drawTo(2, 45);
    drawTo(2, 41);
    drawTo(58, 41);
    drawTo(60, 37);

    drawTo(2, 37);
    drawTo(2, 33);
    drawTo(60, 33);
    drawTo(60, 29);

    drawTo(2, 29);
    drawTo(2, 25);
    drawTo(60, 25);
    drawTo(60, 20);

    drawTo(2, 20);
    drawTo(60, initialy);

    drawTo(initialx + 3 , initialy);
    lift(2);

    break;

  case 11:
    drawTo(bx + 5 * scale, by + 15 * scale);
    lift(0);
    bogenGZS(bx + 5 * scale, by + 15 * scale, 0.1 * scale, 1, -1, 1);
    lift(1);
    drawTo(bx + 5 * scale, by + 5 * scale);
    lift(0);
    bogenGZS(bx + 5 * scale, by + 5 * scale, 0.1 * scale, 1, -1, 1);
    lift(1);
    break;

  }
}


void lift(char lift)
{
  switch(lift)
  {
    case 0:
        Serial.println("lift0");
        if(servoLift >= LIFT0)
        {
          while(servoLift >= LIFT0)
          {
            servoLift--;
            servo3.writeMicroseconds(servoLift);
            delayMicroseconds(LIFTSPEED);
          }
        }
        else
        {
           while(servoLift <= LIFT0)
           {
             servoLift++;
             servo3.writeMicroseconds(servoLift);
             delayMicroseconds(LIFTSPEED);
           }
        }
    break;
    case 1:
        Serial.println("lift1");
        if(servoLift >= LIFT1)
        {
          while(servoLift >= LIFT1)
          {
            servoLift--;
            servo3.writeMicroseconds(servoLift);
            delayMicroseconds(LIFTSPEED);
          }
        }
        else
        {
          while(servoLift <= LIFT1)
          {
            servoLift++;
            servo3.writeMicroseconds(servoLift);
            delayMicroseconds(LIFTSPEED);
          }
        }
    break;
    case 2:
        Serial.println("lift2");
        if(servoLift >= LIFT2)
        {
          while(servoLift >= LIFT2)
          {
            servoLift--;
            servo3.writeMicroseconds(servoLift);
            delayMicroseconds(LIFTSPEED);
          }
        }
        else
        {
          while(servoLift <= LIFT2)
          {
            servoLift++;
            servo3.writeMicroseconds(servoLift);
            delayMicroseconds(LIFTSPEED);
          }
        }
    break;
    default:break;
  }
}

void bogenUZS(float bx, float by, float radius, int start, int ende, float sqee) {
  float inkr = -0.05;
  float count = 0;

  do {
    drawTo(sqee * radius * cos(start + count) + bx,
    radius * sin(start + count) + by);
    count += inkr;
  } 
  while ((start + count) > ende);

}

//cos？sin？
void bogenGZS(float bx, float by, float radius, int start, int ende, float sqee) {
  float inkr = 0.05;
  float count = 0;

  do {
    drawTo(sqee * radius * cos(start + count) + bx,
    radius * sin(start + count) + by);
    count += inkr;
  } 
  while ((start + count) <= ende);
}

void drawTo(double pX, double pY) {
  double dx, dy, c;
  int i;
  
  Serial.println(pX);
  Serial.println(pY);

  // dx dy of new point
  dx = pX - lastX;
  dy = pY - lastY;
  //path lenght in mm, times 4 equals 4 steps per mm
  c = floor(5 * sqrt(dx * dx + dy * dy));

  if (c < 1) c = 1;

  for (i = 0; i <= c; i++) {
    // draw line point by point
    set_XY(lastX + (i * dx / c), lastY + (i * dy / c));

  }

  lastX = pX;
  lastY = pY;
}


double return_angle(double a, double b, double c) {
  // cosine rule for angle between c and a
  return acos((a * a + c * c - b * b) / (2 * a * c));
}


//用各种三角函数把位置坐标换算成舵机的角度
//http://www.thingiverse.com/thing:248009/
void set_XY(double Tx, double Ty) 
{
  delay(1);
  double dx, dy, c, a1, a2, Hx, Hy;

  // calculate triangle between pen, servoLeft and arm joint
  // cartesian dx/dy
  dx = Tx - X1;
  dy = Ty - Y1;

  // polar lemgth (c) and angle (a1)
  c = sqrt(dx * dx + dy * dy); // 
  a1 = atan2(dy, dx); //
  a2 = return_angle(L1, L2, c);
  
  //Serial.println(floor(((M_PI-a1 - a2) * SERVOFAKTORLEFT) + SERVOLEFTNULL));

  servo1.writeMicroseconds(floor(((M_PI-a1 - a2) * SERVOFAKTORLEFT) + SERVOLEFTNULL));

  // calculate joinr arm point for triangle of the right servo arm
  a2 = return_angle(L2, L1, c);
  Hx = Tx + L3 * cos((a1 - a2 + 0.621) + M_PI); //36,5掳
  Hy = Ty + L3 * sin((a1 - a2 + 0.621) + M_PI);

  // calculate triangle between pen joint, servoRight and arm joint
  dx = Hx - X2;
  dy = Hy - Y2;

  c = sqrt(dx * dx + dy * dy);
  a1 = atan2(dy, dx);
  a2 = return_angle(L1, (L2 - L3), c);
  
  //Serial.println(floor(((M_PI - a1 + a2) * SERVOFAKTORRIGHT) + SERVORIGHTNULL));

  servo2.writeMicroseconds(floor(((M_PI - a1 + a2) * SERVOFAKTORRIGHT) + SERVORIGHTNULL));

}

