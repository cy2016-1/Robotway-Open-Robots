/*------------------------------------------------------------------------------------
  ��Ȩ˵����Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by ������ 2023-03-10 https://www.robotway.com/
  ------------------------------*/
#include "sys.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "a4988.h"
#include "pwm.h"
#include "key.h"
#include "oled.h"
#include "stdbool.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʼ����ʱ��168ΪCPU����Ƶ��
	usart_init(9600); 	//���ڳ�ʼ�� 
	usart3_init(9600);
	LED_Init();	//LED�Ƴ�ʼ��
	Stepper_Motor_Init(0); //����������ų�ʼ��
	KEY_Init();
	OLED_Init(1);	
	delay_ms(1000);
	TIM4_PWM_Init(20000-1,84-1);
	Put_Up();delay_ms(1500);
  int receive_touch[2] = {0,0};
	bool Flags_draw = false;
	
	OLED_Clear();
	OLED_ShowString(30,3,(unsigned char*)"Wait...",16);
	
	while(1)
	{
		if(touch_keys(1) == 1)
		{					
		  delay_ms(350);
			receive_touch[0] += 1;
			Flags_draw = false;
		}
		
		if(touch_keys(2) == 1)
		{
			if(Flags_draw)
			{
				receive_touch[1] = 0;			
			}
			else
			{
		    delay_ms(350);
			  receive_touch[1] = 1;	
			}
		}
		
		
	  if(receive_touch[0]==1)
		{
				//printf("data:%d",receive_touch[0]);
			  OLED_Clear();
			  OLED_ShowString(0,0,(unsigned char*)"Sin",16);
				if(receive_touch[1] == 1)
				{
					OLED_Clear();
					OLED_ShowString(0,0,(unsigned char*)"Sin",16);
					OLED_ShowString(0,4,(unsigned char*)"Start",16);
					receive_touch[1]=0;
					delay_ms(1000);
			    Put_Down();delay_ms(1000);
			    drawSin();
			    Put_Up();delay_ms(1000);					
				}				
		}
			if(receive_touch[0]==2)
			{
				//printf("data:%d",receive_touch[0]);
			  OLED_Clear();
			  OLED_ShowString(0,0,(unsigned char*)"Triangle",16);
				if(receive_touch[1] == 1)
				{
					OLED_Clear();
					OLED_ShowString(0,0,(unsigned char*)"Triangle",16);
					OLED_ShowString(0,4,(unsigned char*)"Start",16);
					receive_touch[1]=0;
			    Put_Down();delay_ms(1000);
			    drawTriangle();
			    Put_Up();delay_ms(1000);				
				}		
			}


	  if(receive_touch[0]==3)
		{
				//printf("data:%d",receive_touch[0]);
			  OLED_Clear();
			  OLED_ShowString(0,0,(unsigned char*)"Rect",16);
				if(receive_touch[1] == 1)
				{
					//receive_touch[0]=0;
					OLED_Clear();
					OLED_ShowString(0,0,(unsigned char*)"Rect",16);
					OLED_ShowString(0,4,(unsigned char*)"Start",16);
					receive_touch[1]=0;
			    Put_Down();delay_ms(1000);
			    drawRect();
			    Put_Up();delay_ms(1000);				
				}
		}


	  if(receive_touch[0]==4)
		{
			  OLED_Clear();
			  OLED_ShowString(0,0,(unsigned char*)"ThreeLeaf",16);
				if(receive_touch[1] == 1)
				{
					OLED_Clear();
					OLED_ShowString(0,0,(unsigned char*)"ThreeLeaf",16);
					OLED_ShowString(0,4,(unsigned char*)"Start",16);
					receive_touch[1]=0;
			    //Put_Down();delay_ms(1000);
			    drawThreeLeaf();
			    Put_Up();delay_ms(1000);					
				}
		}

	  if(receive_touch[0]==5)
		{
			  OLED_Clear();
			  OLED_ShowString(8,3,(unsigned char*)"Draw Line End",16);
				receive_touch[0]=0;
			  receive_touch[1]=0;
			  Flags_draw = true;
		}	
  }
}



