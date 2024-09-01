#include "user.h"
//设备层
//1.读取设备id函数
//2.擦除整个芯片函数
//3.读数据：那个字节   放在哪  读多长  返回值：读了多少个字节
//ok
//4.写数据：向那里写  写什么  ，写多长  返回：实际写了多长
//一个读数据函数 一个写数据函数
//linux api  51 stm32 qt 
//读数据和写数据都是这个函数
unsigned char SPI1_write_read(unsigned char data);
//id数组
unsigned char idnum[2] = "" ;
unsigned char sbuff[128] = "" ;
unsigned char sbuff1[128] = "" ;
unsigned char dundun = 0 ;
//常用命令
//设备id
#define W25X_ManufactDeviceID	0x90 

//擦除片选命令
#define W25X_ChipErase			0x60   //或者h都可以
//读状态寄存器
#define W25X_ReadStatusReg		0x05
//读数据
#define W25X_ReadData			0x03
//写使能
#define W25X_WriteEnable		0x06
//写非使能
#define W25X_WriteDisable		0x04 
//页编程 就是写数据
#define W25X_PageProgram		0x02
//块擦除
#define W25X_BlockErase			0xD8 
//扇区擦除  
#define W25X_SectorErase		0x20
//第二层函数
//w25q126；写函数留给大家去做，模仿例题程序

//1初始化函数
void w25q128_init()
{
		//PE1设置高电平  lora 屏蔽掉
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
		GPIO_InitTypeDef GPIOEstruct;
		GPIOEstruct.GPIO_Pin = GPIO_Pin_1;
		GPIOEstruct.GPIO_Speed = GPIO_Speed_2MHz;
		GPIOEstruct.GPIO_PuPd = GPIO_PuPd_UP ;
		GPIOEstruct.GPIO_Mode = GPIO_Mode_OUT;
		GPIOEstruct.GPIO_OType = GPIO_OType_PP;
		GPIO_Init(GPIOE,&GPIOEstruct);
	
		//不选中  //lora要片选拉高。刷卡都不选中
		GPIO_SetBits(GPIOE,GPIO_Pin_1);
	
		//1.spi初始化  //
		SPI1_Config();
		//2.片选中flash  时钟也要初始化配置
		GPIO_InitTypeDef GPIOstruct;
		//填写引脚
		GPIOstruct.GPIO_Pin = GPIO_Pin_2;
		//填写速度
		GPIOstruct.GPIO_Speed = GPIO_Speed_50MHz;
		//填写电阻
		GPIOstruct.GPIO_PuPd = GPIO_PuPd_UP ;
		//填写模式
		GPIOstruct.GPIO_Mode = GPIO_Mode_OUT;
		//即可以输出高电平也可以输出低电平
		GPIOstruct.GPIO_OType = GPIO_OType_PP;
		GPIO_Init(GPIOB,&GPIOstruct);
		//3片选是低电平有效  不用片选 给出高电平
		GPIO_SetBits(GPIOB,GPIO_Pin_2);
}

 

//读写数据函数  

//读取设备id函数  
//16位
//0xef16；是它的芯片id；

//思路：片选 - 写数据(发送命令) - 读数据 - 结束片选

//2.读设备数据函数
uint16_t W25Q_read_id(unsigned char *num1,unsigned char *num2)
{
		uint16_t id = 0 ;
		//1.片选：软件片选
	
		GPIO_ResetBits(GPIOB,GPIO_Pin_2);
		//2.发送命令，设备id
		//90是命令，要求发送四个字节过去  32位  返回2个字节 
		//发送函数和读数据函数都是它
	
		SPI1_write_read(0x90);
		SPI1_write_read(0x00);
		SPI1_write_read(0x00);
		SPI1_write_read(0x00);
	
		//读数据，读到的结果是高八位，先读出高八位
		//返回值是结果，高八位
		id |= SPI1_write_read(0x00);  
		//左移一下
		id = id << 8 ;
		//然后再或上后面的低八位  读两次返回2个字节
		id |=  SPI1_write_read(0x00);
		//3.取消片选
		GPIO_SetBits(GPIOB,GPIO_Pin_2);
		return id;
}

//3写使能函数
//给芯片发送指令。
void write_enable()
{
			//1.片选
			GPIO_ResetBits(GPIOB,GPIO_Pin_2);
			//2.发送命令
			SPI1_write_read(W25X_WriteEnable);
			//3.关闭片选
			GPIO_SetBits(GPIOB,GPIO_Pin_2);
}

//4检查芯片是否在忙碌中函数
//因为擦除是需要时间的
//等待空闲函数
unsigned char w25q128_check_busy()
{
			unsigned char stat = 0 ;
			//片选  
			GPIO_ResetBits(GPIOB,GPIO_Pin_2);
			//发送数据  写数据
			SPI1_write_read(W25X_ReadStatusReg);
			//循环等待 : 先执行动作，再循环等待
			do{
				
			//发送命令  读数据  寄存器不忙 值就是0；
			stat = SPI1_write_read(0x00);
			
				
			}while(stat & 1);
			//取消片选  
			GPIO_SetBits(GPIOB,GPIO_Pin_2);
			return 0;
}
//5读寄存器函数
//片选- 发送命令读取寄存器 -  读取寄存器的值 - 返回这个值  
u8 w25q_readregister()
{
			u8 data = 0;
			//片选
			GPIO_ResetBits(GPIOB,GPIO_Pin_2); 
			//发送命令
			SPI1_write_read(W25X_ReadStatusReg);
			//读取寄存器的状态值
			data = SPI1_write_read(0xff);
			//取消片选
			GPIO_SetBits(GPIOB,GPIO_Pin_2);
			return data ;
}

//6等待空闲函数
void w25q_wait_busy()
{ 
			while((w25q_readregister()&0x01)==0x01);   // 等待BUSY位清空
}
//擦除流程：
	//	1.写使能函数
	//	2.等待空闲函数
	//	3.片选
	//	4.发送擦除命令
	//	5.等待空闲函数

//7读状态寄存器函数： 1片选 -2发送读状态寄存器命令 -3读取最后一个字节- 4关闭片选
//擦除整个芯片		  
//等待时间超长...
void W25QXX_Erase_Chip()   
{          
		//写使能函数
    write_enable();              //SET WEL 
		//忙等待函数
    w25q_wait_busy();  
		//片选-发送命令-取消片选
  	GPIO_ResetBits(GPIOB,GPIO_Pin_2);    
    SPI1_write_read(W25X_ChipErase);  
		GPIO_SetBits(GPIOB,GPIO_Pin_2);  
		//等待芯片擦除结束
		w25q_wait_busy();  			   
} 

//8擦除整个芯片函数
//擦除和写的时候会busy
unsigned char w25q128_eraser_chip_all()
{		
		write_enable();
		w25q128_check_busy();
		//1.片选
		GPIO_ResetBits(GPIOB,GPIO_Pin_2);
		//2.发送命令  从指令表中选出命令
		SPI1_write_read(W25X_ChipErase);
		//当最后字节的第八位进入芯片后，cs必须拉高，如果cs没有拉高，那么芯片擦写指令不会被执行
		//3.取消片选
		GPIO_SetBits(GPIOB,GPIO_Pin_2);
		//4.等待擦除结束  擦除是需要时间的
		w25q128_check_busy();
			
		return 0 ;
}

//9.读出数据函数
//读数据成功了，但是擦除并没有成功
//地址 + 空间 + 长度。
unsigned int w25q128_read_data(uint32_t addr,uint8_t *sbuff,uint8_t len)
{			
			w25q128_check_busy();
			//1.片选
			GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	
			//2.发送读数据指令
			SPI1_write_read(W25X_ReadData);
			//后面跟着的是地址  //取出大小部分。
			SPI1_write_read((addr >> 16) & 0xff); 
			SPI1_write_read((addr >> 8) & 0xff);
			SPI1_write_read((addr) & 0xff);
	
			//3.读出数据
			uint8_t i = 0 ;
			for(i = 0 ; i < len ; i++)
			{
					//读也用这个函数来做。
					sbuff[i] = SPI1_write_read(0);
				
			}
			//4.取消片选
			GPIO_SetBits(GPIOB,GPIO_Pin_2);
			//等待结束。
			//w25q128_check_busy();// 读取操作完成后Flash会自动变为非忙状态。
			//返回实际读到的字节数
			return i ;
}
//10.写设备函数 写到某个位置
//一次写一页 256个字节

void w25q128_write_page(unsigned char *pbuff,unsigned char writeaddr,unsigned short int numbytes)
{	
	
	write_enable();
	//1片选
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	//2.写使能

	//3.发送命令
	SPI1_write_read(W25X_PageProgram);
	//4往哪里写，把地址发过去 循环写数据
	SPI1_write_read((u8)(writeaddr)>>16);
	SPI1_write_read((u8)(writeaddr)>>8);
	SPI1_write_read((u8)writeaddr);
	//5.循环写数据
	int i =0;
	for(i = 0;i<numbytes;i++)
	SPI1_write_read(pbuff[i]);
	
	
	//6.取消片选
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	//7.检查是否忙碌	
	w25q128_check_busy();
	
}

