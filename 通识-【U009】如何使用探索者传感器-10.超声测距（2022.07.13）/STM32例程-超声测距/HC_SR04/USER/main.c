#include "sys.h" 
#include "led.h" 
#include "timer.h"
#include "exti.h"

int main(void)
{
	delay_init(168);		//	��ʼ����ʱ��168ΪCPU����Ƶ��
	uart_init(115200); 	//���ڳ�ʼ�� 
	LED_Init();			//��ʼ��LED��
	EXTI5_Init();	//�ⲿ�жϳ�ʼ��		 
  TIM2_Init(20000-1, 8400-1);	
	//142M/8400=20000hz�ļ���Ƶ��,��װ��ֵ20000������PWMƵ��Ϊ 20000/20000=1hz.  
	while(1)
	{
		Wave_SRD_Strat4();
		delay_ms(60);
		printf("distance:%.2fCM\n", Distance);
		delay_ms(100);
	}

}

