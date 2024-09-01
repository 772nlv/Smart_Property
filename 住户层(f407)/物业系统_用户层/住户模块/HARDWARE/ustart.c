#include "user.h"
//��ֲ���ļ�
extern int flagled;
extern int flagbeep;
extern int flagfan;
extern int flagdata;
extern int flagpage2;
extern int flagat24history;
extern int flagw25history;
extern int flagst25 ;
#define USART_REC_LEN  			500  	
#define EN_USART1_RX 			1		
u8  USART_RX_BUF[USART_REC_LEN];
u16 USART_RX_STA;
//�ض���fputc����  ��
int fputc(int ch, FILE *f) 
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}
//void myprintf(char str[]);
void USART1_Config()
{
  //����USART1ʱ�� 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	//����GPIOAʱ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//���Ÿ�������A��9 10���óɴ���
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	//����GPIO����m��ģʽ����ģʽ
   GPIO_InitTypeDef GPIOA_Initstruct;
	 GPIOA_Initstruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10 ;
	 GPIOA_Initstruct.GPIO_Mode = GPIO_Mode_AF;
   GPIOA_Initstruct.GPIO_PuPd = GPIO_PuPd_UP;
	 GPIOA_Initstruct.GPIO_Speed = GPIO_Low_Speed;
	 
	 GPIO_Init(GPIOA,&GPIOA_Initstruct);
	
	//���ô��ڲ��� 
	 USART_InitTypeDef USART1_Initstruct;
	 USART1_Initstruct.USART_BaudRate = 115200;
	 //Ӳ�������Ʒ�
	 USART1_Initstruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	 //�������ģʽ
	 USART1_Initstruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	 //У��λNO ��У��
	 USART1_Initstruct.USART_Parity = USART_Parity_No;
	 //ֹͣλ1
	 USART1_Initstruct.USART_StopBits = USART_StopBits_1;
	 //�ֳ�
	 USART1_Initstruct.USART_WordLength = USART_WordLength_8b;
	 USART_Init(USART1,&USART1_Initstruct);
	 //���ڵ�·ʹ��
	 USART_Cmd(USART1,ENABLE);
	 
	 //ʹ�� USART1 �����ж�
	 USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	 //NVIC����
	 NVIC_InitTypeDef NVIC_Initstruct;
	 //��������  ����1ȫ���ж�
	 NVIC_Initstruct.NVIC_IRQChannel = USART1_IRQn;
	 NVIC_Initstruct.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority = 0;
	 NVIC_Initstruct.NVIC_IRQChannelSubPriority = 0;
	 NVIC_Init(&NVIC_Initstruct);
}


//char res[20] = "";

//char rx_buffer[20];  // ���ջ�����
//volatile uint8_t rx_index = 0;   // ���ջ���������
//volatile bool rx_complete = false;  // ������ɱ�־
//void USART1_IRQHandler()
//{	
//	unsigned char res = 0;
//	res = USART_ReceiveData(USART1);
//	if(res == 49)//1��ascii��
//	{
//	Beep_Open();
//	USART_SendData(USART1,res+2);
//	
//	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//	}
//		if(res == 'a')
//	{
//	Beep_Close();
//	USART_SendData(USART1,res+2);
//	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//	}
//		if(res == 'b')
//	{
//	LED_TurnOn(LED1);
//	myprintf("LED1 OPEN");
//	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//	}
//		if(res == 'c')
//	{
//	LED_TurnOff(LED1);
//	myprintf("LED1 close");
//	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//	} 
			//��λ�������ַ���led


//void myprintf(char str[])
//{
//        
//        u8 i = 0 ; 
//        while(str[i] != '\0')
//        {
//                USART_SendData(USART1,*(str+i));
//                i++;
//                delay_ms(2);
//        }
//}
void USART1_IRQHandler(void)                	//����1�жϷ������ ��
{
	u8 Res;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
		
		if((USART_RX_STA&0x8000)==0)//����δ���
		{
			if(USART_RX_STA&0x4000)//���յ���0x0d
			{
				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
				//---------------------------------//
				else 
				{
					USART_RX_STA|=0x8000;//���������
					if (strncmp((char*)USART_RX_BUF, "at24history", 11) == 0)  
					{	
						flagat24history = 1;
					}
					if (strncmp((char*)USART_RX_BUF, "stinw25", 7) == 0)  
					{	
						flagst25 = 1;
					}
					if (strncmp((char*)USART_RX_BUF, "w25history", 10) == 0)  
					{	
						flagw25history = 1;
					}
					if (strncmp((char*)USART_RX_BUF, "showpage2", 9) == 0)  
					{	
						flagpage2 = 1;
					}
					if (strncmp((char*)USART_RX_BUF, "showdata", 8) == 0)  
					{	
						flagdata = 1;
					}
					if (strncmp((char*)USART_RX_BUF, "openflowled", 11) == 0)  
					{	
						flagled = 1;
					}
					if (strncmp((char*)USART_RX_BUF, "closeflowled", 12) == 0)  
					{	
						flagled = 0;
					}
					if (strncmp((char*)USART_RX_BUF, "openflowbeep", 12) == 0)  
					{	
						flagbeep = 1;
						
					}
					if (strncmp((char*)USART_RX_BUF, "closeflowbeep", 13) == 0)  
					{	
						flagbeep = 0;
					}
						if (strncmp((char*)USART_RX_BUF, "openflowfan", 11) == 0)  
					{	
						flagfan = 1;
					}
						if (strncmp((char*)USART_RX_BUF, "closeflowfan", 12) == 0)  
					{	
						flagfan = 0;
					}
					memset(USART_RX_BUF, 0, sizeof(USART_RX_BUF));  

          USART_RX_STA = 0;
        } 
					
			}
			
			//----------------------------------------//
			else //��û�յ�0X0D
			{	
				if(Res==0x0d)
					{
							USART_RX_STA|=0x4000;
					}
					
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}  
				USART_ClearITPendingBit(USART1,USART_IT_RXNE);
  } 
	
}
//char res[20] = "";
//unsigned int i =0;
//void USART1_IRQHandler()
//{
//	if(USART_GetFlagStatus(USART1,USART_IT_RXNE)==1)
//	{
//		
//		res[i] = USART_ReceiveData(USART1);
//		i++;
//	}
//	if(!strcmp(res,"open"))
//	{
//		Beep_Open();
//		i =0;
//		memset(res,0,20);
//	}
//	if(!strcmp(res,"close"))
//	{
//		Beep_Close();
//		i =0;
//		memset(res,0,20);
//	}
//	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//}




