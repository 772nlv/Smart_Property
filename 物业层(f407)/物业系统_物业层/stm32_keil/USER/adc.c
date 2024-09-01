#include "user.h"


//�������� 


//����ADC��·������������----��λ
void ADC1_Light_Config()
{
	//1��ʱ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	//2��GPIOA��0������ģ��ģʽ
	GPIO_InitTypeDef gpioastruct;
	gpioastruct.GPIO_Pin = GPIO_Pin_0;
	gpioastruct.GPIO_Mode = GPIO_Mode_AN;
	gpioastruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&gpioastruct);
	//GPIOC��0������ģ��ģʽ
	GPIO_InitTypeDef gpiocstruct;
	gpiocstruct.GPIO_Pin = GPIO_Pin_0;
	gpiocstruct.GPIO_Mode = GPIO_Mode_AN;
	gpiocstruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC,&gpiocstruct);

	//3��ADC��·����
	ADC_CommonInitTypeDef adcstruct;
	//�ر�DMA��·
	adcstruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	//����ģʽ
	adcstruct.ADC_Mode = ADC_Mode_Independent;
	//��Ƶ
	adcstruct.ADC_Prescaler = ADC_Prescaler_Div4;
	//���βɼ����ݵ�ʱ����
	adcstruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	//��ʼ��
	ADC_CommonInit(&adcstruct);
	
	//4��������������
	ADC_InitTypeDef lightstruct;
	//λ����
	lightstruct.ADC_Resolution = ADC_Resolution_12b;
	//��Ҫɨ�衪�����μ���
	lightstruct.ADC_ScanConvMode = DISABLE;
	//ת��һ�ξ�ֹͣ
	lightstruct.ADC_ContinuousConvMode = DISABLE;
	//�ɼ������Ҷ���
	lightstruct.ADC_DataAlign = ADC_DataAlign_Right;
	//������ʽ
	lightstruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	//ֻת��һ������������
	lightstruct.ADC_NbrOfConversion = 1;
	//��ʼ��
	ADC_Init(ADC1,&lightstruct);
	
	//ADC��·ʹ��
	ADC_Cmd(ADC1,ENABLE);
}

//�ɼ���Ϣ
//ͨ����ֵ
//��ʼ�ɼ��ĺ���
unsigned short Get_ADC_Channel(unsigned int channel)
{
	//ADC��ʼ�ɼ�����
	//adc��· ͨ�� һ������ ����ʱ��
	ADC_RegularChannelConfig(ADC1,channel,1,ADC_SampleTime_480Cycles);
	
	//��ʼ�ɼ��������ʼ����
	ADC_SoftwareStartConv(ADC1);
	//�ȴ��ɼ�����  ���۲����ڳ����ж������� �����л�֤�����۵Ĵ��ڡ�
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));

	//��ȡ�Ľ�����з���
	return ADC_GetConversionValue(ADC1);
}


//��ֵ����
//ͨ���� + �ɼ�����
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































