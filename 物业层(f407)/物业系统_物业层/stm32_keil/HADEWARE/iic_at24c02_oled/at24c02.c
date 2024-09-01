

#include "user.h"

//写 低位是 0
//读 低位是 1 
#define WRITE_AT24C02_ADDR 0xa0
#define READ_AT24C02__ADDR 0xa1

//1设备初始化
//返回0 代表本设备ok
//返回1 本设备故障
int AT24C02_INIT()
{
	//检测设备是否存在
	IIC_Config();
	IIC_Start();
	//写数据  0xa0 
	IIC_Send_Byte(WRITE_AT24C02_ADDR);
	if(IIC_Get_ACK())
	{
		//停止协议
		IIC_Stop();
		return 1;
	}
	else
		return 0;
}


//2随机写函数
//向at24c02设备 的某个地址 写数据
//通过返回值判断函数的执行情况
//0:成功
//1:失败
unsigned char AT24C02_Write_Bytes(unsigned char wordaddr,unsigned char newdata)
{
	//1.起始信号
	IIC_Start();
	//2.发送设备地址 
	IIC_Send_Byte(WRITE_AT24C02_ADDR);
	//3.获取ack信号
	if(IIC_Get_ACK())
	{
		//停止协议
		IIC_Stop();
		return 1;
	}

	//4.发送字节地址
	IIC_Send_Byte(wordaddr);
	//5.获取ack信号
	if(IIC_Get_ACK())
	{
		//停止协议
		IIC_Stop();
		return 1;
	}
	
	//6.发送数据本身
	IIC_Send_Byte(newdata);
	//7.获取ack信号
	if(IIC_Get_ACK())
	{
		//停止协议
		IIC_Stop();
		return 1;
	}
	//8.the end 
	IIC_Stop();
	return 0 ;
}


//3随机读函数
//返回的是数据本身
//参数是 字节地址
unsigned char  AT24C02_Read_Bytes(unsigned char wordaddr)
{
	unsigned char ret = 0 ; 
	//1.起始信号
	IIC_Start();
	//2.发送设备地址 写
	IIC_Send_Byte(WRITE_AT24C02_ADDR);
	//3 获取ack
	if(IIC_Get_ACK())
	{
		//停止协议
		IIC_Stop();
		return 1;
	}
	//4.发送字节地址
	IIC_Send_Byte(wordaddr);
	//5.获取ack
	if(IIC_Get_ACK())
	{
		//停止协议
		IIC_Stop();
		return 1;
	}
	//6.起始信号
	IIC_Start();
	//7.发送设备地址 读
	IIC_Send_Byte(READ_AT24C02__ADDR);
	//8.获取ack
	if(IIC_Get_ACK())
	{
		//停止协议
		IIC_Stop();
		return 1;
	}
	//9.读出数据
	ret = IIC_Get_Byte();
	//10.发送nack
	IIC_SEND_ACK(NACK);
	//11.结束
	IIC_Stop();
	return ret;
}

