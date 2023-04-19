/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-03-24 https://www.robotway.com/
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


float LEAD = 8.0;   //定义丝杠导程，即步进电机转动一圈，丝杠前进8mm

 
float DIAGONAL_A = 20;  //定义多边形两条对角线长度
float DIAGONAL_B = 30;

float Xmin = 0;    
float Xmax = sqrt((DIAGONAL_A/2)*(DIAGONAL_A/2)+(DIAGONAL_B/2)*(DIAGONAL_B/2));  //多边形X方向边长
float Ymin = 0;
float Ymax = (2*DIAGONAL_A/2*DIAGONAL_B/2)/Xmax;     //多边形Y方向的高

float x1 = 0;          //多边形四个顶点的坐标
float y1 = 0;
float x2 = Xmax;
float y2 = 0;
float x3 = (2*DIAGONAL_B/2*DIAGONAL_B/2-Xmax*Xmax)/Xmax+Xmax;
float y3 = Ymax;
float x4 = (2*DIAGONAL_B/2*DIAGONAL_B/2-Xmax*Xmax)/Xmax;
float y4 = Ymax;

void setup()
{
	Serial.begin(9600);                             //开启串口通信，波特率为9600
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
     
    step(Y_DIR,Y_STP,-40000);
    step(X_DIR, X_STP, 24000);
    
    runIn(x1, y1, x2, y2);
    
    runIn(x2, y2, x3, y3);
    
    runIn(x3, y3, x4, y4);
    
    runIn(x4, y4, x1, y1);
    
    resetStepper();
	
}

//四象限直线插补函数，参数为两个点的坐标值
void runIn(float x1, float y1, float x2, float y2)
{
  /*
   dx：X轴两坐标间步数值
   dy：Y轴两坐标间步数值
   n ：两坐标X轴和Y轴总步数
   k ：象限值
   f ：偏差计算值
   stepInc：步进电机转动步数
   */
  int dx, dy, n, k, i, f, stepInc;
  dx = abs((x2-x1)/LEAD*stepsPerRevolution);  
  dy = abs((y2-y1)/LEAD*stepsPerRevolution); 
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
  
  if(x2 >= x1)
  {
    k = y2 >= y1 ? 1:4;
  }
  else
  {
    k = y2 >= y1 ? 2:3;
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
