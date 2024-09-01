#include "user.h"

extern int PWM_LED2_flag;
//初始化PWM_ LED2
void PWM_LED3_Config()
{
	

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;


	//1TIM1时钟配置
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE); 
	//2E组时钟配置
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 
	
	//3重启动定时器1
	TIM_DeInit(TIM1);
	
	//4E组第9个引脚复用为定时器1
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); 
	
	//5配置E组引脚配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;   
	//复用功能
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  
	//速度100MHz
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
	//推挽复用输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   
	//上拉
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	//5初始化引脚
	GPIO_Init(GPIOE,&GPIO_InitStructure);  
	
	//6高级定时器初始化
	TIM_TimeBaseStructure.TIM_Prescaler=400;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=100;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	//TIM_TimeBaseStructure.TIM_RepetitionCounter = 1; 
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
		
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 	        
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	//7根据T指定的参数初始化外设TIM1 4OC1
//	TIM_OCInitStructure.TIM_Pulse = 100;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
	//8.使能定时器
	TIM_Cmd(TIM1, ENABLE);  	
	//9控制输出模式使能
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void PWM_LED_ON()
{
	u16 led0pwmval = 0;    
	u8 dir=1;
	PWM_LED3_Config();
	while(1) //实现比较值从0-300递增，到300后从300-0递减，循环
	{
		if(PWM_LED2_flag == 1)
		{
			delay_ms(10);
			//dir==1 led0pwmval递增
			if(dir)
				led0pwmval++;
			else     //dir==0 led0pwmval递减 
				led0pwmval--;
			//led0pwmval到达300后，方向为递减
			if(led0pwmval>100)
				dir=0;
			//led0pwmval递减到0后，方向改为递增
			if(led0pwmval==0)
				dir=1;	
			//修改比较值，修改占空比	
			TIM_SetCompare1(TIM1,led0pwmval);	
			
		}
		else
		{
			TIM_SetCompare1(TIM1,0);	
		}

 		
	}

	
}































