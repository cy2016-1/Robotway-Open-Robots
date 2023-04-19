#include "a4988.h"
#include "delay.h"


int stepperDir_pin[4] = {9, 2, 11, 4};
int stepperStp_pin[4] = {8, 1, 10, 3};
int stepper_delay = 10;
int stepper_delay1 = 100;
int myabs(int a);

void Stepper_Motor_Init(int en)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOD时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_8|GPIO_Pin_9;//对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//对应引脚
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化
	
	SMEN = en;
}


void All_stepper_move(int stepper_x, int stepper_y, int stepper_z, int stepper_a)
{
	unsigned int step_flag[4]={1,1,1,1};
	unsigned int stepper_current[4] = {1,1,1,1};
	const unsigned int stepper_state[4] = {0,0,0,0};
	int step_distance[4] = {0,0,0,0};
	PDout(9)  = stepper_x >0 ? 1 : 0; //x_dir
	PEout(2)  = stepper_y >0 ? 1 : 0; //y_dir
	PDout(11) = stepper_z >0 ? 1 : 0; //z_dir
	PEout(4)  = stepper_a >0 ? 1 : 0; //a_dir
	
	PDout(8)  = stepper_current[0];   //x_stp
	PEout(1)  = stepper_current[1];   //y_stp
	PDout(10) = stepper_current[2];   //z_stp
	PEout(3)  = stepper_current[3];   //a_stp
	 
	step_distance[0] = myabs(stepper_x); //x_distance
	step_distance[1] = myabs(stepper_y); //y_distance
	step_distance[2] = myabs(stepper_z); //z_distance
	step_distance[3] = myabs(stepper_a); //a_distance
	
	int start_count = 0;
	int end_count = 0;
	
	while( step_flag[0] || step_flag[1] || step_flag[2] || step_flag[3] )
	{
		if(step_distance[0] < 0){ stepper_current[0] = 0;step_flag[0]=0; }
		if(step_distance[1] < 0){ stepper_current[1] = 0;step_flag[1]=0; }
    if(step_distance[2] < 0){ stepper_current[2] = 0;step_flag[2]=0; }
    if(step_distance[3] < 0){ stepper_current[3] = 0;step_flag[3]=0; }
	    PDout(8)  = stepper_current[0];//x_stp
	    PEout(1)  = stepper_current[1];//y_stp
	    PDout(10) = stepper_current[2];//z_stp
	    PEout(3)  = stepper_current[3];//a_stp	
		  delay_us(stepperPulse_delay);
		
	    PDout(8)  = stepper_state[0];  //x_stp
	    PEout(1)  = stepper_state[1];  //y_stp
	    PDout(10) = stepper_state[2];  //z_stp
	    PEout(3)  = stepper_state[3];  //a_stp	
		  delay_us(stepperPulse_delay);	
		
    step_distance[0]--;
    step_distance[1]--;	
    step_distance[2]--;
    step_distance[3]--;			
	}
}



void step_move_x(int stepper_x)
{
	PDout(9)  = stepper_x >0 ? 1 : 0; //x_dir
	PDout(8)  = 1;//x_stp
	delay_us(50);
	PDout(8)  = 0;//x_stp
	delay_us(50);	
}

void step_move_y(int stepper_y)
{
	PEout(2)  = stepper_y >0 ? 1 : 0; //y_dir
	PEout(1)  = 1;//x_stp
	delay_us(50);
	PEout(1)  = 0;//x_stp
	delay_us(50);		
}

void step_move_z(int stepper_z)
{
	PDout(11) = stepper_z >0 ? 1 : 0; //z_dir
	PDout(10)  = 1;//x_stp
	delay_us(50);
	PDout(10)  = 0;//x_stp
	delay_us(50);	
}

void step_move_a(int stepper_a)
{
	PEout(4)  = stepper_a >0 ? 1 : 0; //a_dir
	PEout(3)  = 1;//x_stp
	delay_us(50);
	PEout(3)  = 0;//x_stp
	delay_us(50);		
}

void move_test()
{
	for(int i=0;i<3200;i++)
	{
		
	PDout(9)  = 0; //x_dir
	PEout(2)  = 1; //y_dir
	PEout(4)  = 0; //a_dir
	PDout(11) = 1; //z_dir
		
		
//	PDout(8)  = 1;//x_stp
//	PEout(3)  = 1; //a_stp
//	delay_us(500);	
//	PDout(8)  = 0;//x_stp
//	PEout(3)  = 0; //a_stp
//  delay_us(500);		
		

	PDout(8)  = 1;//x_stp
	PEout(1)  = 1;//y_stp
	delay_us(500);	
	PDout(8)  = 0;//x_stp
	PEout(1)  = 0;//y_stp
  delay_us(500);
		
	PDout(10)  = 1;//z_stp
	PEout(3)  = 1; //a_stp
	delay_us(500);
	
		
		
	PDout(10)  =0;//z_stp
	PEout(3)  = 0;//a_stp
	delay_us(500);
		
//	if(i%2 == 0)
//	{
//	  PDout(8)  = 1;//x_stp
//	  PEout(1)  = 1;//x_stp
//	  PDout(10)  = 1;//x_stp
//	  PEout(3)  = 1;//x_stp
//	  delay_us(500);
//	
//	  PDout(8)  = 0;//x_stp
//	  PEout(1)  = 0;//x_stp
//	  PDout(10)  =0;//x_stp
//	  PEout(3)  = 0;//x_stp
//	  delay_us(500);
//	}
//  else{
//	  PDout(3)  = 1;//x_stp
//	  PEout(10)  = 1;//x_stp
//	  PDout(1)  = 1;//x_stp
//	  PEout(8)  = 1;//x_stp
//	  delay_us(500);
//	
//	  PDout(3)  = 0;//x_stp
//	  PEout(10)  = 0;//x_stp
//	  PDout(1)  =0;//x_stp
//	  PEout(8)  = 0;//x_stp
//	  delay_us(500);
//	}		
		

	}
	
	
}

int myabs(int a)
{
	if(a >= 0)
		return a;
	else
		return a*(-1);
}

