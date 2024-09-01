#include "pwm.h"
void OLED2PWM_Init(u16 arr ,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOE,&GPIO_InitStruct);   

  GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_TIM1);
	
	TIM_TimeBaseInitStruct.TIM_Period=arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
  
  TIM_OCInitStruct.TIM_OCIdleState=TIM_OCIdleState_Set;
	TIM_OCInitStruct.TIM_OCNIdleState=TIM_OCNIdleState_Set;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1; 
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStruct.TIM_OutputNState=TIM_OutputNState_Enable;	
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStruct.TIM_OCNPolarity=TIM_OCNPolarity_Low;
  TIM_OCInitStruct.TIM_Pulse=0;	

	TIM_OC2Init(TIM1,&TIM_OCInitStruct);
	
	TIM_ARRPreloadConfig(TIM1,ENABLE);
  TIM_OC2PreloadConfig(TIM1,ENABLE);
	TIM_OC2FastConfig(TIM1,TIM_OCFast_Enable);
	TIM_Cmd(TIM1,ENABLE);
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	TIM_CCxCmd(TIM1,TIM_Channel_2,TIM_CCx_Disable);
}

