#include "user.h"

//协议层 
//PB2 CS  设备层文件先不写
//PB3 CLK PB4 MISO PB5 MOSI  协议层文件配置
//1spi初始化函数
//在设备层 屏蔽掉 lora 的spi片选信号
void SPI1_Config()
{
	//时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	//配置引脚
	GPIO_InitTypeDef spistruct;
	spistruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	spistruct.GPIO_Mode = GPIO_Mode_AF;
	spistruct.GPIO_PuPd = GPIO_PuPd_UP;
	spistruct.GPIO_OType = GPIO_OType_PP;
	spistruct.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_Init(GPIOB,&spistruct); 
	//3.复用GPIO引脚为spi接口
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1);
	//4.SPI电路初始化
	SPI_InitTypeDef NSPISRTUCT;
	//全双工
	NSPISRTUCT.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	//主机模式
	NSPISRTUCT.SPI_Mode = SPI_Mode_Master;
	//数据位的大小 8位
	NSPISRTUCT.SPI_DataSize = SPI_DataSize_8b;
	//时钟极性
	NSPISRTUCT.SPI_CPOL = SPI_CPOL_Low;
	//时钟相位
	NSPISRTUCT.SPI_CPHA = SPI_CPHA_1Edge;
	//传输位选择
	NSPISRTUCT.SPI_FirstBit = SPI_FirstBit_MSB;
	//硬件片选 软件片选
	NSPISRTUCT.SPI_NSS = SPI_NSS_Soft;
	//预分频系数
	NSPISRTUCT.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	//校验数值
	NSPISRTUCT.SPI_CRCPolynomial = 7;
	//spi电路使能
	SPI_Init(SPI1,&NSPISRTUCT);
	
	//SPI电路使能
	SPI_Cmd(SPI1,ENABLE);
}
//2spi读写函数
unsigned char SPI1_write_read(unsigned char data)
{
		//发送数据 关注一个标志位 发送完后 会变成1
		while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)==RESET);
			SPI_I2S_SendData(SPI1,data);
		//接受数据关注一个标注位  接受完后 会变成1
		while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)==RESET);
			return SPI_I2S_ReceiveData(SPI1);
}


