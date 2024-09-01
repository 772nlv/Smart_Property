#include "user.h"

extern char tempvalue_1[128];
extern char humivalue_1[128];
extern char lihgtvalue_1[128];
extern char potenvalue_1[128];

//系统开机
extern int SYSTEM_ON_FLAG;
//采集数据状态位
extern int COLLECT_DATA_ON_FLAG;
//中断KEY_1相关函数声明
void INTERRUPT_KEY1_Config(void)
{
	//1、配置时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//配置GPIO接口
	//2.初始化IO接口
    GPIO_InitTypeDef keystruct;
    //引脚号码
    keystruct.GPIO_Pin = GPIO_Pin_4;
    //输入模式
    keystruct.GPIO_Mode = GPIO_Mode_IN;
    //上拉电阻
    keystruct.GPIO_PuPd = GPIO_PuPd_UP;
    //低速
    keystruct.GPIO_Speed = GPIO_Low_Speed;
    //初始化
    GPIO_Init(GPIOE,&keystruct);
	
	//3、外部中断配置.E组四号引脚配置成中断功能
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource4);
	
	//4、外部中断初始化
	EXTI_InitTypeDef exitstruct;
	
	exitstruct.EXTI_Line = EXTI_Line4;
	exitstruct.EXTI_LineCmd = ENABLE;
	exitstruct.EXTI_Trigger = EXTI_Trigger_Falling;
	exitstruct.EXTI_Mode = EXTI_Mode_Interrupt;
	
	EXTI_Init(&exitstruct);
	
	//中断控制器
	NVIC_InitTypeDef nvicstruct;
	//中断类型 —— 外部中断
	nvicstruct.NVIC_IRQChannel =  EXTI4_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	
	//抢占优先级 四选一
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	//响应优先级
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}

//中断KEY_2相关函数声明
void INTERRUPT_KEY2_Config(void)
{
	//1、配置时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	
	//配置GPIO接口
	//2.初始化IO接口
    GPIO_InitTypeDef keystruct;
    //引脚号码
    keystruct.GPIO_Pin = GPIO_Pin_5;
    //输入模式
    keystruct.GPIO_Mode = GPIO_Mode_IN;
    //上拉电阻
    keystruct.GPIO_PuPd = GPIO_PuPd_UP;
    //低速
    keystruct.GPIO_Speed = GPIO_Low_Speed;
    //初始化
    GPIO_Init(GPIOE,&keystruct);
	
	//3、外部中断配置.E组四号引脚配置成中断功能
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource5);
	
	//4、外部中断初始，配置触发条件
	EXTI_InitTypeDef exitstruct;
	
	exitstruct.EXTI_Line = EXTI_Line5;
	exitstruct.EXTI_LineCmd = ENABLE;
	exitstruct.EXTI_Trigger = EXTI_Trigger_Falling;
	exitstruct.EXTI_Mode = EXTI_Mode_Interrupt;
	
	EXTI_Init(&exitstruct);
	
	//中断控制器
	NVIC_InitTypeDef nvicstruct;
	//配置中断分组；
	nvicstruct.NVIC_IRQChannel =  EXTI9_5_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	
	//抢占优先级 四选一
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	//响应优先级
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}

//中断KEY_3相关函数声明
void INTERRUPT_KEY3_Config(void)
{
	//1、配置时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//配置GPIO接口
	//2.初始化IO接口
    GPIO_InitTypeDef keystruct;
    //引脚号码
    keystruct.GPIO_Pin = GPIO_Pin_6;
    //输入模式
    keystruct.GPIO_Mode = GPIO_Mode_IN;
    //上拉电阻
    keystruct.GPIO_PuPd = GPIO_PuPd_UP;
    //低速
    keystruct.GPIO_Speed = GPIO_Low_Speed;
    //初始化
    GPIO_Init(GPIOE,&keystruct);
	
	//3、外部中断配置.E组6号引脚配置成中断功能
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource6);
	
	//4、外部中断初始化
	EXTI_InitTypeDef exitstruct;
	
	exitstruct.EXTI_Line = EXTI_Line6;
	exitstruct.EXTI_LineCmd = ENABLE;
	exitstruct.EXTI_Trigger = EXTI_Trigger_Falling;
	exitstruct.EXTI_Mode = EXTI_Mode_Interrupt;
	
	EXTI_Init(&exitstruct);
	
	//中断控制器
	NVIC_InitTypeDef nvicstruct;
	//中断类型 —— 外部中断
	nvicstruct.NVIC_IRQChannel =  EXTI9_5_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	
	//抢占优先级 四选一
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	//响应优先级
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}
//中断KEY_4相关函数声明
void INTERRUPT_KEY4_Config(void)
{
	//1、配置时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//配置GPIO接口
	//2.初始化IO接口
    GPIO_InitTypeDef keystruct;
    //引脚号码
    keystruct.GPIO_Pin = GPIO_Pin_13;
    //输入模式
    keystruct.GPIO_Mode = GPIO_Mode_IN;
    //上拉电阻
    keystruct.GPIO_PuPd = GPIO_PuPd_UP;
    //低速
    keystruct.GPIO_Speed = GPIO_Low_Speed;
    //初始化
    GPIO_Init(GPIOC,&keystruct);
	
	//3、外部中断配置.C组13号引脚配置中断功能
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource13);
	
	//4、外部中断初始化
	EXTI_InitTypeDef exitstruct;
	
	exitstruct.EXTI_Line = EXTI_Line13;
	exitstruct.EXTI_LineCmd = ENABLE;
	exitstruct.EXTI_Trigger = EXTI_Trigger_Falling;
	exitstruct.EXTI_Mode = EXTI_Mode_Interrupt;
	
	EXTI_Init(&exitstruct);
	
	//中断控制器
	NVIC_InitTypeDef nvicstruct;
	//中断类型 —— 外部中断
	nvicstruct.NVIC_IRQChannel =  EXTI15_10_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	
	//抢占优先级 四选一
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	//响应优先级
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}

//中断函数
//函数的执行条件为PE4电平改变
//按键1中断
void EXTI4_IRQHandler()
{
	BEEP_TurnOn();
	delay_ms(20);
	BEEP_TurnOff();
	SYSTEM_ON_FLAG = 1;
	EXTI_ClearITPendingBit(EXTI_Line4);

}
//按键2，3中断
void EXTI9_5_IRQHandler()
{
	
	if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5))
	{
		BEEP_TurnOn();
		delay_ms(20);
		BEEP_TurnOff();
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
	if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6))
	{
		BEEP_TurnOn();
		delay_ms(20);
		BEEP_TurnOff();
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
}
//按键4中断
void EXTI15_10_IRQHandler()
{
	BEEP_TurnOn();
	delay_ms(20);
	BEEP_TurnOff();
	EXTI_ClearITPendingBit(EXTI_Line13);
}




















