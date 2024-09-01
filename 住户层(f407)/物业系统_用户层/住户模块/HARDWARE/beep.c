#include "user.h"

//驼峰命名法，模块+功能，单词之间用下划线
//1.beep 模块配置函数

void BEEP_Config()
{
	
//1.配置时钟 - PB -GPIOB-10
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
//2.配置接口
		GPIO_InitTypeDef beepstruct;

	//引脚号码
	beepstruct.GPIO_Pin = 	GPIO_Pin_10;
	//输出模式
	beepstruct.GPIO_Mode = GPIO_Mode_OUT;
	//推挽输出
	beepstruct.GPIO_OType = GPIO_OType_PP;
	//上拉电阻
	beepstruct.GPIO_PuPd = GPIO_PuPd_UP;
	//响应速度
	beepstruct.GPIO_Speed = GPIO_Low_Speed;
	//初始化端口函数
	GPIO_Init(GPIOB,&beepstruct);
	
	
//3.初始化引脚-给PB10低电平(无声状态)-高电平驱动

GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_RESET);

}
//打开蜂鸣器-
void Beep_Open()
{
GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_SET);	
	
}
void Beep_Close()
{
GPIO_WriteBit(GPIOB,GPIO_Pin_10,Bit_RESET);	
	
}
void Beep_Alarm()
{	
		int num = 6;
		while(num--)
		{
    GPIO_ToggleBits(GPIOB,GPIO_Pin_10);//高
    delay_ms(200);
		}
}
