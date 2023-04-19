#ifndef __OLED_H
#define __OLED_H 
#include "stm32f4xx.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"


#define OLED_MODE 	0
#define SIZE		 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED IIC端口定义----------------  					   

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_6)//SCL
#define OLED_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_6)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_7)//SDA
#define OLED_SDIN_Set() GPIO_SetBits(GPIOA,GPIO_Pin_7)

#define OLED_IIC_SDA_Read()   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)

#define OLED_IIC_SDA_Out() 	{GPIOA->MODER&=~(3<<(7*2));GPIOA->MODER|=1<<(7*2);} //PA7输出模式
#define OLED_IIC_SDA_In()	{GPIOA->MODER&=~(3<<(7*2));GPIOA->MODER|=0<<(7*2);}	//PA7输入模式

 		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//OLED控制用函数
extern void OLED_WR_Byte(unsigned dat,unsigned cmd);  
extern void OLED_Display_On(void);
extern void OLED_Display_Off(void);	   							   		    
extern void OLED_Init(u8 x);
extern void OLED_Clear(void);
extern void OLED_DrawPoint(uint8_t x,u8 y,u8 t);
extern void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
extern void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
extern void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
extern void OLED_ShowString(unsigned char x,unsigned char y, unsigned char *p,unsigned char Char_Size);	 
extern void OLED_Set_Pos(unsigned char x, unsigned char y);
extern void OLED_ShowCHinese(u8 x,u8 y,u8 no);
extern void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
extern void Delay_50ms(unsigned int Del_50ms);
extern void Delay_1ms(unsigned int Del_1ms);
extern void fill_picture(unsigned char fill_Data);
extern void Picture(void);
extern void OLED_IIC_Start(void);
extern void OLED_IIC_Stop(void);
extern void OLED_Write_IIC_Command(unsigned char IIC_Command);
extern void OLED_Write_IIC_Data(unsigned char IIC_Data);
extern void OLED_Write_IIC_Byte(unsigned char IIC_Byte);
extern void OLED_ShowCHinese(u8 x,u8 y,u8 no);

extern int OLED_IIC_Wait_Ack(void);


extern void show1(void* param);
extern void show2(void* param);

#endif
