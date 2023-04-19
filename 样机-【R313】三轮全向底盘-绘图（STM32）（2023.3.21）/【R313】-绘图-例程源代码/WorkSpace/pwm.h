#ifndef __PWM_H
#define __PWM_H

#define SERVO	PDout(15)
#include "sys.h"
#include "stm32f4xx_conf.h"

extern void TIM4_PWM_Init(u32 arr,u32 psc);

extern void Put_Up(void);
extern void Put_Down(void);
//extern void TIM4_Int_Init(void);
//extern void Clock_Start(void);
//extern u32 Clock_End(void);
#endif

