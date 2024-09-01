#include "user.h"
//拓展字符数组的方法
extern uint8_t zhao1[];
extern uint8_t shi1[];
extern uint8_t wen1[];
extern uint8_t du1[];

char Client_Data[24];
unsigned int Index_1 = 0;
extern char Send_Client_Data_Buff[13];
int _dsd = 0;
int flg = 0;

char Client_Number[2] = "";
char Client_temp[2] = "";
char Client_humi[2] = "";
char Client_illum[2] = "";

u8 Clinet_Tempreture[5] = "";
u8 Clinet_Humidness[5] = "";
u8 Clinet_Illumination[5] = "";


char Send_Client_Data_Server[13]= "";
void uart2init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//1 串口时钟配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//2 D组时钟配置
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	//3引脚功能配置
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);
	
	//4.GPIO初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	//输出类型不要配置
	GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	//5.//串口初始化
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART2,&USART_InitStructure);
	
	//6串口1使能
	USART_Cmd(USART2,ENABLE);
	//7串口中断使能
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	//8中断配置
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStructure);		
}
//中断服务函数
void USART2_IRQHandler(void)
{ 

	
	if(USART_GetFlagStatus(USART2,USART_IT_RXNE))
	{
		Client_Data[Index_1] = USART_ReceiveData(USART2);
		Index_1++;
	}
	_dsd = 1;
	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	
	
}

//void USART2_IRQHandler()
//{	
//	if(USART_GetFlagStatus(USART2,USART_IT_RXNE))
//	{
//		Client_Data[Index_1] = USART_ReceiveData(USART2);
//		Index_1++;
//	}
//	

//  else{
//		//BEEP_TurnOn();
//		//Index_1 = 0;

//		//printf("%s\r\n",Client_Data);
//	}
//	
//	
//	USART_ClearITPendingBit(USART2,USART_IT_RXNE);	
//}

//void USART2_IRQHandler(void)  
//{  
//    if (USART_GetFlagStatus(USART2, USART_IT_RXNE))  
//    {  
//        char res = USART_ReceiveData(USART2);  
//        if (Index_1 < sizeof(Client_Data) - 1)  
//        {  
//            Client_Data[Index_1++] = res;  
//            if (res == '\n')  
//            {  
//                Client_Data[Index_1] = '\0';  // Null-terminate the string  
//                _dsd =1 ;
//                if (strcmp(Client_Data, "1234") == 0)  
//                {  
//                    BEEP_TurnOn();  
//                }  
//                else if (strcmp(Client_Data, "close beep") == 0)  
//                {  
//                    BEEP_TurnOff();  
//                }  
//                // Reset index and clear buffer for next string  
//                
//                memset(Client_Data, 0, sizeof(Client_Data));  
//            }  
//        }  
//    }  
//    USART_ClearITPendingBit(USART2, USART_IT_RXNE);  
//}

//}
//void ProcessReceivedString(char *str)
//{
//if (strcmp(str, "1\n") == 0)  
//    {  
//        BEEP_TurnOn();  
//    }  
//    else if (strcmp(str, "2\n") == 0)  
//    {  
//        BEEP_TurnOff();  
//    } 
//}

////中断服务函数
//void USART2_IRQHandler(void)
//{
//	unsigned char  res;
//	
//	if(USART_GetITStatus(USART2,USART_IT_RXNE))
//	{	
//		res=USART_ReceiveData(USART2);
//		if(Index < Cient_Data_Size -1)
//		{
//		  Client_Data[Index++] = res;
//		  if(res == '\n')
//			{
//			Client_Data[Index] = '\0';
//      ProcessReceivedString(Client_Data);
//			Index = 0;
//			
//			}
//		}
//		
//	}
//	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
//}

void Client_Get_Data()
{



}

void usart_sendstr(USART_TypeDef * USATRX , char * str,int size)
{
    int i = 0;
    USART_ClearFlag(USATRX,USART_FLAG_TC);
    for(i=0;i<size;i++)
    {
        USART_SendData(USATRX,*str);
        while(RESET == USART_GetFlagStatus(USATRX,USART_FLAG_TC));
        USART_ClearFlag(USATRX,USART_FLAG_TC);
        str++;
    }
}

void setWifi(void)
{ 
	  usart_sendstr(USART2,"AT+RESTORE\r\n",sizeof("AT+RESTORE\r\n"));
	  delay_ms(5000);
	  usart_sendstr(USART2,"AT+RESTORE\r\n",sizeof("AT+RESTORE\r\n"));
    delay_ms(4000);
	  usart_sendstr(USART2,"AT\r\n",sizeof("AT\r\n"));
    delay_ms(2000);
    usart_sendstr(USART2,"AT+CWMODE=3\r\n",sizeof("AT+CWMODE=3\r\n"));
    delay_ms(3000);
    usart_sendstr(USART2,"AT+CWSAP=\"why\",\"12345678\",1,4\r\n",sizeof("AT+CWSAP=\"why\",\"12345678\",1,4\r\n"));
    delay_ms(5000);
    usart_sendstr(USART2,"AT+CIPMUX=1\r\n",sizeof( "AT+CIPMUX=1\r\n"));
    delay_ms(2000);
    usart_sendstr(USART2,"AT+CIPSERVER=1,8089\r\n",sizeof("AT+CIPSERVER=1,8089\r\n"));
	  delay_ms(2000);
    usart_sendstr(USART2,"AT+CWJAP=\"yrl\",\"12345678\"\r\n",sizeof("AT+CWJAP=\"yrl\",\"12345678\"\r\n"));
    delay_ms(5000);
    usart_sendstr(USART2,"AT+CIPSTART=1,\"TCP\",\"192.168.30.222\",6666\r\n",sizeof("AT+CIPSTART=1,\"TCP\",\"192.168.30.222\",6666\r\n"));
    delay_ms(3000);
	  usart_sendstr(USART2,"AT+CIPSEND=1,5\r\n",sizeof("AT+CIPSEND=1,5\r\n"));
	  delay_ms(3000);
	  usart_sendstr(USART2,"12345\r\n",sizeof("12345\r\n"));
		flg = 1;
}

void Send_Client_Data()
{
	  usart_sendstr(USART2,"AT+CIPSEND=1,13\r\n",sizeof("AT+CIPSEND=1,13\r\n"));
	  delay_ms(2000);
    usart_sendstr(USART2,Send_Client_Data_Buff,sizeof(Send_Client_Data_Buff));
	  delay_ms(3000);
}

void Show_Client_Data()
{
   Client_Number[0] = Send_Client_Data_Buff[1];
	 Client_temp[0] = Send_Client_Data_Buff[3];
	 Client_temp[1] = Send_Client_Data_Buff[4];
	 Client_humi[0] = Send_Client_Data_Buff[5];
	 Client_humi[1] = Send_Client_Data_Buff[6];
	 Client_illum[0] = Send_Client_Data_Buff[7];
	 Client_illum[1] = Send_Client_Data_Buff[8];
	 sprintf(Clinet_Tempreture, "%d.%d", Client_temp[0], Client_temp[1]); 
	 sprintf(Clinet_Humidness,"%d.%d",Client_humi[0], Client_humi[1]);
	 sprintf(Clinet_Illumination,"%d%d",Client_illum[0], Client_illum[1]);
	 printf("住户一：温度：%s 湿度：%s 光照：%s\r\n",Clinet_Tempreture,Clinet_Humidness,Clinet_Illumination);
}



