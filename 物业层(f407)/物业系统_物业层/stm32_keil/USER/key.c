#include "user.h"

//1����ʼ������__PE_456
void KEY1_2_3_Config(void)
{
	//1.����ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
    //2.��������
    GPIO_InitTypeDef keystruct;
    //���ź���
    keystruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5|GPIO_Pin_6;
    //����ģʽ
    keystruct.GPIO_Mode = GPIO_Mode_IN;
    //��������
    keystruct.GPIO_PuPd = GPIO_PuPd_UP;
    //����
    keystruct.GPIO_Speed = GPIO_Low_Speed;
    //��ʼ��
    GPIO_Init(GPIOE,&keystruct);

}

//key4 PC_13
void KEY4_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	//��������
	GPIO_InitTypeDef keystruct;
	keystruct.GPIO_Mode = GPIO_Mode_IN;
	keystruct.GPIO_Pin = GPIO_Pin_13;
	keystruct.GPIO_PuPd = GPIO_PuPd_UP;
	keystruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOC,&keystruct);

}
//2��ɨ�谴��
void KEY_Scan(void)
{
	//key1
	if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4))
	{
		//�������ζ���
		My_Delay(10);
		if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4))
		{
			//�жϰ����Ƿ��ɿ�
			while(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4));
			BEEP_TurnOn();
		}
	}
	//key2
	if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5))
	{
		My_Delay(10);
		if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5))
		{
			while(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5));
			BEEP_TurnOff();
		}
	}
	//key3
	if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6))
	{
		My_Delay(10);
		if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6))
		{
			while(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6));
			LED_TurnOn(LED1);
			LED_TurnOn(LED2);
			LED_TurnOn(LED3);
		}
	}
	//key4
	if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13))
	{
		My_Delay(10);
		if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13))
		{
			while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13));
			LED_TurnOff(LED1);
			LED_TurnOff(LED2);
			LED_TurnOff(LED3);
		}
	}
}





















