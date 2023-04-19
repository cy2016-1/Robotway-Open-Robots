#ifndef __PWM_H
#define __PWM_H
#include "sys.h"
#include "stm32f4xx_conf.h"


extern void TIM1_PWM_Init(u32 arr,u32 psc);
extern void TIM3_PWM_Init(u32 arr,u32 psc);
extern void TIM4_PWM_Init(u32 arr,u32 psc);
extern void TIM11_PWM_Init(u32 arr,u32 psc);
extern void TIM12_PWM_Init(u32 arr,u32 psc);
#endif

