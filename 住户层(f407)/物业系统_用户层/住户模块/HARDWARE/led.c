#include "user.h" 
//初始化PF9和PF10为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{    	 
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);	//使能GPIOF时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_10|GPIO_Pin_9;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);					//初始化GPIO
	GPIO_SetBits(GPIOE,GPIO_Pin_8|GPIO_Pin_9 | GPIO_Pin_10);			
}
void LED_TurnOn(unsigned int LEDNUM)
{
		 switch(LEDNUM)
		 {
			 case 1:GPIO_ResetBits(GPIOE,GPIO_Pin_8); break;
			 case 2:GPIO_ResetBits(GPIOE,GPIO_Pin_9); break;
			 case 3:GPIO_ResetBits(GPIOE,GPIO_Pin_10); break;
			 default:break;
		 }
}
//3.关闭led函数

void LED_TurnOff(unsigned int LEDNUM)
{
	 switch(LEDNUM)
		 {
			 case 1:GPIO_SetBits(GPIOE,GPIO_Pin_8); break;
			 case 2:GPIO_SetBits(GPIOE,GPIO_Pin_9); break;
			 case 3:GPIO_SetBits(GPIOE,GPIO_Pin_10); break;
			 default:break;
		 }

}





