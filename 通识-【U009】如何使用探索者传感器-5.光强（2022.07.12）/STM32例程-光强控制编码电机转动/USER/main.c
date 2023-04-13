#include "sys.h" 
#include "led.h" 
#include "adc.h"
#include "pwm.h"


void forward(void);
void back(void);

int main(void)
{
	u16 adcx;
	delay_init(168);		//初始化延时，168为CPU运行频率
	uart_init(115200); 	//串口初始化 
	LED_Init();					//初始化LED灯
	Adc_Init();         //初始化ADC
	TIM4_PWM_Init(20000-1,84-1);	
	TIM3_PWM_Init(20000-1,84-1);
	//84M/84=1000000hz的计数频率,重装载值20000，所以频率为 1000000/20000=50hz. 
	while(1)
	{
		adcx=Get_Adc_Average(ADC_Channel_1,20);	//获取通道5的转换值，20次取平均
		if(adcx < 200)
			forward();
		else
			back();
	}

}

void forward(void)
{
	TIM_SetCompare1(TIM4,0);
	TIM_SetCompare4(TIM3,2000);		
}

void back(void)
{
	TIM_SetCompare1(TIM4,2000);
	TIM_SetCompare4(TIM3,0);	
}

