#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 
#include "stdarg.h"	

//USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//EN_USART1_RX��ʹ�ܷ�ʽ
////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			20  	//�����������ֽ��� 200

extern	u8 USART3_TX_BUF[USART_REC_LEN];
extern	u8 USART3_RX_BUF[USART_REC_LEN];
extern	vu16 USART3_RX_STA;
	  	
extern char USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8	USART_RX_CONUT;				//	�����յ����ݵļ���
extern void u3_printf(char* fmt,...);


void usart3_init(u32 bound);
extern void usart_init(u32 bound);

extern void drawLine_new(float x1, float y1);
extern void drawLine(float x1, float y1);
extern void processIncomingLine( char* line, int charNB );
#endif


