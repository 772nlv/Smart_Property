#ifndef __IIC
#define __IIC

#define ACK 0
#define NACK 1

//IIC模块
void IIC_Config(void);
//开始信号
void IIC_Start(void);
//停止信号
void IIC_Stop(void);
//发送一个字节函数
void IIC_Send_Byte(unsigned char data);
//IIC读取数据
unsigned char IIC_Get_Byte(void);
//获取ACK信号
unsigned char IIC_Get_ACK(void);
//发送一个高电平信号；非应答信号
void IIC_SEND_ACK(unsigned char ack);
//输入模式
void IIC_INMODE(void);
//输出模式
void IIC_OUTMODE(void);


//OLED模块
//1.oled写命令函数
void WriteOLedCmd(uint8_t cmd);
//2 OLED写数据函数
void WriteOLedData(uint8_t data);
//3 oled描点函数
void OLed_Fill(unsigned char bmp_data);
void OLed_SetPos(unsigned char x, unsigned char y);
//5 OLED初始化函数
void InitOLed(void);
//6.显示字母函数
void Oled_print(uint8_t x, uint8_t y,char *str);
//7.显示汉字函数
void OLed_ShowChina(uint8_t x,uint8_t y,uint8_t *buf);
//AT24C02
//设备初始化
//返回0 设备ok
int AT24C02_INIT(void);
unsigned char AT24C02_Write_Bytes(unsigned char wordaddr,unsigned char newdata);//向at24c04设备的 某个地址读数据
unsigned char  AT24C02_Read_Bytes(unsigned char wordaddr);
//AT24c04模块



#endif


