#include "user.h"

//1.���� pwm����
//������PB15 ��ʱ����TIM12 ͨ��2
void TIM12_CH2_PB15_Fan_Config()
{
	
	//1������ʱ�ӡ�ʹ��TIM12 ��PB15
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);//
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	
	//2����������PB15�����óɶ�ʱ��
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM12);
	
	//3���������� PB15
	GPIO_InitTypeDef Fan_struct;
	//����ģʽ
	Fan_struct.GPIO_Mode = GPIO_Mode_AF;
	//���ű��
	Fan_struct.GPIO_Pin = GPIO_Pin_15;
	//��������
	Fan_struct.GPIO_PuPd = GPIO_PuPd_UP;
	//��Ӧ�ٶ�
	Fan_struct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOB,&Fan_struct);
	
	//4�����ö�ʱ��
	TIM_TimeBaseInitTypeDef timer12struct;
	//Ԥ��Ƶ -  84mhz  / 84 = 1mhz
	//һ���������� 1us
	timer12struct.TIM_Period = 84 - 1;	
	//��ʱ���� 20ms
	timer12struct.TIM_Prescaler = 20000; 
	//���ϼ���
	timer12struct.TIM_CounterMode = TIM_CounterMode_Up;
	timer12struct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM12,&timer12struct);
	
	//5������timerͨ��
	TIM_OCInitTypeDef oc2struct;
	//ѡ��ģʽ PWM1
	oc2struct.TIM_OCMode = TIM_OCMode_PWM1;
	//����--�ߵ�ƽ
	oc2struct.TIM_OCPolarity = TIM_OCPolarity_High;
	//���ʹ��
	oc2struct.TIM_OutputState = TIM_OutputState_Enable;
	//��ʼ��
	TIM_OC2Init(TIM12,&oc2struct);
	
	//6���Ƚϲ���ʱ��ʹ��
	TIM_OC2PreloadConfig(TIM12,TIM_OCPreload_Enable);
	
	//7���Զ���װ��ֵʹ��
	TIM_ARRPreloadConfig(TIM12,ENABLE);
	
	//8����ʱ������ʹ��
	TIM_Cmd(TIM12,ENABLE);
}

//2.�򿪷��Ⱥ���
void Fan_TurnOn()
{
//	BEEP_TurnOn();
	TIM_Cmd(TIM12,ENABLE);
	
	delay_ms(1);
}

//3.�رշ���
void Fan_TurnOff()
{
	TIM_Cmd(TIM12,DISABLE);
	//3���������� PB15
	GPIO_InitTypeDef Fan_struct;
	//����ģʽ
	Fan_struct.GPIO_Mode = GPIO_Mode_OUT;
	//���ű��
	Fan_struct.GPIO_Pin = GPIO_Pin_15;
	//��������
	Fan_struct.GPIO_PuPd = GPIO_PuPd_UP;
	//��Ӧ�ٶ�
	Fan_struct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOB,&Fan_struct);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	delay_ms(1);
}

//4�����Ʒ���
void Fan_Control(unsigned int value)
{
	TIM_SetCompare2(TIM12,value);
	delay_ms(1);

}

void Fan_Low_Control()
{
	TIM_SetCompare2(TIM12,200);
	delay_ms(1);
}

void Fan_MId_Control()
{
	TIM_SetCompare2(TIM12,800);
	delay_ms(1);
}

void Fan_High_Control()
{
	TIM_SetCompare2(TIM12,2000);
	delay_ms(1);
}
















