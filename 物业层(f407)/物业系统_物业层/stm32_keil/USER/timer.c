#include "user.h"
//�¶ȡ�ʪ������

//���ö�ʱ��4 ʵ�ֶ�ʱһ��
void Timer4_Config(unsigned short prec,unsigned short peri)
{
	//����ʱ�� APB1 :42hz ����֮������ʱ�� 84hz
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	//����ʱ�䵥Ԫ,��ʼ����ʱ��
	TIM_TimeBaseInitTypeDef timer4struct;
	timer4struct.TIM_ClockDivision = TIM_CKD_DIV1;
	//Ԥ��Ƶϵ�� - ����ʱ�� ������  ����ʱ����Ƶ
	//һ������ ʱ�� = 1/ ����ʱ�� * Ԥ��Ƶϵ�� s
	timer4struct.TIM_Prescaler = prec;
	
	//ʱ����� ÿִ��һ��ʱ����� ����һ���ж� 
	//peri ��һ��ʱ�����ִ�е�������
	timer4struct.TIM_Period = peri;
	TIM_TimeBaseInit(TIM4,&timer4struct);
	

	//�����ж�����
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	
	//�ж�ʹ��
	TIM_Cmd(TIM4,ENABLE);
	
	//����NVIC �жϿ���������
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannel = TIM4_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}

//�жϺ���
void TIM4_IRQHandler()
{
	//�����־λ
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}



























