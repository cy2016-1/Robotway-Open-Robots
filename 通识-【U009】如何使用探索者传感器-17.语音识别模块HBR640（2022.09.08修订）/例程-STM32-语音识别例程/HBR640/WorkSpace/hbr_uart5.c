#include "sys.h"
#include "hbr_uart5.h"	
#include "stdio.h"
#include "string.h"
#include "led.h"
#include "hbr640.h"

void UART5_INIT(void)
{
	GPIO_InitTypeDef Gpio_Value;
	USART_InitTypeDef Uart5_Value;
	NVIC_InitTypeDef Nvic_Value;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2, GPIO_AF_UART5);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12, GPIO_AF_UART5);
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_AF;
	Gpio_Value.GPIO_OType = GPIO_OType_PP;
	Gpio_Value.GPIO_Pin = GPIO_Pin_2;
	Gpio_Value.GPIO_PuPd = GPIO_PuPd_UP;
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &Gpio_Value);
	
	Gpio_Value.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOC, &Gpio_Value);
	
	Uart5_Value.USART_BaudRate = 115200;
	Uart5_Value.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	Uart5_Value.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	Uart5_Value.USART_Parity = USART_Parity_No;
	Uart5_Value.USART_StopBits = USART_StopBits_1;
	Uart5_Value.USART_WordLength = USART_WordLength_8b;
	USART_Init(UART5,&Uart5_Value);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	Nvic_Value.NVIC_IRQChannel = UART5_IRQn;
	Nvic_Value.NVIC_IRQChannelCmd = ENABLE;
	Nvic_Value.NVIC_IRQChannelPreemptionPriority = 0;
	Nvic_Value.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&Nvic_Value);
	
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(UART5, ENABLE);
}



//UART5
void UART5_Send_Byte(unsigned char c)
{
	USART_SendData(UART5, c);//ͨ��USART1���ͱ���c���洢������
	while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);//����USART1�ķ��������Ƿ�ɹ�
	USART_ClearFlag(UART5, USART_FLAG_TC);//���USART1�ķ��ͳɹ��ı�־
}

void UART5_Send_Data(char *buf)
{

	while(*buf != '\0')
	{	
		UART5_Send_Byte(*buf);
		buf++;
	}

}

char UART5_Recv_Byte(void)
{
	unsigned char ret = 0;
	
	if(USART_GetFlagStatus(UART5, USART_FLAG_RXNE) == SET)//�ж�USART1�Ƿ�ӵ�������
	{
		ret = USART_ReceiveData(UART5);//�ѽ��յ������ݴ洢��ret������
		USART_ClearFlag(UART5, USART_FLAG_RXNE);//���USART1�ı�־״̬
	}
	
	return ret;//���ؽ��յ�������
}

char UART5_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
u8	UART5_RX_CONUT = 0;				//	�����յ����ݵļ���

void UART5_IRQHandler(void)                	//����1�жϷ������
{
	char data;
	
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)//�Ƿ�Ϊ�����ж�
	{
	  data=USART_ReceiveData(UART5);				//��ȡ�������ݣ�һ�ֽڵ����ݣ�
	  UART5_RX_BUF[UART5_RX_CONUT++]=data;			//���յ������ݷŵ�����BUF
		_flag = 1;
	}
	if(USART_GetFlagStatus(UART5,USART_FLAG_ORE) == SET) // ��� ORE ��־�����������־��
	{
      USART_ClearFlag(UART5,USART_FLAG_ORE);			//	��������־λ
	}
	
	USART_ClearITPendingBit(UART5,USART_IT_ORE);

	for(int i=0; i < 3; i++){
		_receiveBuf[i] = UART5_RX_BUF[i];
	}	
	
//		UART5_RX_BUF[UART5_RX_CONUT++]=UART5_Recv_Byte();
//		_flag = 1;
	
//	else{
//		_flag = 0;
//	}
//	for(int i=0; i < 3; i++){
//		_receiveBuf[i] = UART5_RX_BUF[i];
//	}	
//	
//	USART_ClearITPendingBit(UART5,USART_IT_ORE);
}


