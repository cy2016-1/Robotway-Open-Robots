#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 


//USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//EN_USART1_RX��ʹ�ܷ�ʽ
////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//�����������ֽ��� 200

	  	
extern u8 	USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8	USART_RX_CONUT;				//	�����յ����ݵļ���

void uart_init(u32 bound);
#endif


