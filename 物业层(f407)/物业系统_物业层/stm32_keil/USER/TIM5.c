#include "user.h"
//�¶ȡ�ʪ������

//���ö�ʱ��5 ʵ�ֶ�ʱһ��
void Timer5_Config(unsigned short prec,unsigned short peri)
{
	//����ʱ�� APB1 :42hz ����֮������ʱ�� 84hz
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	//����ʱ�䵥Ԫ,��ʼ����ʱ��
	TIM_TimeBaseInitTypeDef timer5struct;
	timer5struct.TIM_ClockDivision = TIM_CKD_DIV1;
	//Ԥ��Ƶϵ�� - ����ʱ�� ������  ����ʱ����Ƶ
	//һ������ ʱ�� = 1/ ����ʱ�� / Ԥ��Ƶϵ�� s
	timer5struct.TIM_Prescaler = prec;
	
	//ʱ����� ÿִ��һ��ʱ����� ����һ���ж� 
	//peri ��һ��ʱ�����ִ�е�������
	timer5struct.TIM_Period = peri;
	TIM_TimeBaseInit(TIM5,&timer5struct);
	

	//�����ж�����
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
	
	//�ж�ʹ��
	TIM_Cmd(TIM5,ENABLE);
	
	//����NVIC �жϿ���������
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannel = TIM5_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}

//�жϺ���
void TIM5_IRQHandler()
{
	//��ʱʱ�䵽����ȡ��ʪ��
	GPIO_ToggleBits(GPIOE,GPIO_Pin_9);
	//�����־λ
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}



























