#include "user.h"
//PD15 PWM6 TIM4-CH4
void TIM4_PWM_Init(uint32_t arr, uint32_t psc)  
{  
    GPIO_InitTypeDef GPIO_InitStructure;  
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
    TIM_OCInitTypeDef TIM_OCInitStructure;  
  
    // 使能TIM4和GPIOD的时钟  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  
  
    // 配置GPIOD的Pin15为复用功能（TIM4_CH4）  
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);  
  
    // 初始化GPIOD的Pin15  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 通常对于PWM输出，不需要上下拉  
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
  
    // 初始化TIM4的时间基数  
		TIM_TimeBaseStructure.TIM_Period = arr; 
    TIM_TimeBaseStructure.TIM_Prescaler = psc;  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);  
  
    // 初始化TIM4的输出比较通道4  
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
    //TIM_OCInitStructure.TIM_Pulse = 0; // 初始占空比设置为0（或根据需要设置）  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  
    TIM_OC4Init(TIM4, &TIM_OCInitStructure); // 注意这里是TIM_OC4Init  
  
    // 使能TIM4的ARR预装载寄存器  
    TIM_ARRPreloadConfig(TIM4, ENABLE);  
    // 使能TIM4的OC4预装载  
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); // 注意：这里假设有TIM_OC4PreloadConfig函数，如果没有，可能需要其他方式  

    // 使能TIM4  
    TIM_Cmd(TIM4, ENABLE);  
		//TIM_SetCompare4(TIM4,0);
} 

void FINGER_Init(){
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
		
}

