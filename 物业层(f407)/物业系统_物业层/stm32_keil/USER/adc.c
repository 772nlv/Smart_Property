#include "user.h"


//光敏电阻 


//配置ADC电路——光敏电阻----电位
void ADC1_Light_Config()
{
	//1、时钟问题
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	//2、GPIOA的0号配置模拟模式
	GPIO_InitTypeDef gpioastruct;
	gpioastruct.GPIO_Pin = GPIO_Pin_0;
	gpioastruct.GPIO_Mode = GPIO_Mode_AN;
	gpioastruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&gpioastruct);
	//GPIOC的0号配置模拟模式
	GPIO_InitTypeDef gpiocstruct;
	gpiocstruct.GPIO_Pin = GPIO_Pin_0;
	gpiocstruct.GPIO_Mode = GPIO_Mode_AN;
	gpiocstruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC,&gpiocstruct);

	//3、ADC电路配置
	ADC_CommonInitTypeDef adcstruct;
	//关闭DMA电路
	adcstruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	//独立模式
	adcstruct.ADC_Mode = ADC_Mode_Independent;
	//分频
	adcstruct.ADC_Prescaler = ADC_Prescaler_Div4;
	//两次采集数据的时间间隔
	adcstruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	//初始化
	ADC_CommonInit(&adcstruct);
	
	//4、光敏电阻配置
	ADC_InitTypeDef lightstruct;
	//位精度
	lightstruct.ADC_Resolution = ADC_Resolution_12b;
	//不要扫描——单次即可
	lightstruct.ADC_ScanConvMode = DISABLE;
	//转换一次就停止
	lightstruct.ADC_ContinuousConvMode = DISABLE;
	//采集数据右对齐
	lightstruct.ADC_DataAlign = ADC_DataAlign_Right;
	//触发方式
	lightstruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	//只转换一个规则序列组
	lightstruct.ADC_NbrOfConversion = 1;
	//初始化
	ADC_Init(ADC1,&lightstruct);
	
	//ADC电路使能
	ADC_Cmd(ADC1,ENABLE);
}

//采集信息
//通道数值
//开始采集的函数
unsigned short Get_ADC_Channel(unsigned int channel)
{
	//ADC开始采集函数
	//adc电路 通道 一个序列 采样时间
	ADC_RegularChannelConfig(ADC1,channel,1,ADC_SampleTime_480Cycles);
	
	//开始采集！软件开始控制
	ADC_SoftwareStartConv(ADC1);
	//等待采集结束  理论部分在程序中都有体现 程序中会证明理论的存在。
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));

	//获取的结果进行返回
	return ADC_GetConversionValue(ADC1);
}


//均值操作
//通道数 + 采集次数
unsigned short Get_ADC_Average(unsigned int channel,char times)
{
	unsigned short value = 0;
	int i = 0;
	for(i = 0; i < times ;i++)
	{
		value += Get_ADC_Channel(channel);
		delay_ms(5);
	}
	
	return value/times;
}































