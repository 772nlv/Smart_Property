#include "user.h"
//1�����ں˶�ʱ��
static unsigned int timedelay = 0;
void SYSTICK_Config()
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);//   1/168m s
	if(SysTick_Config(SystemCoreClock/1000));//168000*168m=1ms ����0�ɹ�����1ʧ��
	{				   
		led_open1();
	}	
}

void SysTick_Handler()
{
	if(timedelay!=0)
	{
		timedelay--;
	}
}

void MY_SYSTICK_DELAY(unsigned int n)	
{
	timedelay = n;
	while(timedelay!=0);	
}

