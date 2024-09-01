#ifndef __DHT11_H
#define __DHT11_H


//DHT11 输出输入数据函数
void DHT11_INMode(void);
void DHT11_OUTMode(void);

//DHT11初始化-读字节-读数据-函数
void DHT11_Config(void);
unsigned char DHT11_ReadBytes(void);
unsigned char DHT11_ReadData(char *humiz,char*humix,char *wtempz,char *wtempx);
#endif


