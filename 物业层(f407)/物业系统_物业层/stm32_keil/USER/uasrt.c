#include "user.h"



//1.移植：看懂以后 加载到自己的工程中
#define USART_REC_LEN  			200  	//??????????????? 200
#define EN_USART1_RX 			1		//????1??/?????0??????1????
u8  USART_RX_BUF[USART_REC_LEN];
u16 USART_RX_STA;
//重定义fputc函数 
int fputc(int ch, FILE *f) 
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}

int PWM_LED2_flag = 0;
int COLLECT_DATA_flag = 1;
//PWM蜂鸣器数据状态位
extern int PWM_BEEP_flag;
char res[24] = "";
unsigned int i = 0;
//芯片外接了6个串口
void USART1_Config()
{
	//1、配置时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	
	//2、配置引脚，把A组 9 10 配置成串口功能；
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);	
	
	//3、配置GPIO引脚
	GPIO_InitTypeDef Usart_GpioA_struct;
	//复用模式
	Usart_GpioA_struct.GPIO_Mode = GPIO_Mode_AF;
	//引脚编号
	Usart_GpioA_struct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	//上拉电阻
	Usart_GpioA_struct.GPIO_PuPd = GPIO_PuPd_UP;
	//响应速度
	Usart_GpioA_struct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOA,&Usart_GpioA_struct);
	
	//4、配置串口参数
	USART_InitTypeDef usart1_struct;
	usart1_struct.USART_BaudRate = 115200;
	usart1_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart1_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart1_struct.USART_Parity = USART_Parity_No;
	usart1_struct.USART_StopBits = USART_StopBits_1;
	usart1_struct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&usart1_struct);
	
	
	//5、串口电路使能；
	USART_Cmd(USART1,ENABLE);
	
	//6、NVIC 中断控制器配置
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannel = USART1_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
	
	//串口中断使能 初始化 --接受寄存器不空引起的中断
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
}

//前面配置成功，该函数就能使用
//中断函数
void USART1_IRQHandler()
{	
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE))
	{
		res[i] = USART_ReceiveData(USART1);
		i++;
	}
	if(!strcasecmp(res,"open beep"))
	{
		BEEP_TurnOn();
		i = 0;
		PWM_BEEP_flag = 1; 

		memset(res,0,sizeof(res));
	}
	if(!strcasecmp(res,"open LED1"))
	{
		LED_TurnOn(LED1);
		i = 0;

		memset(res,0,sizeof(res));
	}
	if(!strcasecmp(res,"close beep"))
	{
		BEEP_TurnOff();
		i = 0;
		PWM_BEEP_flag = 0;

		memset(res,0,sizeof(res));
	}
	if(!strcasecmp(res,"close LED1"))
	{
		LED_TurnOff(LED1);
		i = 0;

		memset(res,0,sizeof(res));
	}
	if(!strcasecmp(res,"open LED2"))
	{
//		LED_TurnOn(LED2);
		i = 0;

		memset(res,0,sizeof(res));
		PWM_LED2_flag = 1;
	}
	if(!strcasecmp(res,"close LED2"))
	{
		i = 0;
		memset(res,0,sizeof(res));		
		PWM_LED2_flag = 0;
		TIM_SetCompare1(TIM1,0);
		LED_TurnOff(LED2);

		memset(res,0,sizeof(res));	
	}
	if(!strcasecmp(res,"open fan"))
	{
		Fan_Control(50);
		i = 0;
		memset(res,0,sizeof(res));

	}
	if(!strcasecmp(res,"close fan"))
	{
		Fan_Control(0);
		i = 0;
		memset(res,0,sizeof(res));

	}
	if(!strcasecmp(res,"low fan"))
	{
		Fan_Control(30);
		i = 0;
		memset(res,0,sizeof(res));

	}
	if(!strcasecmp(res,"middle fan"))
	{
		Fan_Control(80);
		i = 0;
		memset(res,0,sizeof(res));

	}
	if(!strcasecmp(res,"fast fan"))
	{
		Fan_Control(150);
		i = 0;
		memset(res,0,sizeof(res));

	}
	if(!strcasecmp(res,"start collect data"))
	{
		COLLECT_DATA_flag = 1;
		i = 0;
		memset(res,0,sizeof(res));
//		printf("COLLECT_DATA_flag:%d\r\n",COLLECT_DATA_flag);
	}
	if(!strcasecmp(res,"stop collect data"))
	{
		COLLECT_DATA_flag = 0;
		i = 0;
		memset(res,0,sizeof(res));
//		printf("COLLECT_DATA_flag:%d\r\n",COLLECT_DATA_flag);
	}
	
	
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);	
}
	



//void USART1_IRQHandler(void)                	//串口1中断服务程序
//{
//	u8 Res;

//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//	{
//		Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
//		
//		if((USART_RX_STA&0x8000)==0)//接收未完成
//		{
//			if(USART_RX_STA&0x4000)//接收到了0x0d
//			{
//				if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
//				else USART_RX_STA|=0x8000;	//接收完成了 
//			}
//			else //还没收到0X0D
//			{	
//				if(Res==0x0d)USART_RX_STA|=0x4000;
//				else
//				{
//					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//					USART_RX_STA++;
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
//				}		 
//			}
//		}   		 
//  } 

//}





















