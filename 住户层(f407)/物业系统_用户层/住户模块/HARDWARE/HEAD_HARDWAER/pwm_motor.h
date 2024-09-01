#ifndef __PWM_MOTOR_H
#define __PWM_MOTOR_H


void TIM4_PWM_Init(uint32_t arr, uint32_t psc) ;

//指纹GPIOA - PA -8使能
void FINGER_Init(void);
//旋转大约180度
//控制开门TIM_SetCompare4(TIM4,5);
//控制关门TIM_SetCompare4(TIM4,20);
#endif

