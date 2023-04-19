#include "key.h"
#include "delay.h" 


void KEY_Init(void)			//������ʼ������
{	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5; //KEY ��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//��������Ҳ������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA	 
} 
//��������KEY_Scan
//����ֵ������״̬ 0��û���κΰ������� 1����������
//������mode:0,��֧��������;1,֧��������;
//���ã��жϰ����Ƿ��£���������״̬��ֵ����ʽ����
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=0;//�������ɿ���־  
	
	if(mode)
		key_up=1;  			//֧������		  
	if(key_up){
		delay_ms(10);		//ȥ���� 
		key_up=0;
		if(KEY0==0)
			return 1;			//��������
	}else if(KEY0==1)
		key_up=1;	
	return 0;					// �ް�������
}

int touch_keys(int mode)
{
	switch(mode)
	{
		case 1:
			     //{
			       if(KEY0 == 0){return 1;}
	           else{return 0;}
             //break;
		       //}
		case 2:
			//{
			if(KEY1 == 0){return 1;}
	    else{return 0;}
      //break;
		//}
		case 3:
			//{
			if(KEY2 == 0){return 1;}
	    else{return 0;}
      //break;
		//}
	}
	return -1;
}


















