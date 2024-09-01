#include "user.h"


//ledģ�����ú���
//�շ�����
void LED_config(void)
{

    //1����ʱ��-PE-GPIOE-8����ѯʱ������ͼ
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
    //���ýӿ�
	//���ýṹ�������һһ��Ӧ�Ĵ���
    GPIO_InitTypeDef ledstruct;
    //���ź���
    ledstruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	
    //���ģʽ
    ledstruct.GPIO_Mode = GPIO_Mode_OUT;
    //��©���
    ledstruct.GPIO_OType = GPIO_OType_PP;
	//
	ledstruct.GPIO_PuPd = GPIO_PuPd_UP;
	//�����ٶ�
	ledstruct.GPIO_Speed = GPIO_Low_Speed;
	
	//�˺������Կ�� ��д�Ĵ���
    GPIO_Init(GPIOE,&ledstruct);
	
    //3.��ʼ���ӿ�-led�ǵ͵�ƽ����
	GPIO_SetBits(GPIOE,GPIO_Pin_8);
	GPIO_SetBits(GPIOE,GPIO_Pin_9);
	GPIO_SetBits(GPIOE,GPIO_Pin_10);
}


//2.��led����
void LED_TurnOn(unsigned int LEDNUM)
{
    //�����ǵ͵�ƽ
	if(LEDNUM == LED1)
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);
	
	if(LEDNUM == LED2)
		GPIO_ResetBits(GPIOE,GPIO_Pin_9);
	
	if(LEDNUM == LED3)
		GPIO_ResetBits(GPIOE,GPIO_Pin_10);

}

//3���ر�led
void LED_TurnOff(unsigned int LEDNUM)
{
    switch(LEDNUM)
	{
		case LED1:GPIO_SetBits(GPIOE,GPIO_Pin_8);break;
		case LED2:GPIO_SetBits(GPIOE,GPIO_Pin_9);break;
		case LED3:GPIO_SetBits(GPIOE,GPIO_Pin_10);break;
		default:break;
	}
}

//led��˸
void LED_Shine(unsigned int LEDNUM)
{
	while(1)
	{
		My_Delay(100);
		LED_TurnOn(LEDNUM);
		My_Delay(100);
		LED_TurnOff(LEDNUM);
	}
}

//led��ˮ
void LED_FLow(void)
{
	while(1)
	{
		//�򿪣��ӳ٣��رգ��ӳ�
		My_Delay(100);
		LED_TurnOn(LED1);
		My_Delay(100);
		LED_TurnOff(LED1);
		
		My_Delay(100);
		LED_TurnOn(LED2);
		My_Delay(100);
		LED_TurnOff(LED2);
		
		My_Delay(100);
		LED_TurnOn(LED3);
		My_Delay(100);
		LED_TurnOff(LED3);
	}
}




















