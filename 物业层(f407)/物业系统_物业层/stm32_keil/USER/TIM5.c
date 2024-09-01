#include "user.h"
//温度、湿度数组

//配置定时器5 实现定时一秒
void Timer5_Config(unsigned short prec,unsigned short peri)
{
	//配置时钟 APB1 :42hz 特殊之处：定时器 84hz
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	//配置时间单元,初始化定时器
	TIM_TimeBaseInitTypeDef timer5struct;
	timer5struct.TIM_ClockDivision = TIM_CKD_DIV1;
	//预分频系数 - 总线时钟 做除法  给定时器分频
	//一个周期 时间 = 1/ 总线时钟 / 预分频系数 s
	timer5struct.TIM_Prescaler = prec;
	
	//时间节拍 每执行一个时间节拍 产生一个中断 
	//peri 是一个时间节拍执行的周期数
	timer5struct.TIM_Period = peri;
	TIM_TimeBaseInit(TIM5,&timer5struct);
	

	//配置中断条件
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
	
	//中断使能
	TIM_Cmd(TIM5,ENABLE);
	
	//配置NVIC 中断控制器配置
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannel = TIM5_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}

//中断函数
void TIM5_IRQHandler()
{
	//计时时间到，读取温湿度
	GPIO_ToggleBits(GPIOE,GPIO_Pin_9);
	//清除标志位
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}



























