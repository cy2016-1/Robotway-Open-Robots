#include "key.h"
#include "delay.h" 


void KEY_Init(void)			//按键初始化函数
{	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5; //KEY 对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//即不上拉也不下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA	 
} 
//函数名：KEY_Scan
//返回值：按键状态 0，没有任何按键按下 1，按键按下
//参数：mode:0,不支持连续按;1,支持连续按;
//作用：判断按键是否按下，并将按键状态以值得形式返回
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=0;//按键按松开标志  
	
	if(mode)
		key_up=1;  			//支持连按		  
	if(key_up){
		delay_ms(10);		//去抖动 
		key_up=0;
		if(KEY0==0)
			return 1;			//按键按下
	}else if(KEY0==1)
		key_up=1;	
	return 0;					// 无按键按下
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


















