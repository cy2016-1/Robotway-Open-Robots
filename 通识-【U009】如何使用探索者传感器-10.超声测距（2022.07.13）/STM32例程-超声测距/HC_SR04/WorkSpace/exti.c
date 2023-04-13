#include "exti.h"
#include "timer.h"
#include "led.h"

#define Trig GPIO_Pin_4		//���������
#define Echo GPIO_Pin_5		//����������

float Distance;

void EXTI5_Init(void)
{
	GPIO_InitTypeDef 	 GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��GPIOAʱ��	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);	//ʹ��SYSCFGʱ��
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource5);//���ӵ��ж���5
	
	GPIO_InitStructure.GPIO_Pin = Echo; //GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��

	GPIO_InitStructure.GPIO_Pin = Trig; //GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��
	
	
	/* ����EXTI_Line4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);//����
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�4
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//����
}



void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) == SET){//���ж�4����
		TIM_SetCounter(TIM2,0);//��ʱ����������
		TIM_Cmd(TIM2,ENABLE);//������ʱ��
		while(GPIO_ReadInputDataBit(GPIOA,Echo));//�ȴ�����
		TIM_Cmd(TIM2,DISABLE);//�رն�ʱ��
		Distance= TIM_GetCounter(TIM2)*340/400;// distance = t*340/2		t = count*1/20000	1m=100cm  �������
		EXTI_ClearITPendingBit(EXTI_Line5);//���LINE4�ϵ��жϱ�־λ  
	}
}



void Wave_SRD_Strat4(void)
{
  GPIO_SetBits(GPIOA,Trig);   //��Trig����Ϊ�ߵ�ƽ
	delay_us(20);               //��������10us����������������ģ�鹤��
	GPIO_ResetBits(GPIOA,Trig); 
}


