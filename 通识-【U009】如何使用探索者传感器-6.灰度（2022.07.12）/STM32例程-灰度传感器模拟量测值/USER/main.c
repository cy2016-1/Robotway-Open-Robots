#include "sys.h" 
#include "led.h" 
#include "adc.h"

int main(void)
{
	u16 adcx;
	delay_init(168);		//��ʼ����ʱ��168ΪCPU����Ƶ��
	uart_init(115200); 	//���ڳ�ʼ�� 
	LED_Init();					//��ʼ��LED��
	Adc_Init();         //��ʼ��ADC
	while(1)
	{
		adcx=Get_Adc_Average(ADC_Channel_1,20);	//��ȡͨ��5��ת��ֵ��20��ȡƽ��
		printf("������ֵΪ��%d\r\n",adcx);			//���ڷ��Ͳ���ֵ
		delay_ms(100);
	}

}

