/*------------------------------------------------------------------------------------
  ��Ȩ˵����Copyright 2023 Robottime(Beijing) Technology Co., Ltd. All Rights Reserved.
           Distributed under MIT license.See file LICENSE for detail or copy at
           https://opensource.org/licenses/MIT
           by ������ 2023-02-07 https://www.robotway.com/
  ------------------------------*/
#include "sys.h" 
#include "led.h" 
#include "pwm.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "stdlib.h"

void split(char *src,const char *separator,char **dest,int *num);	//�ַ�����ֺ���
void Steering_Gear_Angle(u8 num, u16 ang);	//ʱ������20ms ���ƶ���ƶ�
void mysplite(char *src, char **p, const char *separator, const char *separator1, int *num);	//�ַ�����ֺ���
void buf_init(void);	//��ս�������
void all_servo_angle_init();
void all_servo_move(float value0, float value1, float value2, float value3,float value4,float value5,float _f,int _delay_time_servos);

char *pwm[30];
char *tim[2] = {0};
const int servo_num = 6;
float value_init[6]={1200, 950, 1350, 1800, 1500, 1500};
float f = 50.0;
int delay_time_servo = 10;

int main(void)
{
	u8 rxlen;
	int num = 0, num1 = 0;
	delay_init(168);		//��ʼ����ʱ��168ΪCPU����Ƶ��
	uart_init(115200); 	//���ڳ�ʼ�� 
	LED_Init();					//��ʼ��LED��
	TIM12_PWM_Init(20000-1,84-1);
	TIM11_PWM_Init(20000-1,168-1);
	TIM10_PWM_Init(20000-1,168-1);
	TIM9_PWM_Init(20000-1,168-1);
	//42M/42=1Mhz�ļ���Ƶ��,��װ��ֵ20000������PWMƵ��Ϊ 1M/20000=50hz.  

	while(1)
	{
		all_servo_angle_init();
		all_servo_move(1200, 950, 1350, 1800, 1500, 1550,f,delay_time_servo);//��ʼ��������ֱ��״̬��
		all_servo_move(1200, 950, 1350, 1800, 1500, 1550,f,delay_time_servo);
		all_servo_move(1200, 1086, 620, 1480, 2480, 1550,f,delay_time_servo);//delay_ms(1000);//׼��ץȡ
		all_servo_move(1200, 1086, 620, 1480, 2480, 1360,f,delay_time_servo);delay_ms(300);//ץȡ		
		all_servo_move(1200,  650,  850, 2200, 1500,1360,f,delay_time_servo);delay_ms(300);//�м䶯��		
		all_servo_move(1700,  1086,  620, 1480, 600,1360,f,delay_time_servo);delay_ms(300);//ת������
		all_servo_move(1700,  1086,  620, 1480, 600,1550,f,delay_time_servo);delay_ms(300);//�ͷ�
		all_servo_move(1200,  650,  850, 2200, 1500,1550,f,5);delay_ms(30);//�м䶯��
		all_servo_move(1200,  950, 1350, 1800, 1500, 1500,f,5);delay_ms(300);//��ʼ��������ֱ��״̬��		
		while(1){
			
		}
	}
}


void buf_init(void)
{
	for(int i = 0; i < 20; i++){
		pwm[i] = 0;
	}
	for(int i = 0; i < 2; i++){
		tim[i] = 0;
	}			
	for(int i = 0; i < USART_REC_LEN; i++){
		USART_RX_BUF[i] = 0;
	}
}

void mysplite(char *buffer, char **p, const char *separator, const char *separator1, int *num)
{
	int in = 0;
  char *buf = buffer;
  char *outer_ptr = NULL;
  char *inner_ptr = NULL;
	
  while ((p[in] = strtok_r(buf, separator, &outer_ptr)) != NULL)
  {
    buf = p[in];
    while ((p[in] = strtok_r(buf, separator1, &inner_ptr)) != NULL)
    {
      in++;
      buf = NULL;
    }
    buf = NULL;
  }
	p[in] = strtok(p[in], "T");
	*num = in;
}

void split(char *src,const char *separator,char **dest,int *num) 
{
	char *pNext;
	int count = 0;
	
	if (src == NULL || strlen(src) == 0)
		return;
	if (separator == NULL || strlen(separator) == 0)
		return;    
	pNext = strtok(src,separator);
	while(pNext != NULL) {
		*dest++ = pNext;
		++count;
		pNext = strtok(NULL,separator);  
	}  
	*num = count;
}  


void Steering_Gear_Angle(u8 num, u16 ang)
{
	switch(num){
		case 0 :
			TIM_SetCompare2(TIM12, ang);	//�޸ıȽ�ֵ���޸�ռ�ձ�
			break;
		case 1 :
			TIM_SetCompare1(TIM12, ang);	//�޸ıȽ�ֵ���޸�ռ�ձ�
			break;
		case 2 :
			TIM_SetCompare1(TIM11, ang);	//�޸ıȽ�ֵ���޸�ռ�ձ�
			break;
		case 3 :
			TIM_SetCompare1(TIM10, ang);	//�޸ıȽ�ֵ���޸�ռ�ձ�
			break;
		case 4 :
			TIM_SetCompare2(TIM9, ang);	//�޸ıȽ�ֵ���޸�ռ�ձ�
			break;
		case 5 :
			TIM_SetCompare1(TIM9, ang);	//�޸ıȽ�ֵ���޸�ռ�ձ�
			break;
		default:
			break;
	}
	delay_ms(100);
}

void all_servo_angle_init()
{
	TIM_SetCompare2(TIM12, value_init[0]);
	TIM_SetCompare1(TIM12, value_init[1]);
	TIM_SetCompare1(TIM11, value_init[2]);
	TIM_SetCompare1(TIM10, value_init[3]);
	TIM_SetCompare2(TIM9,  value_init[4]);
	TIM_SetCompare1(TIM9,  value_init[5]);
}


void all_servo_move(float value0, float value1, float value2, float value3,float value4,float value5,float _f,int _delay_time_servos)
{
	float value_arguments[6] = {value0, value1, value2, value3, value4, value5};
	float value_delta[servo_num];
  for(int i=0;i<servo_num;i++)
  {
    value_delta[i] = (value_arguments[i] - value_init[i]) / _f;
  }
  for(int i=0;i<f;i++)
  {
    for(int k=0;k<servo_num;k++)
    {
      value_init[k] = value_delta[k] == 0 ? value_arguments[k] : value_init[k] + value_delta[k];
    }
    
    for(int j=0;j<servo_num;j++)
    {
			if(j==0){TIM_SetCompare2(TIM12, value_init[0]);}
			if(j==1){TIM_SetCompare1(TIM12, value_init[1]);}
			if(j==2){TIM_SetCompare1(TIM11, value_init[2]);}
			if(j==3){TIM_SetCompare1(TIM10, value_init[3]);}
			if(j==4){TIM_SetCompare2(TIM9,  value_init[4]);}
			if(j==5){TIM_SetCompare1(TIM9,  value_init[5]);}
			delay_ms(_delay_time_servos);
    }
  }	
}


