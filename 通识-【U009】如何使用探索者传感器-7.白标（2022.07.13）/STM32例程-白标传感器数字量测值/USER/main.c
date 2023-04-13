#include "sys.h" 
#include "led.h" 
#include "digital_sensor.h"

int main(void)
{
	u8 flag;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʼ����ʱ��168ΪCPU����Ƶ��
	uart_init(9600);		//��ʼ������1
	LED_Init();					//��ʼ��LED��
	Sensor_Init();			//��������ʼ��
	while(1)
	{	
		delay_ms(1000);
		flag = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);	//��ȡ��������״̬
		printf("flag:%d\n", flag);
	}

}




