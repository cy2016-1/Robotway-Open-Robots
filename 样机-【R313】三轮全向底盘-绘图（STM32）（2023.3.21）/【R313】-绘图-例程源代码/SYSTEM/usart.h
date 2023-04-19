#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 
#include "stdarg.h"	

//USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//EN_USART1_RX的使能方式
////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			20  	//定义最大接收字节数 200

extern	u8 USART3_TX_BUF[USART_REC_LEN];
extern	u8 USART3_RX_BUF[USART_REC_LEN];
extern	vu16 USART3_RX_STA;
	  	
extern char USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u8	USART_RX_CONUT;				//	串口收到数据的计数
extern void u3_printf(char* fmt,...);


void usart3_init(u32 bound);
extern void usart_init(u32 bound);

extern void drawLine_new(float x1, float y1);
extern void drawLine(float x1, float y1);
extern void processIncomingLine( char* line, int charNB );
#endif


