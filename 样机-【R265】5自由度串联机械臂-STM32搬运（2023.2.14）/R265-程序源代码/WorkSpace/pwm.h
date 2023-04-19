#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
#include "stm32f4xx_conf.h"

void TIM9_PWM_Init(u32 arr,u32 psc);
void TIM10_PWM_Init(u32 arr,u32 psc);
void TIM11_PWM_Init(u32 arr,u32 psc);
void TIM12_PWM_Init(u32 arr,u32 psc);

#endif

