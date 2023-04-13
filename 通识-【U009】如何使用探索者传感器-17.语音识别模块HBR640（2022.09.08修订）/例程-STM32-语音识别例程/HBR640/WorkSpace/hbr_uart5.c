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
	USART_SendData(UART5, c);//通过USART1发送变量c所存储的数据
	while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);//检验USART1的发送数据是否成功
	USART_ClearFlag(UART5, USART_FLAG_TC);//清除USART1的发送成功的标志
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
	
	if(USART_GetFlagStatus(UART5, USART_FLAG_RXNE) == SET)//判断USART1是否接到了数据
	{
		ret = USART_ReceiveData(UART5);//把接收到的数据存储到ret变量中
		USART_ClearFlag(UART5, USART_FLAG_RXNE);//清除USART1的标志状态
	}
	
	return ret;//返回接收到的数据
}

char UART5_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
u8	UART5_RX_CONUT = 0;				//	串口收到数据的计数

void UART5_IRQHandler(void)                	//串口1中断服务程序
{
	char data;
	
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)//是否为接收中断
	{
	  data=USART_ReceiveData(UART5);				//读取串口数据（一字节的数据）
	  UART5_RX_BUF[UART5_RX_CONUT++]=data;			//将收到的数据放到接收BUF
		_flag = 1;
	}
	if(USART_GetFlagStatus(UART5,USART_FLAG_ORE) == SET) // 检查 ORE 标志（串口溢出标志）
	{
      USART_ClearFlag(UART5,USART_FLAG_ORE);			//	清除溢出标志位
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


