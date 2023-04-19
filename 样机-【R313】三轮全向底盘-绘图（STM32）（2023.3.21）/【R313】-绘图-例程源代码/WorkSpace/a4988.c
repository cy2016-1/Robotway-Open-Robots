#include "a4988.h"
#include "delay.h"
#include "key.h"
#include "stdbool.h"
#include "a4988.h"
#include "delay.h"
#include <math.h>
#include "usart.h"
#include "sys.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "led.h"
#include "pwm.h"
#include "stm32f4xx_usart.h"

int stepperDir_pin[4] = {9, 2, 4, 11};
int stepperStp_pin[4] = {8, 1, 3, 10};
int myabs(int a);

const float wheel_D = 58.2f; //0.0582f
const float BigCircle_R =172.5f;     //    0.1725f;   三轮小车轮半径0.16552m


//const float wheel_D = 0.0582f; //0.0582f
const float M_PI = 3.141592f;
const float MICRO_STEP =16.0f;
const float MAIN_STEP =200.0f;
const float TOTAL_STEP =MICRO_STEP * MAIN_STEP;
const float Cwheel = M_PI * wheel_D;
const float Ratio = (TOTAL_STEP / Cwheel); // 3200/(pi*58.2)=  17.50157 step/mm
                                                             //17501.5744980778 step/m
const float ratio_back = (Cwheel/TOTAL_STEP);                //0.00005713771638 m/step
                                                             //0.0571377163 mm/step

const float kTurningAdjustRate = 1.0f;
const float KTurningAdjustRate = 0.95f;
//const float BigCircle_R =0.1725f;     //    0.1725f;   三轮小车轮半径0.16552m
const float Ratios=  3200.0f / (3.14159f * 0.0582f);
const float WRatio = kTurningAdjustRate * BigCircle_R * Ratios; //step/rad弧度  3027.432925


float current_vx = 0.0;
float current_vy = 0.0;
float current_va = 0.0;

float finally_vx = 0;
float finally_vy = 0;
float finally_vz = 0;


struct ActThreeVell{
  double v1;
  double v2;
  double v3;
}vell;

void Stepper_Motor_Init(int en)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOD时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_8|GPIO_Pin_9;//对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//对应引脚
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化
	
	SMEN = en;
}


int myabs(int a)
{
	if(a >= 0)
		return a;
	else
		return a*(-1);
}


float delta_time[3]={0,0,0};

void stepper_motor_go(float _vx,float _vy, float _vz)
{
	int temporary_x=0;
	int temporary_y=0;
	int temporary_z=0;
	
	int permanent_x=0;
	int permanent_y=0;
	int permanent_z=0;		
	
	temporary_x = _vx!=0 ? 1 : 0;
	temporary_y = _vy!=0 ? 1 : 0;
	temporary_z = _vz!=0 ? 1 : 0;
	
	if(temporary_z){
	    SMSTEP_Z=temporary_z;
	    delay_us(fabs((1/_vz)*10000));
	    SMSTEP_Z=permanent_z;		
		  delay_us(fabs((1/_vz)*10000));	
	}
	if(temporary_z){
	    SMSTEP_Z=temporary_z;
	    delay_us(fabs((1/_vz)*10000));
	    SMSTEP_Z=permanent_z;		
		  delay_us(fabs((1/_vz)*10000));	
	}
	
	if(temporary_x){
	    SMSTEP_X=temporary_x;
	    delay_us(fabs((1/_vx)*1000000));
		
	    SMSTEP_X=permanent_x;
		  delay_us(fabs((1/_vx)*1000000));
	}
	
	if(temporary_y){
	    SMSTEP_Y=temporary_y;
	    delay_us(fabs((1/_vy)*1000000));
	    SMSTEP_Y=permanent_y;		
		  delay_us(fabs((1/_vy)*1000000));
	}

	
	delta_time[0] = (fabs(_vx)/1000000)*2;
	delta_time[1] = (fabs(_vy)/1000000)*2;
	delta_time[2] = (fabs(_vz)/1000000)*2;
}

void stepper_motor_go_y(float _vx,float _vy, float _vz)
{
	int temporary_x=0;
	int temporary_y=0;
	int temporary_z=0;
	
	int permanent_x=0;
	int permanent_y=0;
	int permanent_z=0;		
	
	temporary_x = _vx!=0 ? 1 : 0;
	temporary_y = _vy!=0 ? 1 : 0;
	temporary_z = _vz!=0 ? 1 : 0;
	
	if(temporary_z){
	    SMSTEP_Z=temporary_z;
	    delay_us(fabs((1/_vz)*10000));
	    SMSTEP_Z=permanent_z;		
		  delay_us(fabs((1/_vz)*10000));	
	}
	/*
	if(temporary_z){
	    SMSTEP_Z=temporary_z;
	    delay_us(fabs((1/_vz)*10000));
	    SMSTEP_Z=permanent_z;		
		  delay_us(fabs((1/_vz)*10000));	
	}
	*/
	
	if(temporary_x){
	    SMSTEP_X=temporary_x;
	    delay_us(fabs((1/_vx)*1000000));
		
	    SMSTEP_X=permanent_x;
		  delay_us(fabs((1/_vx)*1000000));
	}
	
	if(temporary_y){
	    SMSTEP_Y=temporary_y;
	    delay_us(fabs((1/_vy)*1000000));
	    SMSTEP_Y=permanent_y;		
		  delay_us(fabs((1/_vy)*1000000));
	}

	
	delta_time[0] = (fabs(_vx)/1000000)*2;
	delta_time[1] = (fabs(_vy)/1000000)*2;
	delta_time[2] = (fabs(_vz)/1000000)*2;
}

void XYRun(float Vy, float Vx, float w_t){
  static float flag[3] = {-1.0f,-1.0f,-1.0f};
  static float translation = 0.0f;
  static float translation1 = 0.0f;
  //w_t = ( w_t / (0.1628664f) );
	w_t = ( w_t / (0.16f) );
  w_t *= WRatio;  
  Vx  *= Ratio;
  Vy  *= Ratio;
  if      ( (Vx>0.0f) && (Vy==0.0f) && (w_t==0.0f) ){ translation = -1.0f;translation1 = 1.0f; }
  else if ( (Vx<0.0f) && (Vy==0.0f) && (w_t==0.0f) ){ translation = 1.0f; translation1 = -1.0f;}
  else{translation = 1.0f;translation1 = 1.0f;}
  current_vx = (float)translation1*translation*flag[0]* (-0.5f * Vx - 0.86f * Vy + L * w_t);
  current_vy = (float)translation1*translation*flag[1]* (-0.5f * Vx + 0.86f * Vy + L * w_t);
  current_va = (float)translation1*translation*flag[2]* ( 1.0f * Vx + L * w_t);	
	stepper_motor_go(current_vx, current_vy, current_va);
}


void Set_Stepper_Vel(float Vy, float Vx, float w_t)
{
	XYRun( Vy,  Vx, w_t);
}

// 】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】
//【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【

void move_x(float distance)
{
	float real_vel[3]={0.0,0.0,0.0};
	float odom_car[3]={0.0,0.0,0.0};
	int flag_vel[3]={1,1,1};
	//if(distance>0){finally_vx = 0.15;finally_vy = 0;finally_vz = 0;SMDIR_Z = 1;}
	//else if(distance<0){finally_vx = -0.17;finally_vy = 0;finally_vz = 0;SMDIR_Z = 0;}
	//else {finally_vx = 0.0;finally_vy = 0;finally_vz = 0;SMDIR_Z = 0;}
	
	
	if(distance>0){finally_vx = 50;finally_vy = 0;finally_vz = 0;SMDIR_Z = 1;}
	else if(distance<0){finally_vx = -50;finally_vy = 0;finally_vz = 0;SMDIR_Z = 0;}
	else {finally_vx = 0.0;finally_vy = 0;finally_vz = 0;SMDIR_Z = 0;}	
	
	XYRun(finally_vx,  finally_vy, finally_vz);
  //判断方向
	//printf("start\n");
	//printf("p:%f\n",1.0f/delta_time[0]);
	//printf("v:%f\n",1.0f/delta_time[0]*ratio_back);
  if(current_vx >0){SMDIR_X = 0;}else{SMDIR_X=1;}
  if(current_vy >0){SMDIR_Y = 1;}else{SMDIR_Y=0;}
	for(int i=0;i<3;i++)
  {
	  real_vel[i] = 1.0f/delta_time[0]*ratio_back;
		//printf("real:%f\n",real_vel[i]);
  }
		while(flag_vel[0] || flag_vel[1] || flag_vel[2])
		{
      if(odom_car[0] >=fabs(distance)){flag_vel[0] = 0;}
			if(odom_car[1] >=fabs(distance)){flag_vel[1] = 0;}
			if(odom_car[2] >=fabs(distance)){flag_vel[2] = 0;}      
			XYRun( finally_vy,  finally_vx, finally_vz);
		  odom_car[0] += (real_vel[0]*delta_time[0]/0.3f);
		  odom_car[1] += (real_vel[1]*delta_time[1]/0.3f);
		  odom_car[2] += (real_vel[2]*delta_time[2]/0.3f);
		}
}


void move_y(float distance)
{
	float real_vel[3]={0.0,0.0,0.0};
	float odom_car[3]={0.0,0.0,0.0};
	int flag_vel[3]={1,1,1};
	//if(distance>0){finally_vx = 0.0;finally_vy = 0.2;finally_vz = 0;SMDIR_Z = 1;}
	//else if(distance<0){finally_vx = 0.0;finally_vy = -0.2;finally_vz = 0;SMDIR_Z = 0;}
	//else {finally_vx = 0.0;finally_vy = 0;finally_vz = 0;SMDIR_Z = 0;}
	
	if(distance>0){finally_vx = 0.0;finally_vy = 50;finally_vz = 0;SMDIR_Z = 1;}
	else if(distance<0){finally_vx = 0.0;finally_vy = -50;finally_vz = 0;SMDIR_Z = 0;}
	else {finally_vx = 0.0;finally_vy = 0;finally_vz = 0;SMDIR_Z = 0;}	
	
	XYRun(finally_vx,  finally_vy, finally_vz);
	//printf("start\n");
	
	printf("x_vel:%f\n",current_vx);
	printf("y_vel:%f\n",current_vy);
	printf("z_vel:%f\n",current_va);
	
  if(current_vx >0){SMDIR_X = 0;}else{SMDIR_X=1;}
  if(current_vy >0){SMDIR_Y = 1;}else{SMDIR_Y=0;}
	for(int i=0;i<3;i++)
  {
	  real_vel[i] = 1.0f/delta_time[0]*ratio_back;
  }
	if(distance>0)
	{
		//printf("mode1\n");
		while(flag_vel[0] || flag_vel[1] )
		{
      if(odom_car[0] >=fabs(distance)){flag_vel[0] = 0;}
			if(odom_car[1] >=fabs(distance)){flag_vel[1] = 0;}      
			XYRun( finally_vy,  finally_vx, finally_vz);
       
      //stepper_motor_go_y(current_vx, current_vy, current_va);			
		  odom_car[0] += (real_vel[0]*delta_time[0]*0.632f);
		  odom_car[1] += (real_vel[1]*delta_time[1]*0.632f);
		}
	}
	
	else
	{
		//printf("mode2\n");
		while(flag_vel[0] || flag_vel[1] )
		{
      if(odom_car[0] >=fabs(distance)){flag_vel[0] = 0;}
			if(odom_car[1] >=fabs(distance)){flag_vel[1] = 0;}      
			XYRun( finally_vy,  finally_vx, finally_vz);			
		  odom_car[0] += (real_vel[0]*delta_time[0]*0.636f);
		  odom_car[1] += (real_vel[1]*delta_time[1]*0.636f);			
		}
	}
	
}

// 】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】】
//【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【【


//*============================================================================================*
//|*******【添加的函数】***********************************************************************|
//*============================================================================================*


void Move_Y_New(float steps)
{
	int temporary_x=0;
	int temporary_y=0;
	int temporary_z=0;
	
	int permanent_x=0;
	int permanent_y=0;
	int permanent_z=0;
	
	if(steps>0){
	  finally_vx = 0.0;finally_vy = 50;finally_vz = 0;
	  SMDIR_X=1;SMDIR_Y=0;SMDIR_Z = 1;}
	else if(steps<0){
	  finally_vx = 0.0;finally_vy = -50;finally_vz = 0;
	  SMDIR_X=0;SMDIR_Y=1;SMDIR_Z = 0;}
	else {
	  finally_vx = 0.0;finally_vy = 0;finally_vz = 0;
	  SMDIR_X=0;SMDIR_Y=1;SMDIR_Z = 0;}
	
	float distance_to_step = 0.0;
	distance_to_step = fabs(steps);
	
	temporary_x=1;
	temporary_y=1;
	temporary_z=0;
		
	for(int i=0;i<distance_to_step; i++)
  {
		
	  SMSTEP_X=temporary_x;
	  SMSTEP_Y=temporary_y;
	  SMSTEP_Z=temporary_z;
	  delay_us(stepper_pluse);
		
	  SMSTEP_X=permanent_x;
	  SMSTEP_Y=permanent_y;
	  SMSTEP_Z=permanent_z;		
		delay_us(stepper_pluse);
  }
	
}


void Move_X_New(float steps)
{
	int temporary_x=0;
	int temporary_y=0;
	int temporary_z=0;
	
	int permanent_x=0;
	int permanent_y=0;
	int permanent_z=0;
	
	if(steps>0){
	  finally_vx = 0.0;finally_vy = 50;finally_vz = 0;
	  SMDIR_X=0;SMDIR_Y=0;SMDIR_Z = 1;}
	else if(steps<0){
	  finally_vx = 0.0;finally_vy = -50;finally_vz = 0;
	  SMDIR_X=1;SMDIR_Y=1;SMDIR_Z = 0;}
	else {
	  finally_vx = 0.0;finally_vy = 0;finally_vz = 0;
	  SMDIR_X=1;SMDIR_Y=1;SMDIR_Z = 0;}
	
	float distance_to_step = 0.0;
	distance_to_step = fabs(steps);
	
	temporary_x=1;
	temporary_y=1;
	temporary_z=1;
		
	for(int i=0;i<distance_to_step; i++)
  {
	  SMSTEP_Z=temporary_z;
	  delay_us(stepper_pluse);
	  SMSTEP_Z=permanent_z;		
		delay_us(stepper_pluse);	

		
	  SMSTEP_X=temporary_x;
	  SMSTEP_Y=temporary_y;
	  SMSTEP_Z=temporary_z;
	  delay_us(stepper_pluse);
		
	  SMSTEP_X=permanent_x;
	  SMSTEP_Y=permanent_y;
	  SMSTEP_Z=permanent_z;		
		delay_us(stepper_pluse);
			
  }
	
}



//*============================================================================================*
//|*******【绘制图像】***********************************************************************|
//*============================================================================================*
void initPos(void)
{
	Put_Up();delay_ms(1000);
	drawLine(0,0);
	drawLine(0,0);
	Put_Down();delay_ms(1000);
}

//正弦
void drawSin(){
  const double A = 10;
  const double w = 0.1;
  initPos();
  for(double x=0;x<4*M_PI*10;x++){
    //moveTo(x, A*sin(w*x));
		drawLine(x, A*sin(w*x));
  }
}

//矩形
void drawRect(){
  initPos();
  double rectA = 50; //mm
  drawLine(0, rectA);
  drawLine(rectA, rectA);
  drawLine(rectA, 0);
  drawLine(0, 0);
}

//三角形
void drawTriangle(){
  initPos();  
  double sideA = 50;  //边长A/mm
  double sideB = 40; //边长B
  double points[3][2] = {
    {0, sideA},
    {sideB, 0},
    {0, 0}
  };
  for(int i=0;i<3;i++){  
    drawLine(points[i][0], points[i][1]);
  }
}


//三叶草
void drawThreeLeaf()
{
	initPos();
	double rangeVariable = 0;
	int curveFlag = 0;
	double a = 40.0f;
	double b = 15.0f;
	double r = 0.0f;
	double thetas = 0.0f;
	double dtheta = 1.0f/a;
	double x0 = 0;
	double y0 = 0;
	double curvePt_one[2]={0,0};
	double curvePt_two[2]={0,0};
	curvePt_one[0] = x0;
	curvePt_one[1] = y0;
	
	curvePt_one[0] += a;
	curveFlag = 4;
	rangeVariable = 1;
	thetas = dtheta;
	
	Put_Up();delay_ms(1000);
	drawLine(40, 0);
	Put_Down();delay_ms(1000);
	while(thetas < rangeVariable * 3.141592f)
	{
		r = a * cos(3 * thetas);
    curvePt_two[0] = x0 + r * cos(thetas);
    curvePt_two[1] = y0 + r * sin(thetas);
		
		printf("x:%f\n",curvePt_one[0]);
		printf("y:%f\n",curvePt_one[1]);
		
    drawLine(curvePt_one[0], curvePt_one[1]);
		
    curvePt_one[0] = curvePt_two[0];
    curvePt_one[1] = curvePt_two[1];
    thetas += dtheta;		
	}
	
	drawLine(a, 0);
	//Put_Up();delay_ms(1000);
}
