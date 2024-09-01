#include "user.h"
//���ö�ʱ��4��ʵ�ֶ�ʱ1s
//Ԥ��Ƶϵ��8400���Զ�װ����ֵ��10000
void TIMER4_Init(unsigned int psc,unsigned int period)
{
	//1.����ʱ�ӣ�APB1������42MHZ,������ʱ���Ļ�����84MHZ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	//2.��ʼ����ʱ��������ARR,PSC��
	TIM_TimeBaseInitTypeDef timer4;
	TIM_TimeBaseInitTypeDef *timer4struct = &timer4;
	timer4struct->TIM_Prescaler = psc;
	timer4struct->TIM_Period = period;
	timer4struct->TIM_CounterMode = TIM_CounterMode_Up;
	timer4struct->TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4,timer4struct);
	
	//3.��������ж� ,�����ж��Ƕ�ʱ�����������ʱ�������жϡ�
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);	
	//4.ʹ�ܶ�ʱ��
	TIM_Cmd(TIM4,ENABLE);
	
	//5.������ʱ���жϣ�����NVIC
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannel = TIM4_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority  = 0;
	NVIC_Init(&nvicstruct);

}

	//6.��д�жϷ�����
void	TIM4_IRQHandler()
{		
	GPIO_ToggleBits(GPIOE,GPIO_Pin_10);

	//7.���жϷ�����������жϱ�־λ
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}
	


