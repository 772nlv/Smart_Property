#include "user.h"
//1.外部中断时钟使能和GPIO配置
void INTERRUPT_KEY1_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	//2.GPIO初始化
	GPIO_InitTypeDef keystruct;
	keystruct.GPIO_Pin = GPIO_Pin_4;
	keystruct.GPIO_Mode = GPIO_Mode_IN;
	keystruct.GPIO_PuPd = GPIO_PuPd_UP;
	keystruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOE,&keystruct);
	//3.外部中断线映射配置
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource4);	
	//4.外部中断初始化
	EXTI_InitTypeDef extistruct;
	extistruct.EXTI_Line = EXTI_Line4;
	extistruct.EXTI_LineCmd = ENABLE;
	extistruct.EXTI_Mode = EXTI_Mode_Interrupt;
	extistruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&extistruct);
	//5.NVIC中断配置
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannel = EXTI4_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}
void INTERRUPT_KEY2_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	//2.GPIO初始化
	GPIO_InitTypeDef keystruct;
	keystruct.GPIO_Pin = GPIO_Pin_5;
	keystruct.GPIO_Mode = GPIO_Mode_IN;
	keystruct.GPIO_PuPd = GPIO_PuPd_UP;
	keystruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOE,&keystruct);
	//3.外部中断线映射配置
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource5);
	//4.外部中断初始化
	EXTI_InitTypeDef extistruct;
	extistruct.EXTI_Line = EXTI_Line5;
	extistruct.EXTI_LineCmd = ENABLE;
	extistruct.EXTI_Mode = EXTI_Mode_Interrupt;
	extistruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&extistruct);
	//5.NVIC中断配置
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}

void INTERRUPT_KEY3_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	//2.GPIO初始化
	GPIO_InitTypeDef keystruct;
	keystruct.GPIO_Pin = GPIO_Pin_6;
	keystruct.GPIO_Mode = GPIO_Mode_IN;
	keystruct.GPIO_PuPd = GPIO_PuPd_UP;
	keystruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOE,&keystruct);
	//3.外部中断线映射配置
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource6);
	
	//4.外部中断初始化
	EXTI_InitTypeDef extistruct;
	extistruct.EXTI_Line = EXTI_Line6;
	extistruct.EXTI_LineCmd = ENABLE;
	extistruct.EXTI_Mode = EXTI_Mode_Interrupt;
	extistruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&extistruct);
	//5.NVIC中断配置
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}
void INTERRUPT_KEY4_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	//2.GPIO初始化
	GPIO_InitTypeDef keystruct;
	keystruct.GPIO_Pin = GPIO_Pin_13;
	keystruct.GPIO_Mode = GPIO_Mode_IN;
	keystruct.GPIO_PuPd = GPIO_PuPd_UP;
	keystruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOC,&keystruct);
	//3.外部中断线映射配置
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource13);
	//4.外部中断初始化
	EXTI_InitTypeDef extistruct;
	extistruct.EXTI_Line = EXTI_Line13;
	extistruct.EXTI_LineCmd = ENABLE;
	extistruct.EXTI_Mode = EXTI_Mode_Interrupt;
	extistruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&extistruct);
	//5.NVIC中断配置
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}

//6.中断服务程序
void EXTI4_IRQHandler()
{	


	EXTI_ClearITPendingBit(EXTI_Line4);
	
}
void EXTI9_5_IRQHandler()
{	
			if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5))
			{		
		
				EXTI_ClearITPendingBit(EXTI_Line5);
			}
	
			if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6))
			{		
				
					EXTI_ClearITPendingBit(EXTI_Line6);
			}
}

void EXTI15_10_IRQHandler()
{			

	EXTI_ClearITPendingBit(EXTI_Line13);
}
