#include "user.h"

extern int PWM_LED2_flag;
//��ʼ��PWM_ LED2
void PWM_LED3_Config()
{
	

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;


	//1TIM1ʱ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE); 
	//2E��ʱ������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 
	
	//3��������ʱ��1
	TIM_DeInit(TIM1);
	
	//4E���9�����Ÿ���Ϊ��ʱ��1
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); 
	
	//5����E����������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;   
	//���ù���
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  
	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  
	//���츴�����
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;   
	//����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	//5��ʼ������
	GPIO_Init(GPIOE,&GPIO_InitStructure);  
	
	//6�߼���ʱ����ʼ��
	TIM_TimeBaseStructure.TIM_Prescaler=400;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=100;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	//TIM_TimeBaseStructure.TIM_RepetitionCounter = 1; 
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
		
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 	        
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	//7����Tָ���Ĳ�����ʼ������TIM1 4OC1
//	TIM_OCInitStructure.TIM_Pulse = 100;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure); 
	//8.ʹ�ܶ�ʱ��
	TIM_Cmd(TIM1, ENABLE);  	
	//9�������ģʽʹ��
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void PWM_LED_ON()
{
	u16 led0pwmval = 0;    
	u8 dir=1;
	PWM_LED3_Config();
	while(1) //ʵ�ֱȽ�ֵ��0-300��������300���300-0�ݼ���ѭ��
	{
		if(PWM_LED2_flag == 1)
		{
			delay_ms(10);
			//dir==1 led0pwmval����
			if(dir)
				led0pwmval++;
			else     //dir==0 led0pwmval�ݼ� 
				led0pwmval--;
			//led0pwmval����300�󣬷���Ϊ�ݼ�
			if(led0pwmval>100)
				dir=0;
			//led0pwmval�ݼ���0�󣬷����Ϊ����
			if(led0pwmval==0)
				dir=1;	
			//�޸ıȽ�ֵ���޸�ռ�ձ�	
			TIM_SetCompare1(TIM1,led0pwmval);	
			
		}
		else
		{
			TIM_SetCompare1(TIM1,0);	
		}

 		
	}

	
}































