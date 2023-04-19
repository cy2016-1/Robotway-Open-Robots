/*------------------------------------------------------------------------------------
  ��Ȩ˵����Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by ������ 2023-03-03 https://www.robotway.com/
  ------------------------------*/
#include "sys.h" 
#include "led.h" 
#include "a4988.h"
#include "pwm.h"
#include "math.h"

#define PI 3.14

void Put_Up(void);//��ʺ���
void Put_Down(void);//̧�ʺ���
void draw_sexangle(void);//���������κ���
void drawLine(float x1, float y1);//ֱ�߲岹����

float Xmin = -60;                      //�����ͼ��Χ
float Xmax = 60;
float Ymin = -60;
float Ymax = 60;

float Xpos = 0;
float Ypos = 0;
float l = 60;//�߳�
const int stepsPerRevolution = 3200;//�����������
int step_test = 8000;
int step_test1 = 6000;


int main(void)
{
	delay_init(168);//��ʼ����ʱ��168ΪCPU����Ƶ��
	TIM4_PWM_Init(20000-1,84-1);//�����ʼ��
	Stepper_Motor_Init(0);//���������ʼ��
	while(1)
	{
		All_stepper_move( step_test, -step_test,  step_test, -step_test);delay_ms(500);//ǰ��
		All_stepper_move(-step_test,  step_test, -step_test,  step_test);delay_ms(500);//����

		All_stepper_move(-step_test, -step_test, -step_test, -step_test);delay_ms(500);//��ת
		All_stepper_move( step_test,  step_test,  step_test,  step_test);delay_ms(500);//��ת
		
		All_stepper_move(-step_test, -step_test,  step_test,  step_test);delay_ms(500);//��ƽ��
		All_stepper_move( step_test,  step_test, -step_test, -step_test);delay_ms(500);//��ƽ��
		//move_test();
		while(1){
		}
	}
}
