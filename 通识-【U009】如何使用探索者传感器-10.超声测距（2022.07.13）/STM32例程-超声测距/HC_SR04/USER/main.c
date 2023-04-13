#include "sys.h" 
#include "led.h" 
#include "timer.h"
#include "exti.h"

int main(void)
{
	delay_init(168);		//	初始化延时，168为CPU运行频率
	uart_init(115200); 	//串口初始化 
	LED_Init();			//初始化LED灯
	EXTI5_Init();	//外部中断初始化		 
  TIM2_Init(20000-1, 8400-1);	
	//142M/8400=20000hz的计数频率,重装载值20000，所以PWM频率为 20000/20000=1hz.  
	while(1)
	{
		Wave_SRD_Strat4();
		delay_ms(60);
		printf("distance:%.2fCM\n", Distance);
		delay_ms(100);
	}

}

