/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-03-31 https://www.robotway.com/
  ------------------------------*/
#define SERVOLEFTNULL 500      //左侧舵机转动到0度的值
#define SERVORIGHTNULL 500     //右侧舵机转动到0度的值

#define SERVOFAKTORLEFT 603    //左侧舵机转动到0度右侧舵机转动到90度时的值
#define SERVOFAKTORRIGHT 610   //左侧舵机转动到90度右侧舵机转动到180度时的值

#define LIFT0 2000             //落笔写字时舵机转动的值
#define LIFT1 1800             //一笔写完换笔时舵机转动的值
#define LIFT2 1400             //初始及完成写字后抬笔时舵机的值

#define SERVOPINLEFT 4         //定义一些舵机引脚
#define SERVOPINRIGHT 7
#define SERVOPINLIFT 11

#define LIFTSPEED 1500         //定义抬笔落笔时舵机转动的速度

#define L1 90                  //定义与舵机相连杆的长度 mm  
#define L2 117.6               //定义与舵机相连杆的端点铰接处中心到笔中心的距离 mm
#define L3 31.6                //定义中间杆顶端铰接处中心到笔的距离 mm

#define X1 40.0                //定义左侧舵机中心轴到原点在X方向上的距离
#define Y1 -42                 //定义左侧舵机中心轴到X轴的垂直距离
#define X2 111.4               //定义右侧舵机中心轴到原点在X方向上的距离
#define Y2 -42                 //定义右侧舵机中心轴到到X轴的垂直距离

//坐标系建立第一象限，X轴方向为140mm,Y轴方向为120mm，选取坐标点时Y值建议大于70
int coAry[10][10][2] = {         

              //汉字  王
              {{25,110},{0,0},{51,110},{1,1}},
              {{26,98},{0,0},{49,98},{1,1}},
              {{25,84},{0,0},{51,84},{1,1}},
              {{37,110},{0,0},{37,84},{1,1}},

              //汉字  云
              {{61,110},{0,0},{81,110},{1,1}},
              {{58,100},{0,0},{85,100},{1,1}},
              {{68,100},{0,0},{62,85},{86,85},{1,1}},
              {{80,96},{0,0},{91,82},{1,1}},
              
              //汉字  飞
              {{99,110},{0,0},{114,110},{114,98},{115,90},{115,86},{118,84},{121,82},{126,88},{1,1}},
              {{121,103},{0,0},{116,98},{122,94},{1,1}}
                          
};

#include <Servo.h>

int servoLift = LIFT2;

Servo servo1;
Servo servo2;
Servo servo3;

volatile double lastX = 57;   //笔初始坐标值
volatile double lastY = 93;

void setup() {
  Serial.begin(9600);        //开启串口通信
  
  /*servo1.attach(SERVOPINLEFT);
  servo2.attach(SERVOPINRIGHT);
  servo3.attach(SERVOPINLIFT);
  */
  
}

void loop() {
  
  Serial.println("begin");
  
  if(1)
  {  
    
    if(!servo1.attached()) servo1.attach(SERVOPINLEFT);
    if(!servo2.attached()) servo2.attach(SERVOPINRIGHT);
    if(!servo3.attached()) servo3.attach(SERVOPINLIFT);
    
    lift(2);
    //delay(1000);

    //汉字坐标处理
    for(int i=0;i<10;i++)
    {
      for(int j=0;j<10;j++)
      {
        int x = coAry[i][j][0];
        int y = coAry[i][j][1];
        
        //Serial.println(x);
        //Serial.println(y);
        
        if(x == 0 && y == 0)
        {
          lift(0);
          continue;
        }
        else if(x == 1 && y == 1)
        {
          lift(1);
          break;
        }
        
        drawTo(x,y);
       
       //delay(10);
        
      }
    }
   

    /*
    //摆臂测试坐标，左侧舵机转动到0度，右侧舵机转动到90度；左侧舵机转动到90度，右侧舵机转动到180度，依次循环
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

//抬笔舵机转动函数，三个动作，落笔、换笔、起笔, 0 ,1, 2
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

//笔移动函数，参数为点坐标值，计算两点坐标距离来控制笔移动
void drawTo(double pX, double pY) {
  double dx, dy, c;
  int i;
  
  Serial.println(pX);
  Serial.println(pY);

  // dx dy of new point
  dx = pX - lastX;
  dy = pY - lastY;
  //path lenght in mm, times 4 equals 4 steps per mm
  c = floor(1 * sqrt(dx * dx + dy * dy));

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


//用各种三角函数把位置坐标换算成舵机的角度，如何计算，请参考
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
