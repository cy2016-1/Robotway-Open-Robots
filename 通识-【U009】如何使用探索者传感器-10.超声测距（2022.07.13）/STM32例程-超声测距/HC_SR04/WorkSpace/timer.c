#include "timer.h"

void TIM2_Init(u32 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  			//TIM2时钟使能 
	
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  								//定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   									//自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
		
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	
	TIM_Cmd(TIM2,ENABLE ); 	//使能定时器2

}







