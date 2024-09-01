#include "user.h"
//PD15 PWM6 TIM4-CH4
void TIM4_PWM_Init(uint32_t arr, uint32_t psc)  
{  
    GPIO_InitTypeDef GPIO_InitStructure;  
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
    TIM_OCInitTypeDef TIM_OCInitStructure;  
  
    // ʹ��TIM4��GPIOD��ʱ��  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  
  
    // ����GPIOD��Pin15Ϊ���ù��ܣ�TIM4_CH4��  
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);  
  
    // ��ʼ��GPIOD��Pin15  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // ͨ������PWM���������Ҫ������  
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
  
    // ��ʼ��TIM4��ʱ�����  
		TIM_TimeBaseStructure.TIM_Period = arr; 
    TIM_TimeBaseStructure.TIM_Prescaler = psc;  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);  
  
    // ��ʼ��TIM4������Ƚ�ͨ��4  
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
    //TIM_OCInitStructure.TIM_Pulse = 0; // ��ʼռ�ձ�����Ϊ0���������Ҫ���ã�  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  
    TIM_OC4Init(TIM4, &TIM_OCInitStructure); // ע��������TIM_OC4Init  
  
    // ʹ��TIM4��ARRԤװ�ؼĴ���  
    TIM_ARRPreloadConfig(TIM4, ENABLE);  
    // ʹ��TIM4��OC4Ԥװ��  
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); // ע�⣺���������TIM_OC4PreloadConfig���������û�У�������Ҫ������ʽ  

    // ʹ��TIM4  
    TIM_Cmd(TIM4, ENABLE);  
		//TIM_SetCompare4(TIM4,0);
} 

void FINGER_Init(){
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
		
}

