#include "user.h" 
//��ʼ��PF9��PF10Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{    	 
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);	//ʹ��GPIOFʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_10|GPIO_Pin_9;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//����
	GPIO_Init(GPIOE, &GPIO_InitStructure);					//��ʼ��GPIO
	GPIO_SetBits(GPIOE,GPIO_Pin_8|GPIO_Pin_9 | GPIO_Pin_10);			
}
void LED_TurnOn(unsigned int LEDNUM)
{
		 switch(LEDNUM)
		 {
			 case 1:GPIO_ResetBits(GPIOE,GPIO_Pin_8); break;
			 case 2:GPIO_ResetBits(GPIOE,GPIO_Pin_9); break;
			 case 3:GPIO_ResetBits(GPIOE,GPIO_Pin_10); break;
			 default:break;
		 }
}
//3.�ر�led����

void LED_TurnOff(unsigned int LEDNUM)
{
	 switch(LEDNUM)
		 {
			 case 1:GPIO_SetBits(GPIOE,GPIO_Pin_8); break;
			 case 2:GPIO_SetBits(GPIOE,GPIO_Pin_9); break;
			 case 3:GPIO_SetBits(GPIOE,GPIO_Pin_10); break;
			 default:break;
		 }

}





