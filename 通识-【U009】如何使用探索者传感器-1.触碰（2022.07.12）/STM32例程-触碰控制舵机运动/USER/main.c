#include "sys.h" 
#include "led.h" 
#include "key.h"
#include "pwm.h"

int num = 0;

void Turn_180(void);
void Turn_0(void);

int main(void)
{
	delay_init(168);		//��ʼ����ʱ��168ΪCPU����Ƶ��
	uart_init(115200);
	LED_Init();					//��ʼ��LED��
	KEY_Init();					//��ʼ������
	TIM12_PWM_Init(20000-1,84-1);//��ʱ����ʼ��	
	//84M/84=1000000hz�ļ���Ƶ��,��װ��ֵ20000������Ƶ��Ϊ 1000000/20000=50hz. 
	TIM_SetCompare2(TIM12,1500);
	while(1)
	{
		if(flag){
			if(num%2 == 0)
				Turn_180();
			else
				Turn_0();			
			num++;
			flag = FLASE;
		}
	}
}

void Turn_180(void)
{
	for(int i=1500; i < 2500; i++){
		TIM_SetCompare2(TIM12,i);
		delay_ms(1);
	}	
	for(int i=2500; i > 1500; i--){
		TIM_SetCompare2(TIM12,i);
		delay_ms(1);
	}
}

void Turn_0(void)
{
	for(int i=1500; i > 500; i--){
		TIM_SetCompare2(TIM12,i);
		delay_ms(1);
	}
	for(int i=500; i < 1500; i++){
		TIM_SetCompare2(TIM12,i);
		delay_ms(1);
	}
}

