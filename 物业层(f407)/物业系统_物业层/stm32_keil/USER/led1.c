#include "user.h"


//led模块配置函数
//驼峰命名
void LED_config(void)
{

    //1配置时钟-PE-GPIOE-8，查询时钟中线图
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
    //配置接口
	//设置结构体参数，一一对应寄存器
    GPIO_InitTypeDef ledstruct;
    //引脚号码
    ledstruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	
    //输出模式
    ledstruct.GPIO_Mode = GPIO_Mode_OUT;
    //开漏输出
    ledstruct.GPIO_OType = GPIO_OType_PP;
	//
	ledstruct.GPIO_PuPd = GPIO_PuPd_UP;
	//传输速度
	ledstruct.GPIO_Speed = GPIO_Low_Speed;
	
	//此函数可以快捷 填写寄存器
    GPIO_Init(GPIOE,&ledstruct);
	
    //3.初始化接口-led是低电平驱动
	GPIO_SetBits(GPIOE,GPIO_Pin_8);
	GPIO_SetBits(GPIOE,GPIO_Pin_9);
	GPIO_SetBits(GPIOE,GPIO_Pin_10);
}


//2.打开led函数
void LED_TurnOn(unsigned int LEDNUM)
{
    //开灯是低电平
	if(LEDNUM == LED1)
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);
	
	if(LEDNUM == LED2)
		GPIO_ResetBits(GPIOE,GPIO_Pin_9);
	
	if(LEDNUM == LED3)
		GPIO_ResetBits(GPIOE,GPIO_Pin_10);

}

//3、关闭led
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

//led闪烁
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

//led流水
void LED_FLow(void)
{
	while(1)
	{
		//打开，延迟，关闭，延迟
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




















