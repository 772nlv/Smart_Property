#include "user.h"
//配置定时器4，实现定时1s
//预分频系数8400，自动装载数值是10000
void TIMER4_Init(unsigned int psc,unsigned int period)
{
	//1.配置时钟，APB1本身是42MHZ,供给定时器的话就是84MHZ；
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	//2.初始化定时器，配置ARR,PSC；
	TIM_TimeBaseInitTypeDef timer4;
	TIM_TimeBaseInitTypeDef *timer4struct = &timer4;
	timer4struct->TIM_Prescaler = psc;
	timer4struct->TIM_Period = period;
	timer4struct->TIM_CounterMode = TIM_CounterMode_Up;
	timer4struct->TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4,timer4struct);
	
	//3.允许更新中断 ,更新中断是定时器计数器溢出时产生的中断。
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);	
	//4.使能定时器
	TIM_Cmd(TIM4,ENABLE);
	
	//5.开启定时器中断，配置NVIC
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannel = TIM4_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority  = 0;
	NVIC_Init(&nvicstruct);

}

	//6.编写中断服务函数
void	TIM4_IRQHandler()
{		
	GPIO_ToggleBits(GPIOE,GPIO_Pin_10);

	//7.在中断服务函数中清除中断标志位
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}
	


