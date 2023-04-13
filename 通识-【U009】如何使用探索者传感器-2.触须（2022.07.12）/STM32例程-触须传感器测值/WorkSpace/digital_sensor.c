#include "digital_sensor.h"

void Sensor_Init(void)			//初始化函数
{	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //信号对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//即不上拉也不下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA	 
} 


















