#include "user.h"
//1配置内核定时器
static unsigned int timedelay = 0;
void SYSTICK_Config()
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);//   1/168m s
	if(SysTick_Config(SystemCoreClock/1000));//168000*168m=1ms 返回0成功返回1失败
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

