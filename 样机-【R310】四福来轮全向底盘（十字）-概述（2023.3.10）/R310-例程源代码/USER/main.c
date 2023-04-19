/*------------------------------------------------------------------------------------
  版权说明：Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by 机器谱 2023-03-03 https://www.robotway.com/
  ------------------------------*/
#include "sys.h" 
#include "led.h" 
#include "a4988.h"
#include "pwm.h"
#include "math.h"

#define PI 3.14

void Put_Up(void);//落笔函数
void Put_Down(void);//抬笔函数
void draw_sexangle(void);//画正六边形函数
void drawLine(float x1, float y1);//直线插补函数

float Xmin = -60;                      //定义绘图范围
float Xmax = 60;
float Ymin = -60;
float Ymax = 60;

float Xpos = 0;
float Ypos = 0;
float l = 60;//边长
const int stepsPerRevolution = 3200;//步进电机步数
int step_test = 8000;
int step_test1 = 6000;


int main(void)
{
	delay_init(168);//初始化延时，168为CPU运行频率
	TIM4_PWM_Init(20000-1,84-1);//舵机初始化
	Stepper_Motor_Init(0);//步进电机初始化
	while(1)
	{
		All_stepper_move( step_test, -step_test,  step_test, -step_test);delay_ms(500);//前进
		All_stepper_move(-step_test,  step_test, -step_test,  step_test);delay_ms(500);//后退

		All_stepper_move(-step_test, -step_test, -step_test, -step_test);delay_ms(500);//左转
		All_stepper_move( step_test,  step_test,  step_test,  step_test);delay_ms(500);//右转
		
		All_stepper_move(-step_test, -step_test,  step_test,  step_test);delay_ms(500);//左平移
		All_stepper_move( step_test,  step_test, -step_test, -step_test);delay_ms(500);//右平移
		//move_test();
		while(1){
		}
	}
}
