#include "user.h"

//写，低位是0
//读，低位是1
#define WRITE_AT24C02_ADDR 0xa0;
#define READ_AT24C02_ADDR 0xa1;
//设备相关函数
//设备初始化
//返回0代表设备没问题
//返回1代表设备故障
int  AT24c02init()
{
        IIC_Config();
        IIC_Start();
        //发送设备地址，写入数据                  
        IIC_Send_Byte_Data(0xa0);
        if(IIC_Get_ACK())
        {        
            IIC_Stop();
            return 1;
        }
        return 0 ;
}


//向at24c02设备的某个地址写入数据
//设备地址-字节地址-内容
unsigned char at24c02_write_byte(unsigned char word_addr,unsigned char dat)
{
        //1.起始信号
        IIC_Start();
        
        //2.发送设备地址
        IIC_Send_Byte_Data(0xa0);
        //3.等待应答信号
        if(IIC_Get_ACK())
        {
                IIC_Stop();
                return 1 ;//通过返回值判断函数的执行情况 返回1失败
        }
        //4.发送自己地址
        IIC_Send_Byte_Data(word_addr);
        //5.等待应答信号
        if(IIC_Get_ACK())
        {
                IIC_Stop();
                return 1 ;
        }
        //6.发送数据内容
        IIC_Send_Byte_Data(dat);
        if(IIC_Get_ACK())             //如果没有应答，直接退出，没有应答返回1，有应答返回0.
        {
                   IIC_Stop();
                    return 1 ;                
        }
         IIC_Stop();
        return 0 ; //写成功返回0；
        //8.结束信号。
}


//把数据存进去再读出来。
//存储一串字符串，再读出来。
//任意位置读内容
//从某个设备 某个地址 读出数据
//随机读一个字节，很重要。
//指定从哪个地址开始读。
//从某个地址读数据，实际上就是把地址发送过去，然后再读。
//满足时序要求即可。
unsigned char AT24c02_read_bytes(unsigned char word_addr)
{
        unsigned char buff = 0 ;
        //1发送起始信号
        IIC_Start();
        //2发送设备地址 写低电平
        IIC_Send_Byte_Data(0xa0);
        //3等待应答信号
        if(IIC_Get_ACK())             //如果没有应答，直接退出，没有应答返回1，有应答返回0.
        {
                  IIC_Stop();
                return 1 ;
        }
        //4发送字节地址
        IIC_Send_Byte_Data(word_addr);
        //5等待应答信号
        if(IIC_Get_ACK())             //如果没有应答，直接退出，没有应答返回1，有应答返回0.
        {
                IIC_Stop();
                return 1 ;
        }
        //6再次发送起始信号
        IIC_Start();
        //7发送设备地址 读操作高电平
        IIC_Send_Byte_Data(0XA1);
        //8等待应答信号
        if(IIC_Get_ACK())             
        {
                IIC_Stop();
                return 1 ;
        }
        //9读取具体数据
        buff = IIC_Get_Byte_Data();
        //10发送非应答信号
        IIC_Send_ACK(NACK);
        //11结束信号
        IIC_Stop();       
        return buff ;

}

