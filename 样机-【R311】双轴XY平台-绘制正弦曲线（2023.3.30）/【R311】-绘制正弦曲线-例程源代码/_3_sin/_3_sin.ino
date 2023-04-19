/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-03-27 https://www.robotway.com/
  ------------------------------*/
#define EN        8       //步进电机使能端，低电平有效
#define X_DIR     5       //X轴 步进电机方向控制
#define Y_DIR     6       //y轴 步进电机方向控制
#define X_STP     2       //x轴 步进控制
#define Y_STP     3       //y轴 步进控制
boolean DIR;              //boolean类型变量 DIR，控制步进电机方向，true为正向，false为反向，根据接线做调整
int stepper_delay = 40;   //定义步进电机脉冲发送的时间间隔

const int SENSOR_X = 18;     //定义X方向复位传感器引脚
const int SENSOR_Y = 14;     //定义y方向复位传感器引脚
const int SENSOR_TOUCH = 16; //定义电机运动的触发传感器引脚

const int stepsPerRevolution = 3200;  //定义步进电机每圈转动的步数，细分为16

float LEAD = 0.8;  //定义丝杠导程，即步进电机转动一圈，丝杠前进8cm

float A = 2.0;     //定义sin函数振幅
float W = 1.0;     //定义sin函数角频率
float P = 0.0;     //定义sin函数初始相位

float Xmin = 0;
float Ymin = 0;


float Xpos = Xmin;
float Ypos = Ymin;


void setup()
{
	Serial.begin(9600);                  //开启串口通信，波特率为9600
  pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);
  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);	 	
	resetStepper();
	
	
}

void loop()
{            
        while(digitalRead(SENSOR_TOUCH))
         delay(10);
         
        Xpos = 0;
        Ypos = 0;
         
        step(Y_DIR,Y_STP,-40000);
        //step(X_DIR, X_STP, 28000);
        
        for(float x=0;x<=2*PI/W;x+=0.1)
        {
          float y = A*sin(W*x+P);
          drawLine(x,y);
        }
        
        step(X_DIR, X_STP, 8000);
        
        resetStepper();
	
}

//图形绘制函数，参数为点坐标值
void drawLine(float x1, float y1)
{
  int dx, dy, n, k, i, f, stepInc;
  x1 = (int)(x1/LEAD*stepsPerRevolution);
  y1 = (int)(y1/LEAD*stepsPerRevolution);
  float x0 = Xpos;
  float y0 = Ypos;
  
  Serial.println(Xpos);
  Serial.println(Ypos);
  
  dx = abs(x1-x0);
  dy = abs(y1-y0);
  n = abs(dx+dy);
  if(dx==0||dy==0)
  {
    stepper_delay = 40;
    stepInc = 10;
  }
  else
  {
    stepper_delay = 200;
    stepInc = 100;
  }
  
  if(x1 >= x0)
  {
    k = y1 >= y0 ? 1:4;
  }
  else
  {
    k = y1 >= y0 ? 2:3;
  }
  
  for(i=0,f=0;i<n;i+=stepInc)
  {
    if(f>=0)
    {
      switch(k)
      {
         case 1:
         step(X_DIR, X_STP, stepInc);
         f = f - dy;
         //Serial.println("+x");
         break;
         case 2:
         step(X_DIR, X_STP, -stepInc);
         f = f - dy;
         //Serial.println("-x");
         break;
         case 3:
         step(X_DIR, X_STP, -stepInc);
         f = f - dy;
         //Serial.println("-x");
         break;
         case 4:
         step(X_DIR, X_STP, stepInc);
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
        step(Y_DIR, Y_STP, stepInc);
        f = f + dx;
        //Serial.println("+y");
        break;
        case 2:
        step(Y_DIR, Y_STP, stepInc);
        f = f + dx;
        //Serial.println("+y");
        break;
        case 3:
        step(Y_DIR, Y_STP, -stepInc);
        f = f + dx;
        //Serial.println("-y");
        break;
        case 4:
        step(Y_DIR, Y_STP, -stepInc);
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

/*
//函数：step    功能：控制步进电机方向，步数。
//参数：dirPin对应步进电机的DIR引脚，stepperPin 对应步进电机的step引脚， steps 步进的步数
//无返回值
*/
void step(byte dirPin, byte stepperPin, int steps)
{
  boolean DIR = steps>0 ? true : false;  
  digitalWrite(dirPin,DIR);
  for(int i=0;i<abs(steps); i++)
  {
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(stepper_delay);
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(stepper_delay); 
  }
}

//步进电机复位函数
void resetStepper()
{
        stepper_delay = 40;
	while(digitalRead(SENSOR_X))
		step(X_DIR,X_STP,-10);
        step(X_DIR,X_STP,15);
	while(digitalRead(SENSOR_Y))
		step(Y_DIR,Y_STP,-10);
        step(Y_DIR,Y_STP,15);
}
