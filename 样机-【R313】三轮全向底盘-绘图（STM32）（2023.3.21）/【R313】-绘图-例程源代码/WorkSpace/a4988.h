#ifndef __A4988_H
#define __A4988_H 
#include "sys.h"
#include "stm32f4xx_conf.h"
#include "key.h"
#define SMEN	PEout(0)
//4 z
#define SMSTEP4	10 //固定芯片步进STEP
#define SMDIR4 	11 //固定芯片步进DIR
//3 x
#define SMSTEP3	8 //固定芯片步进STEP
#define SMDIR3 	9 //固定芯片步进DIR
//2 a 
#define SMSTEP2	3 //固定芯片步进STEP
#define SMDIR2	4 //固定芯片步进DIR
//1 y
#define SMSTEP1	1 //固定芯片步进STEP
#define SMDIR1	2 //固定芯片步进DIR


#define stepper_count 4
#define stepperPulse_delay 2000
#define LINE_BUFFER_LENGTH 512

#define positive_x 0
#define positive_y 1
#define negative_x 2
#define negative_y 3
#define AFA 60
#define theta 0
#define L 0.1725 //轮子中心到底盘中心的距离
//==========================================================================================
//********【添加的函数】********************************************************************
//==========================================================================================
#define SMSTEP_Z  PDout(8) //固定芯片步进STEP
#define SMDIR_Z 	PDout(9) //固定芯片步进DIR
#define SMEN	PEout(0)
#define SMSTEP_X  PEout(1) //固定芯片步进STEP
#define SMDIR_X 	PEout(2) //固定芯片步进DIR
#define SMSTEP_Y  PEout(3) //固定芯片步进STEP
#define SMDIR_Y 	PEout(4) //固定芯片步进DIR
#define STEPPER_SPEED  500 //Step motor speed
//#define wheel_D 0.0582f //11.6//121.6 //mm      内齿：121.6毫米    外齿：12.16+1.6=13.76
//#define M_PI 3.14
//#define wheel_R wheel_D/2.0
//#define MICRO_STEP 16
//#define MAIN_STEP 200
//#define TOTAL_STEP (MICRO_STEP * MAIN_STEP) //3200 steps
//#define Cwheel  (M_PI*wheel_D)
//#define Ratio  (TOTAL_STEP / Cwheel)// 3200/(pi*58.2)=  17.50157 step/mm
                                    // 3200/(pi*0.0582)=17501.574498077 step/m

#define x_dir  2
#define x_stp  1
#define y_dir  4
#define y_stp  3
#define z_dir  9
#define z_stp  8

#define stepper_pluse 1800


extern int myabs(int a);//绝对值函数
extern void Stepper_Motor_Init(int en);
extern void StepperMove(int dir_xy, int steps);//步进电机初始化函数
extern void StepperDir(int positiveDir_x, int positiveDir_y, int  negativeDir_x, int negativeDir_y);
extern void Stepper_Motor_Contorl(int dirpin, int steppin);

extern float max_value(float value_a, float value_b, float value_c);
extern void Stepper_Motor_Init_Z(void);
extern void Stepper_Motor_Contorl_Z(u8 dir, u16 period, u32 steps);

extern void Stepper_Motor_Init_XY(void);
extern void Stepper_Motor_Contorl_X(u8 dir, u16 period, u32 steps);
extern void Stepper_Motor_Contorl_Y(u8 dir, u16 period, u32 steps);

extern void step_move(float x, float y, float w);

extern void Stepper_Motor_Contorl_X_new(u8 dir, u16 period, u32 steps);
extern void Stepper_Motor_Contorl_Y_new(u8 dir, u16 period, u32 steps);
extern void Stepper_Motor_Contorl_Z_new(u8 dir, u16 period, u32 steps);

extern void stepper_moves(int dirPin, int stepperPin, float steps);
extern void Stepper_Action_Init(void);
extern void stepper_move(int dirPin, int stepperPin, float steps);
extern void stepper(int dirPin, int stepperPin, int steps);
extern void stepper(int dirPin, int stepperPin, int steps);

extern  void XYRun(float vx, float vy, float w);
extern void stepper_move_distance_Y(float dis_vx, float dis_vy, float dis_vz);
extern void stepper_move_distance_X(float dis_vx, float dis_vy, float dis_vz);




extern void move_y(float distance);
extern void move_x(float distance);
extern void XYRun_x(float Vy, float Vx, float w_t);
extern void stepper_motor_go_x(float _vx,float _vy, float _vz);



extern void Move_Y_New(float steps);
extern void Move_X_New(float steps);
extern void drawSin(void);
extern void initPos(void);
extern void drawRect(void);
extern void drawTriangle();
extern void drawThreeLeaf(void);
#endif
