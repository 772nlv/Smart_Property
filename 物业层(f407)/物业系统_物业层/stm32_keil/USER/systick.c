//#include "user.h"

//unsigned int timedelay =  0;
//void SYSTICK_Init(unsigned int n)
//{
//	
//	//1、设置时钟源
//	//设置时钟源为HCLK 168mhz;
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
//	
//	//2、配置systick的时间中断间隔
//	//uint32_t SysTick_Config(uint32_t ticks);
//	//参数：ticks 是一个无符号32位整数，表示重装载寄存器的值。
//	//这个值决定了 SysTick 定时器在产生中断之前需要计数的时钟周期数。
//	//每执行168000000 \ 1000 次产生中断
//	if(n == us)
//	{
//		if(SysTick_Config(SystemCoreClock/1000000))//时间间隔为1us
//		{
//		LED_TurnOn(LED2);
//		}
//	}
//	if(n == ms)
//	{
//		if(SysTick_Config(SystemCoreClock/1000))//时间间隔为1us
//		{
//		LED_TurnOn(LED1);
//		}
//	}
//	
//}
////1ms到 ，cpu执行中断函数
////中断函数
//void SysTick_Handler()
//{
//	if(timedelay != 0)
//	{
//		timedelay--;
//	}
//}

////systick 延时函数 1ms
//void MY_Systick_Delay(unsigned int n)
//{
//	timedelay = n;
//	while(timedelay);	
//}















