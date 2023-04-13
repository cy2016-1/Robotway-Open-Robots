#ifndef __HBR_UART5_H
#define __HBR_UART5_H
#include "stm32f4xx_conf.h"
#include "sys.h" 
#include "stdio.h"

#define USART_REC_LEN  			200  	//�����������ֽ��� 200

	  	
extern char UART5_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8	UART5_RX_CONUT;				//	�����յ����ݵļ���
extern u8 UART5_TX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8	UART5_TX_CONUT;				//	�����յ����ݵļ���

extern void UART5_INIT(void);
extern void UART5_Send_Byte(unsigned char c);
extern void UART5_Send_Data(char *buf);
extern char UART5_Recv_Byte(void);

#endif


