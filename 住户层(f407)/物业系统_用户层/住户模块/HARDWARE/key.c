#include "user.h"
//按键初始化
void Key_Config()
{
	//1.配置时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	//2.配置接口
	GPIO_InitTypeDef keystruct;
	//引脚号码
	keystruct.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	//输入模式
	keystruct.GPIO_Mode = GPIO_Mode_IN;
	//上拉电阻
	keystruct.GPIO_PuPd = GPIO_PuPd_UP;
	//响应速度
	keystruct.GPIO_Speed = GPIO_Low_Speed;
//3.初始化端口函数
	GPIO_Init(GPIOE,&keystruct);

}
void KEY_4_Config()
{
	//1.配置时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	//2.配置接口
	GPIO_InitTypeDef keystruct;
	//引脚号码
	keystruct.GPIO_Pin = GPIO_Pin_13;
	//输入模式
	keystruct.GPIO_Mode = GPIO_Mode_IN;
	//上拉电阻
	keystruct.GPIO_PuPd = GPIO_PuPd_UP;
	//响应速度
	keystruct.GPIO_Speed = GPIO_Low_Speed;
	//3.初始化端口函数
	GPIO_Init(GPIOC,&keystruct);
}

unsigned char scanfkey()
{
 if(key1==0||key2==0||key3==0||key4==0)
 {
  delay_xms(10);
	if(key1==0) {while(key1==0);delay_xms(10);return 1;}
	else if(key2==0) {while(key2==0);delay_xms(10);return 2;} 
  else if(key3==0) {while(key3==0);delay_xms(10);return 3;}
  else if(key4==0) {while(key4==0);delay_xms(10);return 4;}
 }
 return 0;
}



