#ifndef __IIC_H
#define __IIC_H

#define NACK 1
#define ACK 0

//输入输出模式
void IIC_INMODE(void);
void IIC_OUTMODE(void);
void iic_outputmode(void);
//初始化函数-起始信号-终止信号函数
void IIC_Config(void);
void IIC_Start(void);
void IIC_Stop(void);
//发送一个字节函数--读取一个字节函数
void IIC_Send_Byte_Data(unsigned char data);
unsigned char IIC_Get_Byte_Data(void);
//获取ACK信号函数
unsigned char IIC_Get_ACK(void);
//发送NACK信号函数
void IIC_Send_ACK(unsigned char ack);


#endif



