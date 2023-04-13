#include "sys.h" 
#include "led.h" 
#include "adc.h"
#include "pwm.h"


void forward(void);
void back(void);

int main(void)
{
	u16 adcx;
	delay_init(168);		//��ʼ����ʱ��168ΪCPU����Ƶ��
	uart_init(115200); 	//���ڳ�ʼ�� 
	LED_Init();					//��ʼ��LED��
	Adc_Init();         //��ʼ��ADC
	TIM4_PWM_Init(20000-1,84-1);	
	TIM3_PWM_Init(20000-1,84-1);
	//84M/84=1000000hz�ļ���Ƶ��,��װ��ֵ20000������Ƶ��Ϊ 1000000/20000=50hz. 
	while(1)
	{
		adcx=Get_Adc_Average(ADC_Channel_1,20);	//��ȡͨ��5��ת��ֵ��20��ȡƽ��
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

