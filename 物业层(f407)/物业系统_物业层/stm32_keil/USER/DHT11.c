#include "user.h"

char readBuff[5] = {0};
unsigned int tempvalue = 0;

//1、DHT11配置函数
void DHT11_Config()
{
	//配置时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	//配置引脚 PA3
	GPIO_InitTypeDef dht11struct;
	dht11struct.GPIO_Mode = GPIO_Mode_OUT;
	dht11struct.GPIO_Pin = GPIO_Pin_3;
	dht11struct.GPIO_OType = GPIO_OType_OD;
	dht11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	//初始化PA3
	GPIO_Init(GPIOA,&dht11struct);
}

//输出模式
void DHT11_OUTMode()
{
	//配置引脚 PA3
	GPIO_InitTypeDef dht11struct;
	dht11struct.GPIO_Mode = GPIO_Mode_OUT;
	dht11struct.GPIO_Pin = GPIO_Pin_3;
	dht11struct.GPIO_OType = GPIO_OType_OD;
	dht11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//初始化PA3
	GPIO_Init(GPIOA,&dht11struct);
}

//输入模式
void DHT11_INMode()
{
	//配置引脚 PA3
	GPIO_InitTypeDef dht11struct;
	dht11struct.GPIO_Mode = GPIO_Mode_IN;
	dht11struct.GPIO_Pin = GPIO_Pin_3;
	dht11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//初始化PA3
	GPIO_Init(GPIOA,&dht11struct);
}

//DHT11读取字节
unsigned char DHT11_ReadBytes()
{
	unsigned char retByte;
	for(int i = 0; i < 8;i++)
	{
		retByte = retByte << 1;
		
		//等待上一个高电平结束
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
		//等待上一个低电平结束
		while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
		
		//判断是不是高电平
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))
		{
			//延迟30us
			delay_us(30);
		}
		//判断30us之后还是不是高电平
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))
		{
			//如果是，传过来的数据逻辑为1
			retByte |= 0x01;
		}
		else
		{
			//如果不是，传过来的数据逻辑为0
			retByte &= 0xfe;
		}
	}
	//返回数据
	return retByte;
}

//DHT11 读数据
char DHT11_Readdata(char *humiz,char *humix,char *tempz,char *tempx)
{
	
	tempvalue = 0;
	//设置为输出模式
	DHT11_OUTMode();
	//输出低电平20ms + 高电平30us
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	delay_ms(20);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	delay_us(30);

	//设置DHT11为输入模式
	//发送一个低高电平作为回应
	//DHT11_INMode();
	
	//处理空闲时间 ,等待上拉电阻结束
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
	
		
	//向主机输入一个 低电平（45us） + 高电平（45us）
	while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
//	{
//		delay_us(1);
//		tempvalue++;
//		if(tempvalue > 100)
//		{
//			return 1;
//		}	
//	}
	tempvalue = 0;	
	//等待高电平结束
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
//	{
//		//防止程序在这里打转
//		delay_us(1);
//		tempvalue++;
//		if(tempvalue > 100)
//		{
//			return 1;
//		}
//	}
		//printf("125\r\n");
	//开始接收数据
	for(int i = 0; i < 5;i++)
	{
		//printf("130\r\n");
		readBuff[i] = DHT11_ReadBytes();
	}
	//数据读取完之后，把DHT11改回输出模式
	DHT11_OUTMode();
	if(readBuff[4] == readBuff[0] + readBuff[1] + readBuff[2] + readBuff[3])
	{
		*humiz = readBuff[0];
		*humix = readBuff[1];
		*tempz = readBuff[2];
		*tempx = readBuff[3];
		return 0;
	}
	else
	{
		return 1;
	}
}
















