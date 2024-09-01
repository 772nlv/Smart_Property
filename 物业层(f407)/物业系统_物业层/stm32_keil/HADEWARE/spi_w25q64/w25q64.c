#include "user.h"

//常用指令数值
#define W25X_ManufactDeviceID    0x90 
//擦除片选命令
#define W25X_ChipErase           0x60   //或者h都可以
//读状态寄存器
#define W25X_ReadStatusReg       0x05
//读数据
#define W25X_ReadData            0x03
//写使能
#define W25X_WriteEnable         0x06
//写非使能
#define W25X_WriteDisable        0x04 
//页编程 就是写数据
#define W25X_PageProgram         0x02
//块擦除
#define W25X_BlockErase          0xD8 
//扇区擦除  
#define W25X_SectorErase         0x20
//空
#define W25X_NULL                0x00

//1、设备初始化函数
void W25Q64_Config()
{
	//1、SPI初始化
	SPI_Config();
	
	//2、屏蔽lora PE1：低电平选中 给高电平
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
    GPIO_InitTypeDef loratruct;
    //引脚号码
    loratruct.GPIO_Pin = GPIO_Pin_1;
    //输出模式
    loratruct.GPIO_Mode = GPIO_Mode_OUT;
    //推挽输出
    loratruct.GPIO_OType = GPIO_OType_PP;
	//上拉电阻
	loratruct.GPIO_PuPd = GPIO_PuPd_UP;
	//传输速度
    GPIO_Init(GPIOE,&loratruct);
	GPIO_SetBits(GPIOE,GPIO_Pin_1);

	//初始化本设备的片选引脚
	GPIO_InitTypeDef w25qtruct;
    //引脚号码
    w25qtruct.GPIO_Pin = GPIO_Pin_2;
    //输出模式
    w25qtruct.GPIO_Mode = GPIO_Mode_OUT;
    //推挽输出
    w25qtruct.GPIO_OType = GPIO_OType_PP;
	//上拉电阻
	w25qtruct.GPIO_PuPd = GPIO_PuPd_UP;
	//传输速度
	w25qtruct.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_Init(GPIOB,&w25qtruct);
	//片选信号给高电平，暂时不选中
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
}
//读取设备ID函数
unsigned short W25Q64_ReadID()
{
	//1、准备变量
	unsigned short id = 0;
	//2、片选
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//开始写——发四个字节
	SPI1_Write_Read(W25X_ManufactDeviceID);
	SPI1_Write_Read(W25X_NULL);
	SPI1_Write_Read(W25X_NULL);
	SPI1_Write_Read(W25X_NULL);
	//开始读 —— 2个字节
	id |= SPI1_Write_Read(W25X_NULL);
	id = id << 8;
	id |= SPI1_Write_Read(W25X_NULL);
	
	//取消片选
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	//返回读到的结果
	return id;
		
}
//写数据使能函数
void W25Q64_Write_Enable()
{
	
	//片选
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//发送命令
	SPI1_Write_Read(W25X_WriteEnable);
	//取消片选
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
}

//如果芯片忙碌，就等待
//如果不忙碌，就立即返回0
//检查芯片是否忙碌函数
unsigned char W25Q64_Check_Busy()
{
	unsigned char stat = 0; 
	do{
		//片选
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//发送命令——读相关寄存器，获取状态
	//写 发送命令
	SPI1_Write_Read(W25X_ReadStatusReg);	
	//读
	stat = SPI1_Write_Read(W25X_NULL);
	//取消片选
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	}while(stat & 0x01);
	return 0;

}
//全部都是 1 ffff
//擦除整个芯片函数 耗时很长
void W25Q64_Erase_All_Chip()
{
	W25Q64_Write_Enable();
	W25Q64_Check_Busy();
	//片选
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//发送擦除芯片的命令
	SPI1_Write_Read(W25X_ChipErase);
	//取消片选
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	//判断芯片是否忙完
	W25Q64_Check_Busy();
	

}
//写设备函数——写某个位置
//每次最多256字节
unsigned int W25Q64_Read_Data(unsigned int wordaddr,unsigned char buff[],unsigned char len)
{
	//1、片选
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	
	//2、发送读数据的命令给芯片
	SPI1_Write_Read(W25X_ReadData);
	
	//3、读数据
	//把要读数据的地址发送给芯片 地址是24位 从高往低发三次
	SPI1_Write_Read((wordaddr >> 16) & 0xff);
	SPI1_Write_Read((wordaddr >> 8) & 0xff);
	SPI1_Write_Read((wordaddr >> 0) & 0xff);
	
	//读数据
	int i = 0;
	for(i = 0; i < len ;i++)
	{
		buff[i] = SPI1_Write_Read(W25X_NULL);
	}
	//4、取消片选
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	
	//5、返回读到的数据字节个数
	return i;
}

//一次写一页 256字节
//读设备某个位置的数据函数
int W25Q64_Write_Data(unsigned int writeaddr,char *pbuff,unsigned short byteNum)
{
	//2、写使能
	W25Q64_Write_Enable();
	//1、片选
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	
	//3、发送命令
	SPI1_Write_Read(W25X_PageProgram);
	
	//4、把地址发过去
	//把要读数据的地址发送给芯片 地址是24位 从高往低发三次
	SPI1_Write_Read((writeaddr >> 16) & 0xff);
	SPI1_Write_Read((writeaddr >> 8) & 0xff);
	SPI1_Write_Read((writeaddr >> 0) & 0xff);
	
	//5、循环写数据
	int i = 0;
	for(i = 0;i < byteNum;i++)
	{
		SPI1_Write_Read(pbuff[i]);
	}
	
	//7、取消片选
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	//6、检查是否忙碌
	W25Q64_Check_Busy();
	return i;
}































