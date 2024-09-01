#include "user.h"

#define USART_REC_LEN6 200
u8 USART_RX_BUF6[USART_REC_LEN6];
u16 USART_RX_STA6 = 0;

void uart6_init()
{
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
//	UART_InitTypeDef UART_Initstructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//����ʱ�� 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	//PC6,PC7��������
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6);
 
	//GPIO��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	//���ڳ�ʼ��
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART6,&USART_InitStructure);
	
	USART_Cmd(USART6,ENABLE);
	
	USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	//�����ж�ʹ�� ��ʼ�� --���ܼĴ�������������ж�
	
	
}

void USART6_IRQHandler(void)
{
  u8 Res;
				
	if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res = USART_ReceiveData(USART6);	//��ȡ���յ�������
		
		if((USART_RX_STA6 & 0x8000) == 0) //����δ���
		{
			if(USART_RX_STA6 < USART_REC_LEN6)	//�����Խ�������
			{
				USART_RX_BUF6[USART_RX_STA6++] = Res;	//��¼���յ���ֵ
			}
			else
			{
				USART_RX_STA6 |= 1 << 15;				//ǿ�Ʊ�ǽ������
			}
		}
   } 


}

void Usart_SendData(u8 data)
{
	while((USART6->SR & 0X40) == 0);
	USART6->DR = data;
}
 
void USART6_SendString(u8 *DAT, u8 len)
{
	u8 i;
	for(i = 0; i < len; i++)
	{
		Usart_SendData(*DAT++);
	}
}


//ѡ�񱳾�����2��(0���ޱ�������  1-15���������ֿ�ѡ)
//m[0~16]:0��������Ϊ������16���������������
//v[0~16]:0�ʶ�����Ϊ������16�ʶ��������
//t[0~5]:0�ʶ�����������5�ʶ��������
//���������ù�����ο������ֲ�
void SYN_FrameInfo(u8 *HZdata)
{
  /****************��Ҫ���͵��ı�**********************************/
  unsigned  char  Frame_Info[50];
  unsigned  char  HZ_Length;
  unsigned  char  ecc  = 0;  			//����У���ֽ�
  unsigned  int i = 0;
  HZ_Length = strlen((char*)HZdata); 			//��Ҫ�����ı��ĳ���
 
  /*****************֡�̶�������Ϣ**************************************/
  Frame_Info[0] = 0xFD ; 			//����֡ͷFD
  Frame_Info[1] = 0x00 ; 			//�������������ȵĸ��ֽ�
  Frame_Info[2] = HZ_Length + 3; 		//�������������ȵĵ��ֽ�
  Frame_Info[3] = 0x01 ; 			//���������֣��ϳɲ�������
  Frame_Info[4] = 0x01 | 0 << 4 ; //����������������������趨
 
  /*******************У�������***************************************/
  for(i = 0; i < 5; i++)   				//���η��͹���õ�5��֡ͷ�ֽ�
  {
    ecc = ecc ^ (Frame_Info[i]);		//�Է��͵��ֽڽ������У��
  }
 
  for(i = 0; i < HZ_Length; i++)   		//���η��ʹ��ϳɵ��ı�����
  {
    ecc = ecc ^ (HZdata[i]); 				//�Է��͵��ֽڽ������У��
  }
  /*******************����֡��Ϣ***************************************/
  memcpy(&Frame_Info[5], HZdata, HZ_Length);
  Frame_Info[5 + HZ_Length] = ecc;
  USART6_SendString(Frame_Info, 5 + HZ_Length + 1);
}

/***********************************************************
* ��    �ƣ� YS_SYN_Set(u8 *Info_data)
* ��    �ܣ� ������	�������
* ��ڲ����� *Info_data:�̶���������Ϣ����
* ���ڲ�����
* ˵    �����������������ã�ֹͣ�ϳɡ���ͣ�ϳɵ����� ��Ĭ�ϲ�����9600bps��
* ���÷�����ͨ�������Ѿ�������������������á�
**********************************************************/
void YS_SYN_Set(u8 *Info_data)
{
  u8 Com_Len;
  Com_Len = strlen((char*)Info_data);
  USART6_SendString(Info_data, Com_Len);
}


//void uart5_init()
//{
//  GPIO_InitTypeDef GPIO_InitStructure;
//	UART
//	NVIC_InitTypeDef NVIC_InitStructure;
//	//����ʱ�� 
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
//	
//	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_USART6);
//	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_USART6);
//		//GPIO��ʼ��
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_Init(GPIOC,&GPIO_InitStructure);

//}


