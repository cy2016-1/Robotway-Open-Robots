#include "sys.h" 
#include "led.h" 
#include "key.h"
#include "pwm.h"

int num = 0;

void forward(void);
void back(void);

int main(void)
{
	delay_init(168);		//��ʼ����ʱ��168ΪCPU����Ƶ��
	uart_init(115200);
	LED_Init();					//��ʼ��LED��
	KEY_Init();					//��ʼ������
	TIM4_PWM_Init(20000-1,84-1);	
	TIM3_PWM_Init(20000-1,84-1);
	//84M/84=1000000hz�ļ���Ƶ��,��װ��ֵ20000������Ƶ��Ϊ 1000000/20000=50hz. 
	LED0=0;
	while(1)
	{
		if(flag){
			if(num%2 == 0)
				forward();
			else
				back();			
			num++;
			flag = FLASE;
		}
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

