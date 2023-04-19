/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-03-09 https://www.robotway.com/
  ------------------------------*/
#include <Servo.h>

/*
 * en：定义步进电机使能引脚
 * servo_pin：定义舵机引脚
 * stepper_count：定义步进电机数量
 * stepperPulse_delay：定义步进电机脉冲生成间隔
 * LINE_BUFFER_LENGTH：定义串口接收数据长度
 */
#define en 8
#define servo_pin 11
#define stepper_count 4
#define stepperPulse_delay 850
#define LINE_BUFFER_LENGTH 512

/*
 * positive_x：定义正向 X 轴
 * positive_y：定义正向 Y 轴
 * negative_x：定义负向 X 轴
 * negative_y：定义负向 Y 轴
 */
#define positive_x 0
#define positive_y 1
#define negative_x 2
#define negative_y 3

/*
 * stepperDir_pin：定义步进电机方向引脚数组
 * stepperStp_pin：定义步进电机步进引脚数组
 * dir: x: 5, y: 6, z: 7, a: 13
 * stp: x: 2, y: 3, z: 4, a: 12
 */
int stepperDir_pin[4] = {5, 6, 7, 13};
int stepperStp_pin[4] = {2, 3, 4, 12};

Servo myServo;

const int stepsPerRevolution = 3200;   //定义步进电机每圈转动的步数，此处为16细分，每圈 3200 步
int penZup = 145;                      //定义舵机抬起角度
int penZdown = 150;                    //定义舵机放下角度

float LEAD = sqrt(2) * 58 * PI;        //定义步进电机转动 1 圈，小车前进的距离，单位 mm

float l = 60;                          //定义六边形边长
                                       //定义六边形顶点坐标数组
float coords[7][2] = {
       -l*1/2, -sqrt(3)/2*l,
       l*1/2, -sqrt(3)/2*l,
       l,     0,
       l*1/2, sqrt(3)/2*l,
      -l*1/2, sqrt(3)/2*l,
      -l,     0 ,
      -l*1/2, -sqrt(3)/2*l
};

float Xmin = -60;                      //定义绘图范围
float Xmax = 60;
float Ymin = -60;
float Ymax = 60;

float Xpos = 0;
float Ypos = 0;

void setup() {
  Serial.begin(9600);                 //开启串口通信，波特率为 9600
  myServo.attach(servo_pin);
  myServo.write(penZup);
  for(int i=0;i<stepper_count;i++)
  {
    pinMode(stepperDir_pin[i], OUTPUT);
    pinMode(stepperStp_pin[i], OUTPUT);  
  }
  pinMode(en, OUTPUT);
  digitalWrite(en, LOW);
  delay(1000);
}

void loop()
{ 

  draw_sexangle();
  while(1){};
}

//六边形绘制函数
void draw_sexangle()
{
  drawLine(coords[0][0], coords[0][1]);
  delay(200);
  
  for(int i=0;i<sizeof(coords) / sizeof(coords[0]);i++)
  {
    penDown();
    delay(200);
    drawLine(coords[i][0], coords[i][1]);
    penUp();
  }
}

//直线插补函数，参数为点坐标值
void drawLine(float x1, float y1)
{
  int dx, dy, n, k, i, f, stepInc;
  
  if (x1 >= Xmax) { 
    x1 = Xmax; 
  }
  if (x1 <= Xmin) { 
    x1 = Xmin; 
  }
  if (y1 >= Ymax) { 
    y1 = Ymax; 
  }
  if (y1 <= Ymin) { 
    y1 = Ymin; 
  }
  
  x1 = (int)(x1/LEAD*stepsPerRevolution);
  y1 = (int)(y1/LEAD*stepsPerRevolution);
  float x0 = Xpos;
  float y0 = Ypos;
  
  dx = abs(x1-x0);
  dy = abs(y1-y0);
  n = abs(dx+dy);

  if(x1 >= x0)
  {
    k = y1 >= y0 ? 1:4;
  }
  else
  {
    k = y1 >= y0 ? 2:3;
  }
  
  for(i=0,f=0;i<n;i+=1)
  {
    if(f>=0)
    {
      switch(k)
      {
         case 1:
         stepper_move(positive_x, 1);
         f = f - dy;
         //Serial.println("+x");
         break;
         case 2:
         stepper_move(negative_x, 1);
         f = f - dy;
         //Serial.println("-x");
         break;
         case 3:
         stepper_move(negative_x, 1);
         f = f - dy;
         //Serial.println("-x");
         break;
         case 4:
         stepper_move(positive_x, 1);
         f = f - dy;
         //Serial.println("+x");
         break;
         default:break;
      }
    }
    else
    {
      switch(k)
      {
        case 1:
        stepper_move(positive_y, 1);
        f = f + dx;
        //Serial.println("+y");
        break;
        case 2:
        stepper_move(positive_y, 1);
        f = f + dx;
        //Serial.println("+y");
        break;
        case 3:
        stepper_move(negative_y, 1);
        f = f + dx;
        //Serial.println("-y");
        break;
        case 4:
        stepper_move(negative_y, 1);
        f = f +dx;
        //Serial.println("-y");
        break;
        default:break;
      }
    }
  }
  
  Xpos = x1;
  Ypos = y1;
}

//小车行进方向控制函数
void stepper_dir(int positiveDir_x, int positiveDir_y, int negativeDir_x, int negativeDir_y)
{
  int dir_value[] = {positiveDir_x, positiveDir_y, negativeDir_x, negativeDir_y};
  
  for(int i=0;i<stepper_count;i++)
  {
    //Serial.print(dir_value[i]);
    //Serial.print(",");
    digitalWrite(stepperDir_pin[i], dir_value[i]); 
  }
  //Serial.println();
  
  for(int j=0;j<stepper_count;j++)
  {
    digitalWrite(stepperStp_pin[j], HIGH); 
  }  
  delayMicroseconds(stepperPulse_delay);
  for(int j=0;j<stepper_count;j++)
  {
    digitalWrite(stepperStp_pin[j], LOW);
  }
  delayMicroseconds(stepperPulse_delay);
}

//步进电机转动函数，参数 dir_xy：步进电机转动方向，steps：步进电机转动步数
void stepper_move(int dir_xy, int steps)
{
  for(int i=0;i<abs(steps);i++)
  {
    switch(dir_xy)
    {
      case 0:
      stepper_dir(1, 1, 0, 0);
      break;
      case 1:
      stepper_dir(1, 0, 1, 0);
      break;
      case 2:
      stepper_dir(0, 0, 1, 1);
      break;
      case 3:
      stepper_dir(0, 1, 0, 1);
      break;
      default:break;  
    }  
  }
}

//舵机抬笔函数
void penUp()
{
  myServo.write(penZup);
}

//舵机落笔函数
void penDown()
{
  myServo.write(penZdown);
}
