#include "user.h"



//1.��ֲ�������Ժ� ���ص��Լ��Ĺ�����
#define USART_REC_LEN  			200  	//??????????????? 200
#define EN_USART1_RX 			1		//????1??/?????0??????1????
u8  USART_RX_BUF[USART_REC_LEN];
u16 USART_RX_STA;
//�ض���fputc���� 
int fputc(int ch, FILE *f) 
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}

int PWM_LED2_flag = 0;
int COLLECT_DATA_flag = 1;
//PWM����������״̬λ
extern int PWM_BEEP_flag;
char res[24] = "";
unsigned int i = 0;
//оƬ�����6������
void USART1_Config()
{
	//1������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	
	//2���������ţ���A�� 9 10 ���óɴ��ڹ��ܣ�
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);	
	
	//3������GPIO����
	GPIO_InitTypeDef Usart_GpioA_struct;
	//����ģʽ
	Usart_GpioA_struct.GPIO_Mode = GPIO_Mode_AF;
	//���ű��
	Usart_GpioA_struct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	//��������
	Usart_GpioA_struct.GPIO_PuPd = GPIO_PuPd_UP;
	//��Ӧ�ٶ�
	Usart_GpioA_struct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOA,&Usart_GpioA_struct);
	
	//4�����ô��ڲ���
	USART_InitTypeDef usart1_struct;
	usart1_struct.USART_BaudRate = 115200;
	usart1_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart1_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart1_struct.USART_Parity = USART_Parity_No;
	usart1_struct.USART_StopBits = USART_StopBits_1;
	usart1_struct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&usart1_struct);
	
	
	//5�����ڵ�·ʹ�ܣ�
	USART_Cmd(USART1,ENABLE);
	
	//6��NVIC �жϿ���������
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannel = USART1_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
	
	//�����ж�ʹ�� ��ʼ�� --���ܼĴ�������������ж�
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
}

//ǰ�����óɹ����ú�������ʹ��
//�жϺ���
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
	



//void USART1_IRQHandler(void)                	//����1�жϷ������
//{
//	u8 Res;

//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//	{
//		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
//		
//		if((USART_RX_STA&0x8000)==0)//����δ���
//		{
//			if(USART_RX_STA&0x4000)//���յ���0x0d
//			{
//				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
//				else USART_RX_STA|=0x8000;	//��������� 
//			}
//			else //��û�յ�0X0D
//			{	
//				if(Res==0x0d)USART_RX_STA|=0x4000;
//				else
//				{
//					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//					USART_RX_STA++;
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
//				}		 
//			}
//		}   		 
//  } 

//}





















