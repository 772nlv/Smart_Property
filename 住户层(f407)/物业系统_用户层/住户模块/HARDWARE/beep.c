#include "user.h"

//�շ���������ģ��+���ܣ�����֮�����»���
//1.beep ģ�����ú���

void BEEP_Config()
{
	
//1.����ʱ�� - PB -GPIOB-10
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
//2.���ýӿ�
		GPIO_InitTypeDef beepstruct;

	//���ź���
	beepstruct.GPIO_Pin = 	GPIO_Pin_10;
	//���ģʽ
	beepstruct.GPIO_Mode = GPIO_Mode_OUT;
	//�������
	beepstruct.GPIO_OType = GPIO_OType_PP;
	//��������
	beepstruct.GPIO_PuPd = GPIO_PuPd_UP;
	//��Ӧ�ٶ�
	beepstruct.GPIO_Speed = GPIO_Low_Speed;
	//��ʼ���˿ں���
	GPIO_Init(GPIOB,&beepstruct);
	
	
//3.��ʼ������-��PB10�͵�ƽ(����״̬)-�ߵ�ƽ����

GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_RESET);

}
//�򿪷�����-
void Beep_Open()
{
GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_SET);	
	
}
void Beep_Close()
{
GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_RESET);	
	
}
void Beep_Alarm()
{	
		int num = 6;
		while(num--)
		{
    GPIO_ToggleBits(GPIOB,GPIO_Pin_10);//��
    delay_ms(200);
		}
}
