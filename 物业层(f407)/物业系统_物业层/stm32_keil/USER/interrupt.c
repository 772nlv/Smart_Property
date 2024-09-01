#include "user.h"

extern char tempvalue_1[128];
extern char humivalue_1[128];
extern char lihgtvalue_1[128];
extern char potenvalue_1[128];

//ϵͳ����
extern int SYSTEM_ON_FLAG;
//�ɼ�����״̬λ
extern int COLLECT_DATA_ON_FLAG;
//�ж�KEY_1��غ�������
void INTERRUPT_KEY1_Config(void)
{
	//1������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//����GPIO�ӿ�
	//2.��ʼ��IO�ӿ�
    GPIO_InitTypeDef keystruct;
    //���ź���
    keystruct.GPIO_Pin = GPIO_Pin_4;
    //����ģʽ
    keystruct.GPIO_Mode = GPIO_Mode_IN;
    //��������
    keystruct.GPIO_PuPd = GPIO_PuPd_UP;
    //����
    keystruct.GPIO_Speed = GPIO_Low_Speed;
    //��ʼ��
    GPIO_Init(GPIOE,&keystruct);
	
	//3���ⲿ�ж�����.E���ĺ��������ó��жϹ���
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource4);
	
	//4���ⲿ�жϳ�ʼ��
	EXTI_InitTypeDef exitstruct;
	
	exitstruct.EXTI_Line = EXTI_Line4;
	exitstruct.EXTI_LineCmd = ENABLE;
	exitstruct.EXTI_Trigger = EXTI_Trigger_Falling;
	exitstruct.EXTI_Mode = EXTI_Mode_Interrupt;
	
	EXTI_Init(&exitstruct);
	
	//�жϿ�����
	NVIC_InitTypeDef nvicstruct;
	//�ж����� ���� �ⲿ�ж�
	nvicstruct.NVIC_IRQChannel =  EXTI4_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	
	//��ռ���ȼ� ��ѡһ
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	//��Ӧ���ȼ�
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}

//�ж�KEY_2��غ�������
void INTERRUPT_KEY2_Config(void)
{
	//1������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	
	//����GPIO�ӿ�
	//2.��ʼ��IO�ӿ�
    GPIO_InitTypeDef keystruct;
    //���ź���
    keystruct.GPIO_Pin = GPIO_Pin_5;
    //����ģʽ
    keystruct.GPIO_Mode = GPIO_Mode_IN;
    //��������
    keystruct.GPIO_PuPd = GPIO_PuPd_UP;
    //����
    keystruct.GPIO_Speed = GPIO_Low_Speed;
    //��ʼ��
    GPIO_Init(GPIOE,&keystruct);
	
	//3���ⲿ�ж�����.E���ĺ��������ó��жϹ���
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource5);
	
	//4���ⲿ�жϳ�ʼ�����ô�������
	EXTI_InitTypeDef exitstruct;
	
	exitstruct.EXTI_Line = EXTI_Line5;
	exitstruct.EXTI_LineCmd = ENABLE;
	exitstruct.EXTI_Trigger = EXTI_Trigger_Falling;
	exitstruct.EXTI_Mode = EXTI_Mode_Interrupt;
	
	EXTI_Init(&exitstruct);
	
	//�жϿ�����
	NVIC_InitTypeDef nvicstruct;
	//�����жϷ��飻
	nvicstruct.NVIC_IRQChannel =  EXTI9_5_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	
	//��ռ���ȼ� ��ѡһ
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	//��Ӧ���ȼ�
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}

//�ж�KEY_3��غ�������
void INTERRUPT_KEY3_Config(void)
{
	//1������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//����GPIO�ӿ�
	//2.��ʼ��IO�ӿ�
    GPIO_InitTypeDef keystruct;
    //���ź���
    keystruct.GPIO_Pin = GPIO_Pin_6;
    //����ģʽ
    keystruct.GPIO_Mode = GPIO_Mode_IN;
    //��������
    keystruct.GPIO_PuPd = GPIO_PuPd_UP;
    //����
    keystruct.GPIO_Speed = GPIO_Low_Speed;
    //��ʼ��
    GPIO_Init(GPIOE,&keystruct);
	
	//3���ⲿ�ж�����.E��6���������ó��жϹ���
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource6);
	
	//4���ⲿ�жϳ�ʼ��
	EXTI_InitTypeDef exitstruct;
	
	exitstruct.EXTI_Line = EXTI_Line6;
	exitstruct.EXTI_LineCmd = ENABLE;
	exitstruct.EXTI_Trigger = EXTI_Trigger_Falling;
	exitstruct.EXTI_Mode = EXTI_Mode_Interrupt;
	
	EXTI_Init(&exitstruct);
	
	//�жϿ�����
	NVIC_InitTypeDef nvicstruct;
	//�ж����� ���� �ⲿ�ж�
	nvicstruct.NVIC_IRQChannel =  EXTI9_5_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	
	//��ռ���ȼ� ��ѡһ
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	//��Ӧ���ȼ�
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}
//�ж�KEY_4��غ�������
void INTERRUPT_KEY4_Config(void)
{
	//1������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//����GPIO�ӿ�
	//2.��ʼ��IO�ӿ�
    GPIO_InitTypeDef keystruct;
    //���ź���
    keystruct.GPIO_Pin = GPIO_Pin_13;
    //����ģʽ
    keystruct.GPIO_Mode = GPIO_Mode_IN;
    //��������
    keystruct.GPIO_PuPd = GPIO_PuPd_UP;
    //����
    keystruct.GPIO_Speed = GPIO_Low_Speed;
    //��ʼ��
    GPIO_Init(GPIOC,&keystruct);
	
	//3���ⲿ�ж�����.C��13�����������жϹ���
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource13);
	
	//4���ⲿ�жϳ�ʼ��
	EXTI_InitTypeDef exitstruct;
	
	exitstruct.EXTI_Line = EXTI_Line13;
	exitstruct.EXTI_LineCmd = ENABLE;
	exitstruct.EXTI_Trigger = EXTI_Trigger_Falling;
	exitstruct.EXTI_Mode = EXTI_Mode_Interrupt;
	
	EXTI_Init(&exitstruct);
	
	//�жϿ�����
	NVIC_InitTypeDef nvicstruct;
	//�ж����� ���� �ⲿ�ж�
	nvicstruct.NVIC_IRQChannel =  EXTI15_10_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	
	//��ռ���ȼ� ��ѡһ
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	//��Ӧ���ȼ�
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}

//�жϺ���
//������ִ������ΪPE4��ƽ�ı�
//����1�ж�
void EXTI4_IRQHandler()
{
	BEEP_TurnOn();
	delay_ms(20);
	BEEP_TurnOff();
	SYSTEM_ON_FLAG = 1;
	EXTI_ClearITPendingBit(EXTI_Line4);

}
//����2��3�ж�
void EXTI9_5_IRQHandler()
{
	
	if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5))
	{
		BEEP_TurnOn();
		delay_ms(20);
		BEEP_TurnOff();
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
	if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6))
	{
		BEEP_TurnOn();
		delay_ms(20);
		BEEP_TurnOff();
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
}
//����4�ж�
void EXTI15_10_IRQHandler()
{
	BEEP_TurnOn();
	delay_ms(20);
	BEEP_TurnOff();
	EXTI_ClearITPendingBit(EXTI_Line13);
}




















