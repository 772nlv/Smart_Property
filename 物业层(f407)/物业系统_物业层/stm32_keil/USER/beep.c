#include "user.h"

//配置蜂鸣器
void BEEP_Config(void)
{
//1配置时钟-PE-GPIOE-8，查询时钟中线图
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
    //配置接口
    
	//设置结构体参数，一一对应寄存器
	GPIO_InitTypeDef beepstruct;
	
    //引脚号码
    beepstruct.GPIO_Pin = GPIO_Pin_10;
	
    //输出模式
    beepstruct.GPIO_Mode = GPIO_Mode_OUT;
    //推免输出
    beepstruct.GPIO_OType = GPIO_OType_PP;
	//电阻
	beepstruct.GPIO_PuPd = GPIO_PuPd_UP;
	//传输速度
	beepstruct.GPIO_Speed = GPIO_Low_Speed;
	
	//此函数可以快捷 填写寄存器
    GPIO_Init(GPIOB,&beepstruct);
	
    //3.初始化引脚
    //给PB10 低电平
    GPIO_ResetBits(GPIOB,GPIO_Pin_10);
}


//打开蜂鸣器
void BEEP_TurnOn(void)
{
	//打开蜂鸣器高电平
	
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_SET);
}

//关闭蜂鸣器
void BEEP_TurnOff(void)
{
    GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_RESET);
}

//蜂鸣器alarm,限定次数
void BEEP_Alarm_Count(unsigned int count)
{
	
	while(count)
	{
		My_Delay(100);
		BEEP_TurnOn();
		My_Delay(100);
		BEEP_TurnOff();
		count--;
	}
}

//蜂鸣器一直警报
void BEEP_Alarm(void)
{
	
		GPIO_ToggleBits(GPIOB,GPIO_Pin_10);
		My_Delay(100);
	
}

//蜂鸣器和LED1同步
void BEEP_LED_To(unsigned int count)
{

	while(count)
	{
		My_Delay(100);
		BEEP_TurnOn();
		LED_TurnOn(LED1);
		My_Delay(100);
		BEEP_TurnOff();
		LED_TurnOff(LED1);
		count--;
	}
}




























