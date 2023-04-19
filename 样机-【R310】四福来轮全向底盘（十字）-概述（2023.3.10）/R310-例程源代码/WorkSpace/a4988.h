#ifndef __A4988_H
#define __A4988_H 
#include "sys.h"
#include "stm32f4xx_conf.h"
#define SMEN	PEout(0)
//4 z
#define SMSTEP4	10 //�̶�оƬ����STEP
#define SMDIR4 	11 //�̶�оƬ����DIR
//3 x
#define SMSTEP3	8 //�̶�оƬ����STEP
#define SMDIR3 	9 //�̶�оƬ����DIR
//2 a 
#define SMSTEP2	3 //�̶�оƬ����STEP
#define SMDIR2	4 //�̶�оƬ����DIR
//1 y
#define SMSTEP1	1 //�̶�оƬ����STEP
#define SMDIR1	2 //�̶�оƬ����DIR


#define stepper_count 4
#define stepperPulse_delay 220
#define LINE_BUFFER_LENGTH 512

#define positive_x 0
#define positive_y 1
#define negative_x 2
#define negative_y 3

extern int stepper_delay;

extern int myabs(int a);//����ֵ����
extern void Stepper_Motor_Init(int en);//���������ʼ������
extern void All_stepper_move(int stepper_x, int stepper_y, int stepper_z, int stepper_a);
extern void step_move_x(int stepper_x);
extern void step_move_y(int stepper_y);
extern void step_move_z(int stepper_z);
extern void step_move_a(int stepper_a);
extern void move_test();
#endif
