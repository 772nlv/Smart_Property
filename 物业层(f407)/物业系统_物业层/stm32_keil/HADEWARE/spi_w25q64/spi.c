#include "user.h"



//PB2 Cs  -->设备层文件配置
//PB3 CLK  PB4 MISO PB5 MOSI ——>协议层

//在设备层 屏蔽Lora的 SPi信号片选信号


//SPI初始化函数
void SPI_Config()
{
	//1、配置时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	//2、配置引脚
	GPIO_InitTypeDef spistruct;
	spistruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_5;
	//复用模式 
	spistruct.GPIO_Mode = GPIO_Mode_AF;
	//推挽模式
//	spistruct.GPIO_OType = GPIO_OType_PP;
	//上拉电阻
	spistruct.GPIO_PuPd = GPIO_PuPd_UP;
	//响应速度————快速
	spistruct.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_Init(GPIOB,&spistruct);
	
	//3.复用配置——GPIO复用成SPI
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1);
	
	
	//4.SPI电路初始化
	SPI_InitTypeDef SPI1struct;
	//全双工
	SPI1struct.SPI_Direction  = SPI_Direction_2Lines_FullDuplex;
	//主机模式
	SPI1struct.SPI_Mode = SPI_Mode_Master;
	//数据位的大小
	SPI1struct.SPI_DataSize = SPI_DataSize_8b;
	//时钟极性
	SPI1struct.SPI_CPOL = SPI_CPOL_Low;
	//时钟相位
	SPI1struct.SPI_CPHA = SPI_CPHA_1Edge;
	//传输位选择
	SPI1struct.SPI_FirstBit = SPI_FirstBit_MSB;
	//软件片选
	SPI1struct.SPI_NSS = SPI_NSS_Soft;
	//波特率选择——预分频系数 为2
	SPI1struct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	//校验数值——默认为7
	SPI1struct.SPI_CRCPolynomial = 7;
	
	SPI_Init(SPI1,&SPI1struct);
	
	//5.SPI电路使能
	SPI_Cmd(SPI1,ENABLE);
	
}


//返回值是读到的数据
//参数是发送的数据
//SPI读写函数
unsigned char SPI1_Write_Read(unsigned char senddata)
{
	//发送数据，关注标志位，发送完上一个数据之后 变成1
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET){}
		SPI_I2S_SendData(SPI1,senddata);
	
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET){}
		return SPI_I2S_ReceiveData(SPI1);
}

































