#include "user.h"
//拓展字符数组的方法
extern uint8_t zhao1[];
extern uint8_t shi1[];
extern uint8_t wen1[];
extern uint8_t du1[];
extern char wendu[128];
extern char shidu[128];
extern char guangzhao[30];
char wendu[128] = "30";
char shidu[128] = "50";
char guangzhao[30] = "1000";
extern int flagled;
extern int flagbeep;
extern int flagfan;
//配置部分；
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);		
}
//中断服务函数
void USART2_IRQHandler()
{
	unsigned char  res;
	if(USART_GetITStatus(USART2,USART_IT_RXNE))
	{	
		res=USART_ReceiveData(USART2);
		switch(res)
		{
			//打开 
			case 1:
						 OLed_Fill(0x00);Oled_print(16,2,"OPEN FLOWLED");
						 flagled = 1;
			break;
			//关闭
			case 2:	OLed_Fill(0x00);Oled_print(16,2,"CLOSE FLOWLED");
							flagled = 0;
			break;
			//打开
			case 3:
							OLed_Fill(0);Oled_print(16,2,"OPEN FLOWBEEP"); 
							flagbeep = 1;
			break;
			//关闭
			case 4:
							OLed_Fill(0);Oled_print(16,2,"CLOSE FLOWBEEP");
							flagbeep = 0;
			break;
			//
			case 5:
					OLed_Fill(0);		Oled_print(16,2,"OPEN FLOWFAN");				
					flagfan = 1;
					;break;
			case 6:
					OLed_Fill(0);		Oled_print(16,2,"CLOSE FLOWFAN");	
					flagfan = 0;
					;break;
			//显示光照
			case 7:
					OLed_Fill(0);
					Oled_print(1,2,"light is");
					Oled_print(70,2,guangzhao);
					break;
			//输入错误
			//default: OLed_Fill(0);Oled_print(8,2,"INPUT ERROR!"); break;
		}
		
	}
	USART_ClearITPendingBit(USART2,USART_IT_ORE);
	USART_ReceiveData(USART2);
//	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
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
		usart_sendstr(USART2,"+++\r\n",sizeof("+++\r\n"));
		delay_ms(1000);	
		usart_sendstr(USART2,"AT+CIPCLOSE\r\n",sizeof("AT+CIPCLOSE\r\n"));
		delay_ms(1000);
    usart_sendstr(USART2,"AT\r\n",sizeof("AT\r\n"));
    delay_ms(1000);
    usart_sendstr(USART2,"AT+CWMODE=1\r\n",sizeof("AT+CWMODE=1\r\n"));
    delay_ms(2000);
    usart_sendstr(USART2,"AT+CWLAP\r\n",sizeof("AT+CWLAP\r\n"));
    delay_ms(3000);
    usart_sendstr(USART2,"AT+CWJAP=\"why\",\"12345678\"\r\n",sizeof("AT+CWJAP=\"why\",\"12345678\"\r\n"));
    delay_ms(5000);
		printf("wifi连接成功");
    usart_sendstr(USART2,"AT+CIPMUX=0\r\n",sizeof( "AT+CIPMUX=0\r\n"));
    delay_ms(2000);
    usart_sendstr(USART2,"AT+CIPMODE=1\r\n",sizeof("AT+CIPMODE=1\r\n"));
    delay_ms(2000);
    usart_sendstr(USART2,"AT+CIPSTART=\"TCP\",\"192.168.4.1\",8089\r\n",sizeof("AT+CIPSTART=\"TCP\",\"192.168.4.1\",8089\r\n"));
    delay_ms(2000);
		printf("tcp连接成功");
    usart_sendstr(USART2,"AT+CIPSEND\r\n",sizeof("AT+CIPSEND\r\n"));
    delay_ms(2000);
}

char sendhumi[3];
char sendtemp[3];
unsigned short int send_guang;
int send_voltage_mv;
extern uint8_t datapack[11];

void senddata(){
	usart_sendstr(USART2,datapack,sizeof(datapack));
	//delay_ms(10000);
	for(int i=0;i<11;i++)
	{
			printf("%x ",datapack[i]);
	}
}


