#ifndef __HBR640_H_
#define __HBR640_H_
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h"

extern void HBR640_INIT(void);
extern void open(void);
extern void lisen(void);
extern int isHeard(void);
extern int getSentence(void);
extern void close(void);

extern unsigned char _initializerBuf[3];
extern unsigned char _sensitivity[3];
extern unsigned char _noise[3];
extern unsigned char _volume[3];
extern unsigned char _openBuf[3];
extern unsigned char _endBuf[3];
extern char _receiveBuf[3];
extern int  _value;
extern int _flag;

#endif //_HBR640_H_
