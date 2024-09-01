#include "user.h"
//移植的文件
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
//重定义fputc函数  发
int fputc(int ch, FILE *f) 
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}
//void myprintf(char str[]);
void USART1_Config()
{
  //配置USART1时钟 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	//配置GPIOA时钟
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	//引脚复用配置A组9 10配置成串口
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	//配置GPIO引脚m，模式复用模式
   GPIO_InitTypeDef GPIOA_Initstruct;
	 GPIOA_Initstruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10 ;
	 GPIOA_Initstruct.GPIO_Mode = GPIO_Mode_AF;
   GPIOA_Initstruct.GPIO_PuPd = GPIO_PuPd_UP;
	 GPIOA_Initstruct.GPIO_Speed = GPIO_Low_Speed;
	 
	 GPIO_Init(GPIOA,&GPIOA_Initstruct);
	
	//配置串口参数 
	 USART_InitTypeDef USART1_Initstruct;
	 USART1_Initstruct.USART_BaudRate = 115200;
	 //硬件流控制否定
	 USART1_Initstruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	 //输入输出模式
	 USART1_Initstruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	 //校验位NO 不校验
	 USART1_Initstruct.USART_Parity = USART_Parity_No;
	 //停止位1
	 USART1_Initstruct.USART_StopBits = USART_StopBits_1;
	 //字长
	 USART1_Initstruct.USART_WordLength = USART_WordLength_8b;
	 USART_Init(USART1,&USART1_Initstruct);
	 //串口电路使能
	 USART_Cmd(USART1,ENABLE);
	 
	 //使能 USART1 接收中断
	 USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	 //NVIC配置
	 NVIC_InitTypeDef NVIC_Initstruct;
	 //串口类型  串口1全局中断
	 NVIC_Initstruct.NVIC_IRQChannel = USART1_IRQn;
	 NVIC_Initstruct.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority = 0;
	 NVIC_Initstruct.NVIC_IRQChannelSubPriority = 0;
	 NVIC_Init(&NVIC_Initstruct);
}


//char res[20] = "";

//char rx_buffer[20];  // 接收缓冲区
//volatile uint8_t rx_index = 0;   // 接收缓冲区索引
//volatile bool rx_complete = false;  // 接收完成标志
//void USART1_IRQHandler()
//{	
//	unsigned char res = 0;
//	res = USART_ReceiveData(USART1);
//	if(res == 49)//1的ascii码
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
			//上位机输入字符打开led


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
void USART1_IRQHandler(void)                	//串口1中断服务程序 收
{
	u8 Res;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
		
		if((USART_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART_RX_STA&0x4000)//接收到了0x0d
			{
				if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
				//---------------------------------//
				else 
				{
					USART_RX_STA|=0x8000;//接收完成了
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
			else //还没收到0X0D
			{	
				if(Res==0x0d)
					{
							USART_RX_STA|=0x4000;
					}
					
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
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




