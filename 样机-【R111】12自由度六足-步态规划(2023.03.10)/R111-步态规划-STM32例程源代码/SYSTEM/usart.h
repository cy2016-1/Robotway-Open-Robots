#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 
#include "timer.h"
#include "stdarg.h"	

//USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//EN_USART1_RX��ʹ�ܷ�ʽ
////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//�����������ֽ��� 200

	  	
extern	u8 USART_TX_BUF[USART_REC_LEN];
extern	u8 USART_RX_BUF[USART_REC_LEN];
extern	vu16 USART_RX_STA;

extern void usart_send(unsigned char c);

extern void usart_send_data(char *buf);

void usart_init(u32 bound);
#endif

