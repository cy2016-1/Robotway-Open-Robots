#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 

/*����ķ�ʽ��ͨ��ֱ�Ӳ����⺯����ʽ��ȡIO*/
#define KEY0 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)	//PA1
#define KEY1 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)	//PA3
#define KEY2 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)	//PA5

extern void KEY_Init(void);	//IO��ʼ��
extern u8 KEY_Scan(u8);  		//����ɨ�躯��	
extern int touch_keys(int mode);
#endif
