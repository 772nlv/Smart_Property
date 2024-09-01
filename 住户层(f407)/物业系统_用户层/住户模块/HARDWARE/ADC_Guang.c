#include "user.h"
//�������� ADC1 -IN0 -PA0
//1����ADC��·
void ADC1_GUANG_INO_Config()
{
	//1ʱ�� APB2 84/4 = 21 <36MHZ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
		GPIO_InitTypeDef Vstruct;
		//���ź���
	Vstruct.GPIO_Pin = 	GPIO_Pin_0;
	//���ģʽ
	Vstruct.GPIO_Mode = GPIO_Mode_OUT;
	//�������
	Vstruct.GPIO_OType = GPIO_OType_PP;
	//�������� ���ǣ���ע�⣬��GPIO���ű�����Ϊ���ģʽ��GPIO_Mode_OUT��ʱ��
	//�ڲ�������������ÿ��ܻ��ܵ����ƻ���ԣ���Ϊ���ģʽ������ֱ�ӿ������ŵĵ�ƽ״̬��
	Vstruct.GPIO_PuPd = GPIO_PuPd_NOPULL;//GPIO_PuPd_NOPULL
	//��Ӧ�ٶ�
	Vstruct.GPIO_Speed = GPIO_Low_Speed;
	//��ʼ���˿ں���
	GPIO_Init(GPIOC,&Vstruct);
	//GPIOA 0�Ÿ��ù���
	
	GPIO_InitTypeDef gpioastruct;
	gpioastruct.GPIO_Pin = GPIO_Pin_0;
	gpioastruct.GPIO_Mode = GPIO_Mode_AN;
	gpioastruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&gpioastruct);
	//gpio����Ҫ�������Ÿ���ӳ��
	//GPIO_PinAFConfig()
	
	//2.adc��·����
	ADC_CommonInitTypeDef adcstruct;
	//�ر�dma��·
	adcstruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	//����ģʽ
	adcstruct.ADC_Mode = ADC_Mode_Independent;
	//���ں����ĳ�ʼ��ֵ���ҵ���ѡ��ֵ
	adcstruct.ADC_Prescaler = ADC_Prescaler_Div4;
	//���βɼ���ʱ����
	adcstruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&adcstruct);
	
	//3.ADC����
	ADC_InitTypeDef guangstruct;
	//12λ����
	guangstruct.ADC_Resolution = ADC_Resolution_12b;
	//��Ҫɨ�� - ���μ���
	guangstruct.ADC_ScanConvMode = DISABLE;
	//ת��һ�ξ�ֹͣ
	guangstruct.ADC_ContinuousConvMode = DISABLE;
	//�Ҷ���
	guangstruct.ADC_DataAlign = 	ADC_DataAlign_Right;
	//������ʽ
	guangstruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	//ֻת��һ������������
	guangstruct.ADC_NbrOfConversion =1;
	//��ʼ��
	ADC_Init(ADC1,&guangstruct);
	//3.����adc��·ʹ��
	ADC_Cmd(ADC1,ENABLE);


}


//2.�ɼ��źŲ�������
unsigned short int getADC_channel(unsigned int channel)
{
	//ADC��ʼ�ɼ�����
	//adc��·ͨ�� һ�����еĲ���ʱ��
	ADC_RegularChannelConfig(ADC1,channel,1,ADC_SampleTime_480Cycles);
	
	//��ʼ�ɼ� �����ʼ����
	ADC_SoftwareStartConv(ADC1);
	
	//�ȴ��ɼ�����
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	
	//��ȡ�Ľ�����з���
	return ADC_GetConversionValue(ADC1);

}


//3.��ֵ��������
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



