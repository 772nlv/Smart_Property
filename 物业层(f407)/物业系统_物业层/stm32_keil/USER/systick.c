//#include "user.h"

//unsigned int timedelay =  0;
//void SYSTICK_Init(unsigned int n)
//{
//	
//	//1������ʱ��Դ
//	//����ʱ��ԴΪHCLK 168mhz;
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
//	
//	//2������systick��ʱ���жϼ��
//	//uint32_t SysTick_Config(uint32_t ticks);
//	//������ticks ��һ���޷���32λ��������ʾ��װ�ؼĴ�����ֵ��
//	//���ֵ������ SysTick ��ʱ���ڲ����ж�֮ǰ��Ҫ������ʱ����������
//	//ÿִ��168000000 \ 1000 �β����ж�
//	if(n == us)
//	{
//		if(SysTick_Config(SystemCoreClock/1000000))//ʱ����Ϊ1us
//		{
//		LED_TurnOn(LED2);
//		}
//	}
//	if(n == ms)
//	{
//		if(SysTick_Config(SystemCoreClock/1000))//ʱ����Ϊ1us
//		{
//		LED_TurnOn(LED1);
//		}
//	}
//	
//}
////1ms�� ��cpuִ���жϺ���
////�жϺ���
//void SysTick_Handler()
//{
//	if(timedelay != 0)
//	{
//		timedelay--;
//	}
//}

////systick ��ʱ���� 1ms
//void MY_Systick_Delay(unsigned int n)
//{
//	timedelay = n;
//	while(timedelay);	
//}















