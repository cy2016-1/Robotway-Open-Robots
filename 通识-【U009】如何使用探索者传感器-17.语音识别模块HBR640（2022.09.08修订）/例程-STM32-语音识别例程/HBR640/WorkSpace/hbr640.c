#include "hbr640.h"
#include "hbr_uart5.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

unsigned char _initializerBuf[3];
unsigned char _sensitivity[3];
unsigned char _noise[3];
unsigned char _volume[3];
unsigned char _openBuf[3];
unsigned char _endBuf[3];
char _receiveBuf[3];
int  _value;
int _flag;



void HBR640_INIT(void)
{
	unsigned char _Buf0[3] = {0xA0, 0xA0, 0xA0};
	for (int i = 0; i < 3; ++i)
	{
			_initializerBuf[i] = _Buf0[i];
	}

	unsigned char _Buf1[3] = {0XA1, 0X0C, 0X02};
	for(int i=0;i<3;i++)
	{
		_sensitivity[i] = _Buf1[i];
		
	}

	unsigned char _Buf2[3] = {0xA2, 0x1A, 0x1D};//{0xA2, 0x1E, 0x21};
	for(int i=0;i<3;i++)
	{
		_noise[i] = _Buf2[i];
	}

	unsigned char _Buf3[3] = {0xCA, 0X0F, 0X00};
	for(int i=0;i<3;i++)
	{
		_volume[i] = _Buf3[i];
	}

	unsigned char _Buf4[3] = {0xAB, 0xAB, 0x00};
	//unsigned char _Buf1[3] = {0xAA, 0x08, 0x00};
	for (int i = 0; i < 3; ++i)
	{
			_openBuf[i] = _Buf4[i];
	}

	unsigned char _Buf5[3] = {0xAC, 0xAC, 0x00};
	for (int i = 0; i < 3; ++i)
	{
			_endBuf[i] = _Buf5[i];
	}

	_value = 0;
	_flag = 0;
}

void open(void)
{
	delay_ms(100);
	UART5_INIT();
	for(int i=0; i < 3; i++){
		UART5_Send_Byte(_initializerBuf[i]);
	}
	delay_ms(100);
	for(int i=0; i < 3; i++){
		UART5_Send_Byte(_sensitivity[i]);
	}	
	delay_ms(100);
	for(int i=0; i < 3; i++){
		UART5_Send_Byte(_noise[i]);
	}	
	delay_ms(100);
	for(int i=0; i < 3; i++){
		UART5_Send_Byte(_openBuf[i]);
	}	
	delay_ms(100);
}

void lisen(void)
{
	for(int i=0; i < 3; i++){
		_receiveBuf[i] = UART5_RX_BUF[i];
	}	
}

int isHeard(void)
{
	return _flag;
}

int getSentence(void)
{
	_flag = 0;
	return (int)((_receiveBuf[2] << 8) | (_receiveBuf[1]));
}
void close(void)
{
	for(int i=0; i < 3; i++){
		UART5_Send_Byte(_endBuf[i]);
	}
}
