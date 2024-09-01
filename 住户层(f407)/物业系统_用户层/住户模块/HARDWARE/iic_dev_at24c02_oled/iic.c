#include "user.h"
//PB6 :SCL PB7:SDA
//输入模式
void IIC_INMODE()
{
	GPIO_InitTypeDef iicstruct;
	iicstruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOB,&iicstruct);
}
//输出模式
void IIC_OUTMODE()
{
	GPIO_InitTypeDef iicstruct;
	iicstruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOB,&iicstruct);
}

//1 初始化函数
void IIC_Config()
{
	//时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//引脚
	GPIO_InitTypeDef iicstruct;
	iicstruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	iicstruct.GPIO_Mode = GPIO_Mode_OUT;
	iicstruct.GPIO_OType = GPIO_OType_OD;
	//外部有上拉电阻
	iicstruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	iicstruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOB,&iicstruct);
	//初始化
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
}


//2 起始信号函数
void IIC_Start()
{	
	//1 时钟信号为高不变 + 数据线是从高到低
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	//2.数据有效性：时钟线为低电平的时候 不采集数据线上的数据，因此数据可以改变
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
}


//3 终止信号函数
void IIC_Stop()
{
	//
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	//时钟线拉高
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	delay_us(2);
	//数据线拉高
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(2);
	//终止信号结束以后两条线都是高 空闲
}


//4发送一个字节函数
//把要发送的数据按位进行传输 一次传输一个字节 按位传输
void IIC_Send_Byte_Data(unsigned char data)
{	
	unsigned char i =0;
	for(i =0;i<8;i++)
	{	
			//先传递高位 MSB LSB
			//先传一位
			GPIO_ResetBits(GPIOB,GPIO_Pin_6);
			delay_us(1);
			if((data>>(7-i)) & 0x01)
			GPIO_SetBits(GPIOB,GPIO_Pin_7);
			else
			GPIO_ResetBits(GPIOB,GPIO_Pin_7);
			delay_us(2);
			GPIO_SetBits(GPIOB,GPIO_Pin_6);
			delay_us(4);
			//		data & 0x01; 得到最低位的数据并发送
			//循环八次
	}
	//本函数结束的时候 时钟线为低电平 数据线上的数据  对面不会读取
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(2);
}


//5读取一个字节函数
//对面发送数据也是先发高位，所以是先接收高位数据，接收后按位置左移数据
unsigned char IIC_Get_Byte_Data()
{	
	
	//用来存储对面发送过来的数据
	unsigned char data =0;
	unsigned char i = 0;
	for(i =0;i<8;i++)
	{		
			//先移动位置
			data <<= 1;
			//时钟线为低电平 数据线上的数据可以变化
			GPIO_ResetBits(GPIOB,GPIO_Pin_6);
			delay_us(1);
			//拉高数据线
			GPIO_SetBits(GPIOB,GPIO_Pin_7);
			delay_us(1);
			//时钟线拉高
			GPIO_SetBits(GPIOB,GPIO_Pin_6);
			delay_us(1);

			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
					data |= 0x01;
			else
					data &= 0xfe;

			GPIO_ResetBits(GPIOB,GPIO_Pin_6);
			delay_us(4);
	}
	return data;
}


//6获取有效位（获取ack信号）函数 
//读取到对面发送的低电平为0  则说明8bit数据传输成功
unsigned char IIC_Get_ACK()
{	
	//显示设置时钟线为低电平
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
	//提前拉高数据线
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	delay_us(1);
	//拉高时钟线，时钟线为高电平的时候才读取数据
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	delay_us(1);
	//读到低电平才成功，对面发来的是高电平或者是上拉电阻拉高的，都是失败的
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7))
		return 1;
	else
	{	//函数结束的时候 设置时钟线为低
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		delay_us(1);
		return 0;
	}
	//数据线为低电平时读到0

}


//7 发送NACK信号函数 1

void IIC_Send_ACK(unsigned char ack)
{
		//时钟线拉低
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		delay_us(1);
	//发送数据
		if(ack == NACK)
			GPIO_SetBits(GPIOB,GPIO_Pin_7);
		else
			GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		//时钟线为高电平 对面会读数据
		GPIO_SetBits(GPIOB,GPIO_Pin_6);
		delay_us(4);
		//函数结束的时候 设置时钟线为低
		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		delay_us(1);
}
void iic_outputmode()
{
		GPIO_InitTypeDef iicstruct;
		iicstruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		//输出模式
		iicstruct.GPIO_Mode = GPIO_Mode_OUT;
		//推挽输出
		iicstruct.GPIO_OType = GPIO_OType_PP;
		//低速输出
		iicstruct.GPIO_Speed = GPIO_Speed_100MHz;
		iicstruct.GPIO_PuPd = GPIO_PuPd_UP;
		//引脚初始化。
		GPIO_Init(GPIOB,&iicstruct);
}
