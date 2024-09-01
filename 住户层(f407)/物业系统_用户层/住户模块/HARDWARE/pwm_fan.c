#include "user.h"
//���Ʒ�����ҪPWM�źţ�PWM�ź���Ҫ����->����ͨ����ʱ������->ͨ������ͨ������->��Щ��ʱ����-/TIM1_CH3N/TIM8_CH3N/TIM12_CH2
//�˴�ѡ��TIM12_CH2������PWM�ź�
//����->1.ʹ��TIM12��ʱ����GPIOB�˿ڵ�ʱ��(ʹ���κ�����ǰ������Ҫʹ�����ǵ�ʱ��)2.����TIM12����(�������벶������Ƚϡ�PWM����)
//3.��GPIOB-15����Ϊ����ģʽ4.���ö�ʱ���������˶�ʱ���Ļ�����������Ƶ�����Զ����ؼĴ������ڣ�������ģʽ->��Щ����������PWM��Ƶ��
//5.����timer12�ıȽ�ͨ��2���Դ�������PWM�ź�6.����OC2ͨ����Ԥװ�ع��ܣ����Ը���CCR�Ĵ�����ֵ�������������ʱƽ���ص���PWMռ�ձȷǳ�����
//7.����OC2��Ԥװ�ع������ƣ�����Ӱ����Ƕ�ʱ�������ڣ���ARR�Ĵ�����ֵ�������ô˹��ܺ�������ڲ�Ӱ�쵱ǰ��ʱ�����ڵ�����¸���ARR��ֵ�������������ʱ����PWMƵ�ʷǳ����á�
//����pwm����
//PB15 + TIMER12_CH2

void TIMER12_CH2_PWM_PB15_Config()
{	
//1.����ʱ�� APB1 42mhz -GPIOʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
//2.�������� b��15���������óɸ��ù��ܶ�ʱ��12
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM12);
//3.GPIO�������óɸ���ģʽ
	GPIO_InitTypeDef fanstruct = {0};
	//���ź���
	fanstruct.GPIO_Pin = 	GPIO_Pin_15;
	//����ģʽ
	fanstruct.GPIO_Mode = GPIO_Mode_AF;
	//��������
	fanstruct.GPIO_PuPd = GPIO_PuPd_UP;
	//��Ӧ�ٶ�
	fanstruct.GPIO_Speed = GPIO_Low_Speed;
	//��ʼ���˿ں���
	GPIO_Init(GPIOB,&fanstruct);
	//4.���ö�ʱ��
	TIM_TimeBaseInitTypeDef tim12struct = {0};
	tim12struct.TIM_Prescaler = 84-1;
	tim12struct.TIM_Period = 20000-1;
	tim12struct.TIM_CounterMode = TIM_CounterMode_Up;
	tim12struct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM12,&tim12struct);
	//5.����timer12 ͨ��2
	TIM_OCInitTypeDef oc2struct = {0};
	oc2struct.TIM_OCMode =TIM_OCMode_PWM1;
	oc2struct.TIM_OCPolarity = TIM_OCPolarity_High;
	oc2struct.TIM_OutputState =	TIM_OutputState_Enable;
	TIM_OC2Init(TIM12,&oc2struct);
	//����CCR2��ֵ
	//TIM12->CCR2 = (19999 / 2) - 1; 
	//6�Ƚϲ���Ĵ���ʹ��
	TIM_OC2PreloadConfig(TIM12,TIM_OCPreload_Enable);
	//7.�Զ���װ�ؼĴ���ʹ�� Ԥװ��
	TIM_ARRPreloadConfig(TIM12,ENABLE);
	//8.��ʱ������ʹ��
	//TIM_Cmd(TIM12,ENABLE);
}
//�򿪷��Ⱥ���
void Fan_TurnOn()
{	
	TIM_Cmd(TIM12,ENABLE);
	Fan_Control(10000);
}

//�رշ���
void Fan_TurnOff()
{	
		Fan_Control(0);
  //TIM_Cmd(TIM12,DISABLE);�������
		delay_ms(500);
}

//���Ʒ��Ⱥ��� ���� ���� ���� 10000
void Fan_Control(unsigned int cvalue)
{
   TIM_SetCompare2(TIM12,cvalue);
}

