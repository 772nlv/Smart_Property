#include "user.h"
//������ʼ��
void Key_Config()
{
	//1.����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	//2.���ýӿ�
	GPIO_InitTypeDef keystruct;
	//���ź���
	keystruct.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	//����ģʽ
	keystruct.GPIO_Mode = GPIO_Mode_IN;
	//��������
	keystruct.GPIO_PuPd = GPIO_PuPd_UP;
	//��Ӧ�ٶ�
	keystruct.GPIO_Speed = GPIO_Low_Speed;
//3.��ʼ���˿ں���
	GPIO_Init(GPIOE,&keystruct);

}
void KEY_4_Config()
{
	//1.����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	//2.���ýӿ�
	GPIO_InitTypeDef keystruct;
	//���ź���
	keystruct.GPIO_Pin = GPIO_Pin_13;
	//����ģʽ
	keystruct.GPIO_Mode = GPIO_Mode_IN;
	//��������
	keystruct.GPIO_PuPd = GPIO_PuPd_UP;
	//��Ӧ�ٶ�
	keystruct.GPIO_Speed = GPIO_Low_Speed;
	//3.��ʼ���˿ں���
	GPIO_Init(GPIOC,&keystruct);
}

unsigned char scanfkey()
{
 if(key1==0||key2==0||key3==0||key4==0)
 {
  delay_xms(10);
	if(key1==0) {while(key1==0);delay_xms(10);return 1;}
	else if(key2==0) {while(key2==0);delay_xms(10);return 2;} 
  else if(key3==0) {while(key3==0);delay_xms(10);return 3;}
  else if(key4==0) {while(key4==0);delay_xms(10);return 4;}
 }
 return 0;
}



