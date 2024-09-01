#include "user.h"


//IIC接口初始化 SCL: PB6  SDA:PB7
void IIC_Config()
{
//配置时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	//配置引脚 PA3
	GPIO_InitTypeDef IICstruct;
	IICstruct.GPIO_Mode = GPIO_Mode_OUT;
	IICstruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;
	IICstruct.GPIO_OType = GPIO_OType_OD;
	//外部已经有上拉电阻
	IICstruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	IICstruct.GPIO_Speed = GPIO_Low_Speed;
	//初始化PA3
	GPIO_Init(GPIOB,&IICstruct);
}

void IIC_INMODE()
{
	GPIO_InitTypeDef iicstruct;
	iicstruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOB,&iicstruct);
}
void IIC_OUTMODE()
{
	GPIO_InitTypeDef iicstruct;
	iicstruct.GPIO_Mode = GPIO_Mode_OUT;
	iicstruct.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(GPIOB,&iicstruct);
}

//开始信号
void IIC_Start()
{
	//时钟信号为高不变 +  数据线是由高到低
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	
	//数据有效性，时钟线为低电平的时候，数据不采集
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
}

//停止信号
void IIC_Stop()
{
	//结束信号，时钟线在高电平不变的情况下，数据线由低到高
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);	
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(2);
	//SCL 高
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	delay_us(2);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	//空闲状态
//	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
//	delay_us(2);
}

//发送一个字节函数
//把要发送的数据一个个字节传输，串行通信，每次传输一个位
void IIC_Send_Byte(unsigned char data)
{
	unsigned char i = 0 ;
	for(i = 0 ; i < 8 ; i ++)
	{
		//先传递的是高位 MSB LSB
		//先传一位
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		//加上延时
		delay_us(1); 
		
		//  data & 0x01
		if((data >>(7 - i))& 0x01)
			GPIO_SetBits(GPIOB,GPIO_Pin_7);
		else
			GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		GPIO_SetBits(GPIOB,GPIO_Pin_6);
		delay_us(4);
		// data >> 1 & 0x01
	//循环8次
	}	
	//本函数结束的时候  时钟线为低电平 数据线上的数据 对面不会读取
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(2);
}
	
//IIC读取数据
unsigned char IIC_Get_Byte()
{
	IIC_INMODE();
	//输入模式-
	//用来存储对面发送过来的数据
	unsigned char dat = 0 ;
	unsigned char i = 0 ;
	for(i = 0 ; i < 8 ; i++)
	{
		//先移动位置
		dat = dat << 1;
		//时钟线为低电平 数据线上的数据 可以变化
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		delay_us(1);
		GPIO_SetBits(GPIOB,GPIO_Pin_7);
		delay_us(1);
		
		//时钟线拉高
		GPIO_SetBits(GPIOB,GPIO_Pin_6);
		delay_us(1);
		//读对面发送过来的数据
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
			dat |= 0X01;
		else
			dat &= 0xfe;
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		delay_us(4);
	}
	//输出模式
	IIC_OUTMODE();
	//返回数据
	return dat;
}

//获取ACK信号
unsigned char IIC_Get_ACK()
{
	//时钟线低电平
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
	//把数据线提前拉高为高电平
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(1);
	
	//时钟线拉高
	GPIO_SetBits(GPIOB,GPIO_Pin_6);	
	delay_us(1);
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
		return 1;//发送失败
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_6); 
		delay_us(1);
		return 0;
	}
		
}


//发送一个高电平信号；非应答信号
void IIC_SEND_ACK(unsigned char ack)
{
	//SCL低电平
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
	if(ack == NACK)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_7);//SDA高电平，非应答信号
		delay_us(1);
	}
	else
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_7);//SDA低电平，应答信号
		delay_us(1);
	}
	//拉高SCL，数据可读
	GPIO_SetBits(GPIOB,GPIO_Pin_6);	
	delay_us(1);

	//拉低SCL，空闲状态
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(2);
	
}


































