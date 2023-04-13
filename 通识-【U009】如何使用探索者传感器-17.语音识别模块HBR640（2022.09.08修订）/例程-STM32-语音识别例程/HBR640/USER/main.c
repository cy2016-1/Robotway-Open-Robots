#include "sys.h" 
#include "led.h" 
#include "motor.h"
#include "hbr640.h"
#include "hbr_uart5.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

void forward(void);
void back(void);
void left(void);
void right(void);

int main(void)
{
	delay_init(168);		//初始化延时，168为CPU运行频率
	usart_init(115200); 	//串口初始化 
	UART5_INIT();
	LED_Init();					//初始化LED灯
	MOTOR_Init();				//电机初始化
	HBR640_INIT();
	open();
	while(1)
	{	
		delay_ms(100);
		printf("%s\n",_receiveBuf);
		if(isHeard()){
			int value = getSentence();
			printf("%d\n",value);
			switch(value){
				case 0 :
					forward();
					delay_ms(1000);
					break;
				case 1 :
					back();
					delay_ms(1000);
					break;
				case 2 :
					left();
					delay_ms(1000);
					break;
				case 3 :
					right();
					delay_ms(1000);
					break;
				default:
					delay_ms(1000);
					break;
			}		
		}
		UART5_RX_CONUT=0;		//清除接收计数
		for(int i=0;i<USART_REC_LEN;i++)
		{
			UART5_RX_BUF[i]=0;		//清空接收BUF
		}
		for(int i=0;i<3;i++)
		{
			_receiveBuf[i]=0;		//清空接收BUF
		}
	}

}


void forward(void)
{
	PDout(14) = 0;//左
	PDout(13) = 1;
	PCout(9) = 0;//右
	PDout(12) = 1;
}

void back(void)
{
	PDout(14) = 1;//左
	PDout(13) = 0;
	PCout(9) = 1;//右
	PDout(12) = 0;
}

void left(void)
{
	PDout(14) = 1;//左
	PDout(13) = 1;
	PCout(9) = 0;//右
	PDout(12) = 1;	
}

void right(void)
{
	PDout(14) = 0;//左
	PDout(13) = 1;
	PCout(9) = 1;//右
	PDout(12) = 1;
}
