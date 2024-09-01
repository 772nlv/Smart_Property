#include "user.h"
//光敏电阻 ADC1 -IN0 -PA0
//1配置ADC电路
void ADC1_GUANG_INO_Config()
{
	//1时钟 APB2 84/4 = 21 <36MHZ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
		GPIO_InitTypeDef Vstruct;
		//引脚号码
	Vstruct.GPIO_Pin = 	GPIO_Pin_0;
	//输出模式
	Vstruct.GPIO_Mode = GPIO_Mode_OUT;
	//推挽输出
	Vstruct.GPIO_OType = GPIO_OType_PP;
	//上拉电阻 但是，请注意，当GPIO引脚被配置为输出模式（GPIO_Mode_OUT）时，
	//内部上拉电阻的作用可能会受到限制或忽略，因为输出模式允许您直接控制引脚的电平状态。
	Vstruct.GPIO_PuPd = GPIO_PuPd_NOPULL;//GPIO_PuPd_NOPULL
	//响应速度
	Vstruct.GPIO_Speed = GPIO_Low_Speed;
	//初始化端口函数
	GPIO_Init(GPIOC,&Vstruct);
	//GPIOA 0号复用功能
	
	GPIO_InitTypeDef gpioastruct;
	gpioastruct.GPIO_Pin = GPIO_Pin_0;
	gpioastruct.GPIO_Mode = GPIO_Mode_AN;
	gpioastruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&gpioastruct);
	//gpio不需要配置引脚复用映射
	//GPIO_PinAFConfig()
	
	//2.adc电路配置
	ADC_CommonInitTypeDef adcstruct;
	//关闭dma电路
	adcstruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	//独立模式
	adcstruct.ADC_Mode = ADC_Mode_Independent;
	//都在函数的初始化值中找到可选数值
	adcstruct.ADC_Prescaler = ADC_Prescaler_Div4;
	//两次采集的时间间隔
	adcstruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&adcstruct);
	
	//3.ADC配置
	ADC_InitTypeDef guangstruct;
	//12位精度
	guangstruct.ADC_Resolution = ADC_Resolution_12b;
	//不要扫描 - 单次即可
	guangstruct.ADC_ScanConvMode = DISABLE;
	//转换一次就停止
	guangstruct.ADC_ContinuousConvMode = DISABLE;
	//右对齐
	guangstruct.ADC_DataAlign = 	ADC_DataAlign_Right;
	//触发方式
	guangstruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	//只转换一个规则序列组
	guangstruct.ADC_NbrOfConversion =1;
	//初始化
	ADC_Init(ADC1,&guangstruct);
	//3.开启adc电路使能
	ADC_Cmd(ADC1,ENABLE);


}


//2.采集信号操作函数
unsigned short int getADC_channel(unsigned int channel)
{
	//ADC开始采集函数
	//adc电路通道 一个序列的采样时间
	ADC_RegularChannelConfig(ADC1,channel,1,ADC_SampleTime_480Cycles);
	
	//开始采集 软件开始控制
	ADC_SoftwareStartConv(ADC1);
	
	//等待采集结束
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	
	//获取的结果进行返回
	return ADC_GetConversionValue(ADC1);

}


//3.均值操作函数
unsigned short int getADC_average(unsigned int  channel,char times)
{
		unsigned short int value =0;
	for(int i = 0;i < times;i++)
	{
		value += getADC_channel(channel);
		delay_ms(5);
	}
	return value/times;

}



