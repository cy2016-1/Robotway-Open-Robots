/*------------------------------------------------------------------------------------
  ��Ȩ˵����Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by ������ 2023-02-16 https://www.robotway.com/
  ------------------------------*/
#include "sys.h" 
#include "led.h" 
#include "stdio.h"
#include "delay.h"
#include "usart.h"
#include "stdio.h"
#include "core_cm4.h"
#include "string.h"
#include "stdlib.h"
#include "pwm.h"
#include "timer.h"
#include "math.h"

/*
		  7			 1
	    |      |
 6----|			 |----0
			|			 |
			9			 3
	    |      |
 8----|			 |----2
			|			 |
			11			 5
	    |      |
10----|			 |----4
			|			 |
*/


float Ang[12] = {100, 85, 90, 90, 90, 80, 100, 90, 95, 90, 90, 95};
int Ang_Init[12] = {100, 85, 90, 90, 90, 80, 100, 90, 95, 90, 90, 95};
float data_f[12] = {0};

void split(char *src,const char *separator,char **dest,int *num);//�ַ�����ֺ���
float sort(float data[12]);//��������С->��
float find_min(float *de);//Ѱ����Сֵ����
void Set_Ang(float, float, float, float, float, float, float, float, float, float, float, float);//���ö����ת�ǶȺ���
void Steering_Gear_Init(void);//��е�۳�ʼ��λ�ú���
void Steering_Gear_Angle(u8 num, float ang);//����������ƺ���
void Steering_Gear_Ang_Pwm1(float data[12]);//��е���ƶ�����

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);				//��ʼ����ʱ��168ΪCPU����Ƶ��
	usart_init(115200); 		//���ڳ�ʼ�� 
	LED_Init();							//��ʼ��LED��				
	TIM1_PWM_Init(20000-1, 168-1);
	TIM4_PWM_Init(20000-1,84-1);
	TIM3_PWM_Init(20000-1,84-1);	
	TIM11_PWM_Init(20000-1,168-1);
	TIM12_PWM_Init(20000-1,84-1);
	Steering_Gear_Init();//����λ�ó�ʼ��
	while(1)
	{		
		Set_Ang(80,85,110,90,110,80,80,90,115,90,70,95);
		Steering_Gear_Ang_Pwm1(data_f);	
		delay_ms(1000);
		while(1){		
			Set_Ang(90,100,105,75,110,95,90,105,105,75,80,110);
			Steering_Gear_Ang_Pwm1(data_f);
			Set_Ang(70,100,70,75,130,95,120,105,120,75,120,110);
			Steering_Gear_Ang_Pwm1(data_f);			
			Set_Ang(70,70,70,105,130,65,120,75,120,105,120,80);
			Steering_Gear_Ang_Pwm1(data_f);
			Set_Ang(90,70,105,105,110,65,90,75,105,105,80,80);
			Steering_Gear_Ang_Pwm1(data_f);				
			Set_Ang(120,70,120,105,60,65,80,75,70,105,70,80);
			Steering_Gear_Ang_Pwm1(data_f);
			Set_Ang(120,100,120,75,60,95,80,105,70,75,70,110);
			Steering_Gear_Ang_Pwm1(data_f);				
		}
		
	}
}

void split(char *src,const char *separator,char **dest,int *num) 
{
	char *pNext;
	int count = 0;
	
	if (src == NULL || strlen(src) == 0)//�ַ���Ϊ�ջ�����������־
		return;
	if (separator == NULL || strlen(separator) == 0)//�ָ���Ϊ��
		return;    
	pNext = strtok(src,separator);//�ַ����ָ�
	while(pNext != NULL) {
		*dest++ = pNext;
		++count;
		pNext = strtok(NULL,separator);  
	}  
	*num = count;
} 

//�����������г�Ա����С�����˳��������У���������Сֵ
float sort(float data1[12])
{
	float array[12] = {0};
	int i = 0;
	int j = 0;
	int temp;
	
	for(int i=0; i < 12; i++){
		array[i] = data1[i];
	} 
	
	for ( i = 0; i < 12; i++){
		for ( j = 0; j < 11-i; j++){
			if(array[j]>array[j+1]){
				temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
			}
		}			
	}	
	return find_min(array);
}
//Ѱ�������е���Сֵ
float find_min(float *de)
{
	if((int)*de != 0)
		return *de;
	find_min(++de);
	
}
//�����鸳ֵ
void Set_Ang(float ang1, float ang2, float ang3, float ang4, float ang5, float ang6, float ang7, float ang8, float ang9, float ang10, float ang11, float ang12)
{
	data_f[0] = ang1;
	data_f[1] = ang2;
	data_f[2] = ang3;
	data_f[3] = ang4;
	data_f[4] = ang5;
	data_f[5] = ang6;
	data_f[6] = ang7;
	data_f[7] = ang8;
	data_f[8] = ang9;
	data_f[9] = ang10;
	data_f[10] = ang11;
	data_f[11] = ang12;
}

//������λ��֮����Ҫ����ƶ��Ķ���ת��Ϊ�ಽ��Ȼ��ֲ����
void Steering_Gear_Ang_Pwm1(float data[12])
{
	float den = 0;
	float dif[12] = {0};
	float	ang[12] = {0};		
	
	//��������λ��֮��Ĳ�ֵ
	for(int i=0; i < 12; i++){
		dif[i] = fabs(data[i] - Ang[i]);
	}

	//�õ���С��ֵ
	den = sort(dif);

	//����12�����ÿ���ƶ�����С����
	if((int)den == 0){
		for(int i=0; i < 12; i++)
			ang[i] = 0;
	}else{
		for(int i=0; i < 12; i++){			
			ang[i] = (data[i] - Ang[i])/den;
		}

		for(int i=0; i<den; i++){
			for(int j=0; j < 12; j++)
				Ang[j] += ang[j];
			//�Զ���������λ�����ƣ���ֹ�����ת
			for(int g=0; g < 12; g++){
				if(Ang[g] < 0)
					Ang[g] = 0;
				else if(Ang[g] > 180)
					Ang[g] = 180;
			}
			//�������
			for(int k=0; k<12; k++){		
				Steering_Gear_Angle(k, Ang[k]);
			}
		}
	}
}

void Steering_Gear_Angle(u8 num, float ang)
{
	u32 Ang = 0;
	
	Ang = 500 + ang*2000/180;
	
	switch(num){
		case 0 :
			TIM_SetCompare1(TIM1, Ang);				//�޸ıȽ�ֵ���޸�ռ�ձ�
			break;
		case 1 :
			TIM_SetCompare2(TIM1, Ang);				//�޸ıȽ�ֵ���޸�ռ�ձ�			
			break;
		case 2 :
			TIM_SetCompare3(TIM1, Ang);				//�޸ıȽ�ֵ���޸�ռ�ձ�		
      break;
		case 3 :
			TIM_SetCompare4(TIM1, Ang);				//�޸ıȽ�ֵ���޸�ռ�ձ�
			break;
		case 4 :
			TIM_SetCompare1(TIM3, Ang);				//�޸ıȽ�ֵ���޸�ռ�ձ�			
			break;
		case 5 :
			TIM_SetCompare2(TIM3, Ang);				//�޸ıȽ�ֵ���޸�ռ�ձ�	
			break;
		case 6 :
			TIM_SetCompare4(TIM4, Ang);				//�޸ıȽ�ֵ���޸�ռ�ձ�
			break;
		case 7 :
			TIM_SetCompare3(TIM4, Ang);				//�޸ıȽ�ֵ���޸�ռ�ձ�
			break;
		case 8 :
			TIM_SetCompare2(TIM4, Ang);				//�޸ıȽ�ֵ���޸�ռ�ձ�			
			break;
		case 9 :
			TIM_SetCompare2(TIM12, Ang);				//�޸ıȽ�ֵ���޸�ռ�ձ�		
      break;
		case 10 :
			TIM_SetCompare1(TIM12, Ang);				//�޸ıȽ�ֵ���޸�ռ�ձ�
			break;
		case 11 :
			TIM_SetCompare1(TIM11, Ang);				//�޸ıȽ�ֵ���޸�ռ�ձ�			
			break;
		default:
			break;
	}
	delay_ms(1);
}
//������ʼλ��
void Steering_Gear_Init(void)
{
	for(int i=0; i < 12; i++){
		Steering_Gear_Angle(i,Ang_Init[i]);
	}
	delay_ms(1000);
}


