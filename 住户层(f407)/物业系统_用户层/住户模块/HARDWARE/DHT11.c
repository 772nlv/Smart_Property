#include "user.h"

//1.DHT11配置函数
void DHT11_Config()
{
	//PA3引脚
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef DHT11struct = {0};
	DHT11struct.GPIO_Pin = 	GPIO_Pin_3;
	DHT11struct.GPIO_Mode = GPIO_Mode_OUT;
	//开漏输出
	DHT11struct.GPIO_OType = GPIO_OType_OD;	
	DHT11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&DHT11struct);
	//如果是输出模式的话，主动输出高电平
	//因为起始信号时低加高的组合，所以让他先高电平开始
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
}
//2.DHT11输入模式函数
void DHT11_INMode()
{
	GPIO_InitTypeDef DHT11struct = {0};
	DHT11struct.GPIO_Pin = 	GPIO_Pin_3;
	DHT11struct.GPIO_Mode = GPIO_Mode_IN;
	//开漏输出	
	DHT11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&DHT11struct);

}
//3.DHT11输出模式函数
void DHT11_OUTMode()
{
		GPIO_InitTypeDef DHT11struct = {0};
	DHT11struct.GPIO_Pin = 	GPIO_Pin_3;
	DHT11struct.GPIO_Mode = GPIO_Mode_OUT;
	//开漏输出
	DHT11struct.GPIO_OType = GPIO_OType_OD;	
	DHT11struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB,&DHT11struct);
	//如果是输出模式的话，主动输出高电平
	//因为起始信号时低加高的组合，所以让他先高电平开始
	//GPIO_SetBits(GPIOA,GPIO_Pin_3);
}
//4.DHT11读字节函数
	unsigned char DHT11_ReadBytes()
{
	unsigned char resdata = 0;
	char i = 0 ; 
	for(i = 0 ; i < 8 ; i ++)
	{
		//先移位
		resdata = resdata << 1 ;
		//先读一位
		//等待高电平结束
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
		//等待低电平结束
		while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
		//判断高电平时长
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))
		{
			delay_us(30);
		}
		//30以后 还是高电平  0000 0000 | 0000 0001
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))
				resdata |= 0x01 ;   //最低位增加一个1
		else
				resdata &= 0xfe;   // 最低位 清零 1111 1110
		//后移位
		//resdata = resdata << 1 ;
	}
	//返回数据
	return resdata;
}


//5.DHT11读数据函数
//参数是指针，输出型指针
//返回值0是成功1是失败
char buff[5] = "";
unsigned char DHT11_ReadData(char *humiz,char*humix,char *wtempz,char *wtempx)
{
	//总时序
	//1输出模式 +低20ms +高30us 
	DHT11_OUTMode();
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	delay_ms(20);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	delay_us(20);
	//输入模式 读数据 对面发送 低45us + 高45us 这里的输入模式是指stm32控制器等待接受dht11传来的数据
	DHT11_INMode();
	//等待高电平结束，防止上拉电阻起作用
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
	//可以不要对面的时间长度
	//如果对面发送的是低电平，那么本cpu等待，直到低电平过去
	//while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
	//把45us的高也越过去
	//while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));
	while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));

	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3));

	//低高电平时间循环过去后就到了数据接收阶段
	//湿度整数
	for(int i =0;i<5;i++)
	{
		buff[i] = DHT11_ReadBytes();
	}
	//DHT11_OUTMode();
	//校验和
	if(buff[4] == buff[0]+buff[1]+buff[2]+buff[3])
	{		
		*humiz = buff[0];
		*humix = buff[1];
		*wtempz = buff[2];
		*wtempx = buff[3];
			//返回数据
			return 0;//成功
	}
	else
		return 1;//失败
}


