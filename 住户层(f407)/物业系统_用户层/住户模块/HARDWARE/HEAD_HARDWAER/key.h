#ifndef __KEY_H
#define __KEY_H


#define key1   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define key2   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)
#define key3   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)
#define key4   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)
//按键1-4初始化-扫描函数
void Key_Config(void);
void KEY_4_Config(void);
unsigned char  scanfkey(void);


#endif

