#include "sys.h" 
#include "led.h" 
#include "key.h"
#include "pwm.h"

int num = 0;

void forward(void);
void back(void);

int main(void)
{
	delay_init(168);		//初始化延时，168为CPU运行频率
	uart_init(115200);
	LED_Init();					//初始化LED灯
	KEY_Init();					//初始化按键
	TIM4_PWM_Init(20000-1,84-1);	
	TIM3_PWM_Init(20000-1,84-1);
	//84M/84=1000000hz的计数频率,重装载值20000，所以频率为 1000000/20000=50hz. 
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

