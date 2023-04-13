#include "sys.h" 
#include "led.h" 
#include "adc.h"

int main(void)
{
	u16 adcx;
	delay_init(168);		//初始化延时，168为CPU运行频率
	uart_init(115200); 	//串口初始化 
	LED_Init();					//初始化LED灯
	Adc_Init();         //初始化ADC
	while(1)
	{
		adcx=Get_Adc_Average(ADC_Channel_1,20);	//获取通道5的转换值，20次取平均
		printf("测量的值为：%d\r\n",adcx);			//串口发送测量值
		delay_ms(100);
	}

}

