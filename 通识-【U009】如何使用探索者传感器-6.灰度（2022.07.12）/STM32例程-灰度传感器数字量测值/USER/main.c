#include "sys.h" 
#include "led.h" 
#include "digital_sensor.h"

int main(void)
{
	u8 flag;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//初始化延时，168为CPU运行频率
	uart_init(9600);		//初始化串口1
	LED_Init();					//初始化LED灯
	Sensor_Init();			//传感器初始化
	while(1)
	{	
		delay_ms(1000);
		flag = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);	//获取传感器的状态
		printf("flag:%d\n", flag);
	}

}




