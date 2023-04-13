#include "exti.h"
#include "timer.h"
#include "led.h"

#define Trig GPIO_Pin_4		//超声波输出
#define Echo GPIO_Pin_5		//超声波输入

float Distance;

void EXTI5_Init(void)
{
	GPIO_InitTypeDef 	 GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能GPIOA时钟	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);	//使能SYSCFG时钟
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource5);//连接到中断线5
	
	GPIO_InitStructure.GPIO_Pin = Echo; //GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化

	GPIO_InitStructure.GPIO_Pin = Trig; //GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化
	
	
	/* 配置EXTI_Line4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
	EXTI_Init(&EXTI_InitStructure);//配置
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断4
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);//配置
}



void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) == SET){//由中断4触发
		TIM_SetCounter(TIM2,0);//定时器计数清零
		TIM_Cmd(TIM2,ENABLE);//开启定时器
		while(GPIO_ReadInputDataBit(GPIOA,Echo));//等待输入
		TIM_Cmd(TIM2,DISABLE);//关闭定时器
		Distance= TIM_GetCounter(TIM2)*340/400;// distance = t*340/2		t = count*1/20000	1m=100cm  距离计算
		EXTI_ClearITPendingBit(EXTI_Line5);//清除LINE4上的中断标志位  
	}
}



void Wave_SRD_Strat4(void)
{
  GPIO_SetBits(GPIOA,Trig);   //将Trig设置为高电平
	delay_us(20);               //持续大于10us触发，触发超声波模块工作
	GPIO_ResetBits(GPIOA,Trig); 
}


