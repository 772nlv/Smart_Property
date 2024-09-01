#include "user.h"

//1.配置 pwm风扇
//引脚是PB15 定时器是TIM12 通道2
void TIM12_CH2_PB15_Fan_Config()
{
	
	//1、配置时钟、使能TIM12 、PB15
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);//
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	
	//2、复用配置PB15，配置成定时器
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM12);
	
	//3、配置引脚 PB15
	GPIO_InitTypeDef Fan_struct;
	//复用模式
	Fan_struct.GPIO_Mode = GPIO_Mode_AF;
	//引脚编号
	Fan_struct.GPIO_Pin = GPIO_Pin_15;
	//上拉电阻
	Fan_struct.GPIO_PuPd = GPIO_PuPd_UP;
	//响应速度
	Fan_struct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOB,&Fan_struct);
	
	//4、配置定时器
	TIM_TimeBaseInitTypeDef timer12struct;
	//预分频 -  84mhz  / 84 = 1mhz
	//一个机器周期 1us
	timer12struct.TIM_Period = 84 - 1;	
	//定时周期 20ms
	timer12struct.TIM_Prescaler = 20000; 
	//向上计数
	timer12struct.TIM_CounterMode = TIM_CounterMode_Up;
	timer12struct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM12,&timer12struct);
	
	//5、配置timer通道
	TIM_OCInitTypeDef oc2struct;
	//选择模式 PWM1
	oc2struct.TIM_OCMode = TIM_OCMode_PWM1;
	//极性--高电平
	oc2struct.TIM_OCPolarity = TIM_OCPolarity_High;
	//输出使能
	oc2struct.TIM_OutputState = TIM_OutputState_Enable;
	//初始化
	TIM_OC2Init(TIM12,&oc2struct);
	
	//6、比较捕获定时器使能
	TIM_OC2PreloadConfig(TIM12,TIM_OCPreload_Enable);
	
	//7、自动重装载值使能
	TIM_ARRPreloadConfig(TIM12,ENABLE);
	
	//8、定时器本身使能
	TIM_Cmd(TIM12,ENABLE);
}

//2.打开风扇函数
void Fan_TurnOn()
{
//	BEEP_TurnOn();
	TIM_Cmd(TIM12,ENABLE);
	
	delay_ms(1);
}

//3.关闭风扇
void Fan_TurnOff()
{
	TIM_Cmd(TIM12,DISABLE);
	//3、配置引脚 PB15
	GPIO_InitTypeDef Fan_struct;
	//复用模式
	Fan_struct.GPIO_Mode = GPIO_Mode_OUT;
	//引脚编号
	Fan_struct.GPIO_Pin = GPIO_Pin_15;
	//上拉电阻
	Fan_struct.GPIO_PuPd = GPIO_PuPd_UP;
	//响应速度
	Fan_struct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOB,&Fan_struct);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	delay_ms(1);
}

//4、控制风扇
void Fan_Control(unsigned int value)
{
	TIM_SetCompare2(TIM12,value);
	delay_ms(1);

}

void Fan_Low_Control()
{
	TIM_SetCompare2(TIM12,200);
	delay_ms(1);
}

void Fan_MId_Control()
{
	TIM_SetCompare2(TIM12,800);
	delay_ms(1);
}

void Fan_High_Control()
{
	TIM_SetCompare2(TIM12,2000);
	delay_ms(1);
}
















