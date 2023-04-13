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
	delay_init(168);		//��ʼ����ʱ��168ΪCPU����Ƶ��
	usart_init(115200); 	//���ڳ�ʼ�� 
	UART5_INIT();
	LED_Init();					//��ʼ��LED��
	MOTOR_Init();				//�����ʼ��
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
		UART5_RX_CONUT=0;		//������ռ���
		for(int i=0;i<USART_REC_LEN;i++)
		{
			UART5_RX_BUF[i]=0;		//��ս���BUF
		}
		for(int i=0;i<3;i++)
		{
			_receiveBuf[i]=0;		//��ս���BUF
		}
	}

}


void forward(void)
{
	PDout(14) = 0;//��
	PDout(13) = 1;
	PCout(9) = 0;//��
	PDout(12) = 1;
}

void back(void)
{
	PDout(14) = 1;//��
	PDout(13) = 0;
	PCout(9) = 1;//��
	PDout(12) = 0;
}

void left(void)
{
	PDout(14) = 1;//��
	PDout(13) = 1;
	PCout(9) = 0;//��
	PDout(12) = 1;	
}

void right(void)
{
	PDout(14) = 0;//��
	PDout(13) = 1;
	PCout(9) = 1;//��
	PDout(12) = 1;
}
