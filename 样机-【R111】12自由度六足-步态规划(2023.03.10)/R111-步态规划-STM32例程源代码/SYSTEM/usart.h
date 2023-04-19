#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 
#include "timer.h"
#include "stdarg.h"	

//USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//EN_USART1_RX的使能方式
////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//定义最大接收字节数 200

	  	
extern	u8 USART_TX_BUF[USART_REC_LEN];
extern	u8 USART_RX_BUF[USART_REC_LEN];
extern	vu16 USART_RX_STA;

extern void usart_send(unsigned char c);

extern void usart_send_data(char *buf);

void usart_init(u32 bound);
#endif

