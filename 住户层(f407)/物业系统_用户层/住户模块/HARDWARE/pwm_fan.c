#include "user.h"
//控制风扇需要PWM信号，PWM信号需要生成->可以通过定时器生成->通过配置通道生成->哪些定时器？-/TIM1_CH3N/TIM8_CH3N/TIM12_CH2
//此处选择TIM12_CH2来生成PWM信号
//配置->1.使能TIM12定时器和GPIOB端口的时钟(使用任何外设前，都需要使能它们的时钟)2.复用TIM12引脚(用于输入捕获、输出比较、PWM生成)
//3.将GPIOB-15配置为复用模式4.配置定时器，设置了定时器的基本参数，分频器，自动重载寄存器周期，计数器模式->这些参数决定了PWM的频率
//5.配置timer12的比较通道2，以此来产生PWM信号6.启动OC2通道的预装载功能，可以更新CCR寄存器的值。这对于在运行时平滑地调整PWM占空比非常有用
//7.这与OC2的预装载功能类似，但它影响的是定时器的周期（即ARR寄存器的值）。启用此功能后，你可以在不影响当前定时器周期的情况下更新ARR的值，这对于在运行时调整PWM频率非常有用。
//配置pwm风扇
//PB15 + TIMER12_CH2

void TIMER12_CH2_PWM_PB15_Config()
{	
//1.配置时钟 APB1 42mhz -GPIO时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
//2.复用配置 b组15号引脚配置成复用功能定时器12
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM12);
//3.GPIO引脚配置成复用模式
	GPIO_InitTypeDef fanstruct = {0};
	//引脚号码
	fanstruct.GPIO_Pin = 	GPIO_Pin_15;
	//复用模式
	fanstruct.GPIO_Mode = GPIO_Mode_AF;
	//上拉电阻
	fanstruct.GPIO_PuPd = GPIO_PuPd_UP;
	//响应速度
	fanstruct.GPIO_Speed = GPIO_Low_Speed;
	//初始化端口函数
	GPIO_Init(GPIOB,&fanstruct);
	//4.配置定时器
	TIM_TimeBaseInitTypeDef tim12struct = {0};
	tim12struct.TIM_Prescaler = 84-1;
	tim12struct.TIM_Period = 20000-1;
	tim12struct.TIM_CounterMode = TIM_CounterMode_Up;
	tim12struct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM12,&tim12struct);
	//5.配置timer12 通道2
	TIM_OCInitTypeDef oc2struct = {0};
	oc2struct.TIM_OCMode =TIM_OCMode_PWM1;
	oc2struct.TIM_OCPolarity = TIM_OCPolarity_High;
	oc2struct.TIM_OutputState =	TIM_OutputState_Enable;
	TIM_OC2Init(TIM12,&oc2struct);
	//设置CCR2的值
	//TIM12->CCR2 = (19999 / 2) - 1; 
	//6比较捕获寄存器使能
	TIM_OC2PreloadConfig(TIM12,TIM_OCPreload_Enable);
	//7.自动重装载寄存器使能 预装载
	TIM_ARRPreloadConfig(TIM12,ENABLE);
	//8.定时器本身使能
	//TIM_Cmd(TIM12,ENABLE);
}
//打开风扇函数
void Fan_TurnOn()
{	
	TIM_Cmd(TIM12,ENABLE);
	Fan_Control(10000);
}

//关闭风扇
void Fan_TurnOff()
{	
		Fan_Control(0);
  //TIM_Cmd(TIM12,DISABLE);问题代码
		delay_ms(500);
}

//控制风扇函数 低速 高速 中速 10000
void Fan_Control(unsigned int cvalue)
{
   TIM_SetCompare2(TIM12,cvalue);
}

