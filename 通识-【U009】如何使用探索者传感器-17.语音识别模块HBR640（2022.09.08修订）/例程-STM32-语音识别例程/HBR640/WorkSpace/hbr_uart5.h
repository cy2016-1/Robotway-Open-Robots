#ifndef __HBR_UART5_H
#define __HBR_UART5_H
#include "stm32f4xx_conf.h"
#include "sys.h" 
#include "stdio.h"

#define USART_REC_LEN  			200  	//定义最大接收字节数 200

	  	
extern char UART5_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u8	UART5_RX_CONUT;				//	串口收到数据的计数
extern u8 UART5_TX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u8	UART5_TX_CONUT;				//	串口收到数据的计数

extern void UART5_INIT(void);
extern void UART5_Send_Byte(unsigned char c);
extern void UART5_Send_Data(char *buf);
extern char UART5_Recv_Byte(void);

#endif


