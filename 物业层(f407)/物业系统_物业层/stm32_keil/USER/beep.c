#include "user.h"

//���÷�����
void BEEP_Config(void)
{
//1����ʱ��-PE-GPIOE-8����ѯʱ������ͼ
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
    //���ýӿ�
    
	//���ýṹ�������һһ��Ӧ�Ĵ���
	GPIO_InitTypeDef beepstruct;
	
    //���ź���
    beepstruct.GPIO_Pin = GPIO_Pin_10;
	
    //���ģʽ
    beepstruct.GPIO_Mode = GPIO_Mode_OUT;
    //�������
    beepstruct.GPIO_OType = GPIO_OType_PP;
	//����
	beepstruct.GPIO_PuPd = GPIO_PuPd_UP;
	//�����ٶ�
	beepstruct.GPIO_Speed = GPIO_Low_Speed;
	
	//�˺������Կ�� ��д�Ĵ���
    GPIO_Init(GPIOB,&beepstruct);
	
    //3.��ʼ������
    //��PB10 �͵�ƽ
    GPIO_ResetBits(GPIOB,GPIO_Pin_10);
}


//�򿪷�����
void BEEP_TurnOn(void)
{
	//�򿪷������ߵ�ƽ
	
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_SET);
}

//�رշ�����
void BEEP_TurnOff(void)
{
    GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_RESET);
}

//������alarm,�޶�����
void BEEP_Alarm_Count(unsigned int count)
{
	
	while(count)
	{
		My_Delay(100);
		BEEP_TurnOn();
		My_Delay(100);
		BEEP_TurnOff();
		count--;
	}
}

//������һֱ����
void BEEP_Alarm(void)
{
	
		GPIO_ToggleBits(GPIOB,GPIO_Pin_10);
		My_Delay(100);
	
}

//��������LED1ͬ��
void BEEP_LED_To(unsigned int count)
{

	while(count)
	{
		My_Delay(100);
		BEEP_TurnOn();
		LED_TurnOn(LED1);
		My_Delay(100);
		BEEP_TurnOff();
		LED_TurnOff(LED1);
		count--;
	}
}




























